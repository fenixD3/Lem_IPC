#include "ipc_lib.h"

bool close_ipcs(t_ipcs *ipcs)
{
	bool is_error;

	is_error = false;
	if (close_sem(&ipcs->sem))
		is_error = true;
	if (close_mq(ipcs->mq))
		is_error = true;
	return is_error;
}

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
	if (sem_unlink(sem_name) == -1)
	{
		perror("sem_unlink");
		is_error = true;
	}
	return is_error;
}

void destroy_mq(const char *mq_name_prefix, const int team_count)
{
	char *mq_name;

	if ((mq_name = malloc(sizeof(char) * (strlen(mq_name_prefix) + 3))) == NULL)
	{
		perror("malloc_mq_name");
		exit(EXIT_FAILURE);
	}
	for (int i = 1; i <= team_count; ++i)
	{
		sprintf(mq_name, "%s%s%d", mq_name_prefix, "_", i);
		mq_unlink(mq_name);
	}
}

bool remove_file(const char *file_name)
{
	bool is_error;

	is_error = false;
	if (unlink(file_name) == -1)
	{
		perror("unlink");
		is_error = true;
	}
	return is_error;
}
