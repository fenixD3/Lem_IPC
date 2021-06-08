#include "lem_ipc.h"

bool close_sem(sem_t **sem)
{
	bool is_error;

	is_error = false;
	if (sem_close(*sem) == -1)
	{
		perror("sem_close");
		is_error = true;
	}
	return is_error;
}

bool close_mq(mqd_t mq)
{
	bool is_error;

	is_error = false;
	if (mq_close(mq) == -1)
	{
		perror("mq_close");
		is_error = true;
	}
	return is_error;
}

bool destroy_shm(void **shm_addr, const char *shm_name, size_t shm_size)
{
	bool is_error;

	is_error = false;
	if (munmap(*shm_addr, shm_size) == -1)
	{
		perror("munmap");
		is_error = true;
	}
	if (shm_unlink(shm_name) == -1)
	{
		perror("shm_unlink");
		is_error = true;
	}
	return is_error;
}

bool destroy_sem(const char *sem_name)
{
	bool is_error;

	is_error = false;
	if (sem_unlink(SEM_NAME) == -1)
	{
		perror("sem_unlink");
		is_error = true;
	}
	return is_error;
}

bool destroy_mq(const char *mq_name)
{
	bool is_error;

	is_error = false;
	if (mq_unlink(mq_name) == -1)
	{
		perror("mq_unlink");
		is_error = true;
	}
	return is_error;
}
