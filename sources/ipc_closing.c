#include "lem_ipc.h"

bool close_shm(t_ipcs *ipcs)
{
	bool is_error;

	is_error = false;
	//if (close(ipcs->shm_fd) == -1)
	//{
	//	perror("shm_close");
	//	is_error = true;
	//}
	return (is_error);
}

bool close_sem(t_ipcs *ipcs)
{
	bool is_error;

	is_error = false;
	if (sem_close(ipcs->sem) == -1)
	{
		perror("sem_close");
		is_error = true;
	}
	return (is_error);
}

bool close_mq(t_ipcs *ipcs)
{
	bool is_error;

	is_error = false;
	if (mq_close(ipcs->mq) == -1)
	{
		perror("mq_close");
		is_error = true;
	}
	return (is_error);
}
