#include "ipc_lib.h"

char *get_shm(const char *shm_name, size_t shm_size, const int process_count)
{
	int		shm_fd;
	char	*shm_addr;

	if (process_count == 1)
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
	shm_addr = mmap(NULL, shm_size, PROT_WRITE | PROT_READ, MAP_SHARED, shm_fd, 0);
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

sem_t *get_sem(const char *sem_name, const int process_count, const int default_value)
{
	sem_t *sem;

	if (process_count == 1)
		sem_unlink(sem_name);
	sem = sem_open(sem_name, O_CREAT | O_EXCL, 0644, default_value);
	if (sem == SEM_FAILED && errno == EEXIST)
		sem = sem_open(sem_name, 0);
	else if (sem == SEM_FAILED)
	{
		perror("sem_open");
		exit(EXIT_FAILURE);
	}
	return sem;
}

mqd_t get_mq(const char *mq_name_prefix, const int process_count, const int team_number)
{
	mqd_t mq;
	char *mq_name;

	if ((mq_name = malloc(sizeof(char) * (strlen(mq_name_prefix) + 3))) == NULL)
	{
		perror("malloc_mq_name");
		exit(EXIT_FAILURE);
	}
	sprintf(mq_name, "%s%s%d", mq_name_prefix, "_", team_number);
	if (process_count == 1)
		mq_unlink(mq_name);
	mq = mq_open(mq_name, O_RDWR | O_CREAT | O_EXCL | O_NONBLOCK, 0644, NULL);
	if (mq == (mqd_t)-1 && errno == EEXIST)
		mq = mq_open(mq_name, O_RDWR | O_NONBLOCK, 0644, NULL);
	else if (mq == (mqd_t)-1)
	{
		perror("mq_open");
		exit(EXIT_FAILURE);
	}
	return mq;
}

bool get_or_create_mapped_file(const char *file_name, size_t file_size, void **file_mapped)
{
	bool is_new_file = false;
	int file_fd;

	file_fd = open(file_name, O_CREAT | O_EXCL | O_RDWR, 0644);
	if (file_fd == -1 && errno == EEXIST)
	{
		if ((file_fd = open(file_name, O_CREAT | O_RDWR, 0644)) == -1)
		{
			perror("open_log");
			exit(EXIT_FAILURE);
		}
	}
	else if (file_fd == -1)
	{
		perror("create_log");
		exit(EXIT_FAILURE);
	}
	else
	{
		if (ftruncate(file_fd, file_size) == -1)
		{
			perror("ftruncate_log_file");
			exit(EXIT_FAILURE);
		}
		is_new_file = true;
	}
	*file_mapped = mmap(0, file_size, PROT_WRITE | PROT_READ, MAP_SHARED, file_fd, 0);
	if (*file_mapped == MAP_FAILED)
	{
		perror("mmap_log_file");
		exit(EXIT_FAILURE);
	}
	if (close(file_fd) == -1)
	{
		perror("close_log_fd");
		exit(EXIT_FAILURE);
	}
	return is_new_file;
}
