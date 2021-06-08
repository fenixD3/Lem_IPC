#include "lem_ipc.h"
#include "ipc_management.h"

char *get_shm(const char *shm_name, size_t shm_size)
{
	int		shm_fd;
	char	*shm_addr;

	shm_unlink(shm_name);
	shm_fd = shm_open(shm_name, O_CREAT | O_RDWR | O_EXCL, 0644);
	if (shm_fd == -1 && errno == EEXIST)
		shm_fd = shm_open(shm_name, O_CREAT | O_RDWR, 0644);
	else if (shm_fd == -1)
	{
		perror("shm_open");
		exit(EXIT_FAILURE);
	}
	else if (ftruncate(shm_fd, shm_size) == -1)
	{
		perror("ftruncate");
		exit(EXIT_FAILURE);
	}
	shm_addr = mmap(NULL, shm_size, PROT_WRITE | PROT_READ,
					MAP_SHARED, shm_fd, 0);
	if (shm_addr == MAP_FAILED)
	{
		perror("mmap");
		exit(EXIT_FAILURE);
	}
	if (close(shm_fd) == -1)
	{
		perror("shm_close");
		exit(EXIT_FAILURE);
	}
	return shm_addr;
}

sem_t *create_sem(const char *sem_name)
{
	sem_t *sem;

	sem_unlink(sem_name);
	sem = sem_open(sem_name, O_CREAT | O_EXCL, 0644, SEM_DEFAULT_VALUE);
	if (sem == SEM_FAILED && errno == EEXIST)
		sem = sem_open(sem_name, 0);
	else if (sem == SEM_FAILED)
	{
		perror("sem_open");
		exit(EXIT_FAILURE);
	}
	return sem;
}

mqd_t create_mq(const char *mq_name)
{
	mqd_t mq;

	mq_unlink(mq_name);
	mq = mq_open(mq_name, O_RDWR | O_CREAT | O_EXCL, 0644, NULL);
	if (mq == (mqd_t)-1 && errno == EEXIST)
		mq = mq_open(mq_name, O_RDWR, 0644, NULL);
	else if (mq == (mqd_t)-1)
	{
		perror("mq_open");
		exit(EXIT_FAILURE);
	}
	return mq;
}
