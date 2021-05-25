#include "lem-ipc.h"

void	create_shm(t_ipcs *ipcs)
{
	int		shm_fd;
	char	*shm_addr;

	shm_fd = shm_open(SHM_MAP_NAME, O_CREAT | O_RDWR | O_EXCL, 0777);
	if (shm_fd == -1 && errno == EEXIST)
		shm_fd = shm_open(SHM_MAP_NAME, O_CREAT | O_RDWR, 0777);
	else if (shm_fd == -1)
	{
		perror("shm_open");
		exit(EXIT_FAILURE);
	}
	if (ftruncate(shm_fd, MAP_X * MAP_Y) == -1)
	{
		perror("ftruncate");
		exit(EXIT_FAILURE);
	}
	shm_addr = mmap(NULL, get_shm_mmap_size(), PROT_WRITE | PROT_READ,
					MAP_SHARED, shm_fd, 0);
	if (shm_addr == MAP_FAILED)
	{
		perror("mmap");
		exit(EXIT_FAILURE);
	}
	ipcs->shm_fd = shm_fd;
	ipcs->shm_addr = shm_addr;
}

void	create_sem(t_ipcs *ipcs)
{
	sem_t *sem;

	sem = sem_open(SEM_NAME, O_CREAT | O_EXCL, 0777, SEM_DEFAULT_VALUE);
	if (sem == SEM_FAILED && errno == EEXIST)
		sem = sem_open(SEM_NAME, 0);
	else
	{
		perror("sem_open");
		exit(EXIT_FAILURE);
	}
	ipcs->sem = sem;
}

void	create_mq(t_ipcs *ipcs)
{
	mqd_t mq;

	mq = mq_open(MQ_NAME, O_RDWR | O_CREAT | O_EXCL, 0777, NULL);
	if (mq == (mqd_t)-1 && errno == EEXIST)
		mq = mq_open(MQ_NAME, O_RDWR, 0777, NULL);
	else if (mq == (mqd_t)-1)
	{
		perror("mq_open");
		exit(EXIT_FAILURE);
	}
	ipcs->mq = mq;
}
