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

	is_error = close_shm(ipcs);
	is_error = (is_error) ? is_error : close_sem(ipcs);
	is_error = (is_error) ? is_error : close_mq(ipcs);
	return (is_error);
}

void	destroy_ipcs(t_ipcs *ipcs)
{
	bool is_error;

	is_error = close_ipcs(ipcs);
	if (munmap(ipcs->shm_addr, MAP_SIZE) == -1)
	{
		perror("munmap");
		is_error = true;
	}
	if (shm_unlink(SHM_MAP_NAME) == -1)
	{
		perror("shm_unlink");
		is_error = true;
	}
	if (sem_unlink(SEM_NAME) == -1)
	{
		perror("sem_unlink");
		is_error = true;
	}
	if (mq_unlink(MQ_NAME) == -1)
	{
		perror("mq_unlink");
		is_error = true;
	}
	if (is_error)
		exit(EXIT_FAILURE);
}
