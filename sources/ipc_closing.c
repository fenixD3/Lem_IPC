#include "lem_ipc.h"

void	close_shm(t_ipcs *ipcs)
{
	bool is_error;

	is_error = false;
	if (munmap(ipcs->shm_addr, get_shm_mmap_size()) == -1)
	{
		perror("munmap");
		is_error = true;
	}
	if (close(ipcs->shm_fd) == -1)
	{
		perror("shm_close");
		is_error = true;
	}
	if (shm_unlink(SHM_MAP_NAME) == -1)
	{
		perror("shm_unlink");
		is_error = true;
	}
	ipcs->shm_fd = -1;
	ipcs->shm_addr = NULL;
	if (is_error)
		exit(EXIT_FAILURE);
}

void	close_sem(t_ipcs *ipcs)
{
	if (sem_close(ipcs->sem) == -1)
	{
		perror("sem_close");
		exit(EXIT_FAILURE);
	}
	if (sem_unlink(SEM_NAME) == -1)
	{
		perror("sem_unlink");
		exit(EXIT_FAILURE);
	}
	ipcs->sem = NULL;
}

void	close_mq(t_ipcs *ipcs)
{
	if (mq_unlink(MQ_NAME) == -1)
	{
		perror("mq_unlink");
		exit(EXIT_FAILURE);
	}
	ipcs->mq = (mqd_t)-1;
}
