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

	is_error = false;
	if (close_sem(&ipcs->sem))
		is_error = true;
	if (close_mq(ipcs->mq))
		is_error = true;
	return is_error;
}

void	destroy_ipcs(t_ipcs *ipcs)
{
	bool is_error;

	is_error = false;
	if (destroy_shm((void **) &ipcs->shm_addr, SHM_MAP_NAME, MAP_SIZE))
		is_error = true;
	if (destroy_sem(SEM_NAME))
		is_error = true;
	if (destroy_mq(MQ_NAME))
		is_error = true;
	if (is_error)
		exit(EXIT_FAILURE);
}
