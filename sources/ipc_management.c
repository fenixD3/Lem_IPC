#include "lem_ipc.h"
#include "ipc_management.h"

void	create_ipcs(t_ipcs *ipcs)
{
	ipcs->shm_addr = get_shm(SHM_MAP_NAME, MAP_SIZE);
	ipcs->sem = create_sem(SEM_NAME);
	ipcs->mq = create_mq(MQ_NAME);
}

bool	close_ipcs(t_ipcs *ipcs)
{
	bool is_error;

	is_error = close_sem(&ipcs->sem);
	is_error = (is_error) ? is_error : close_mq(ipcs->mq);
	return (is_error);
}

void	destroy_ipcs(t_ipcs *ipcs)
{
	bool is_error;

	is_error = destroy_shm((void **) &ipcs->shm_addr, SHM_MAP_NAME, MAP_SIZE);
	is_error = (is_error) ? is_error : destroy_sem(SEM_NAME);
	is_error = (is_error) ? is_error : destroy_mq(MQ_NAME);
	if (is_error)
		exit(EXIT_FAILURE);
}
