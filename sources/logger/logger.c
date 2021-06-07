#include "logger.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include <errno.h>

#include "ipc_management.h"

t_logger *create_logger()
{
	t_logger *logger;

	if (!(logger = malloc(sizeof(t_logger))))
	{
		perror("malloc_for_logger");
		exit(EXIT_FAILURE);
	}
	logger->sem = create_sem(LOG_SEM_NAME);
	logger->files_info = NULL;
	return logger;
}

static void add_log_file_to_chain(t_files **files_info, t_files *new_file_info)
{
	new_file_info->next = *files_info;
	*files_info = new_file_info;
}

void create_log_file(t_files **files_info)
{
	t_files		*new_file_info;
	int			file_fd;
	static int	log_postfix;

	if (!(new_file_info = malloc(sizeof(t_files))))
	{
		perror("malloc_file_info");
		exit(EXIT_FAILURE);
	}
	sprintf(new_file_info->file_name, "%s%d", LOG_PATH, log_postfix++);
	if ((file_fd = open(new_file_info->file_name, O_CREAT | O_EXCL | O_RDWR, 0777)) == -1)
	{
		if (errno == EEXIST)
		{
			if ((file_fd = open(new_file_info->file_name, O_CREAT | O_RDWR, 0777)) == -1)
			{
				perror("open_log");
				exit(EXIT_FAILURE);
			}
			if (ftruncate(file_fd, LOG_FILE_SIZE) == -1)
			{
				perror("ftruncate_log_file");
				exit(EXIT_FAILURE);
			}
			new_file_info->available_space = (size_t *)get_shm(LOG_SHM_SIZE_NAME, LOG_FILE_SIZE);
			*new_file_info->available_space = LOG_FILE_SIZE;
		}
		else
		{
			perror("create_log");
			exit(EXIT_FAILURE);
		}
	}
	new_file_info->file_mapped = mmap(0, LOG_FILE_SIZE,
	PROT_WRITE | PROT_READ, MAP_SHARED, file_fd, 0);
	if (new_file_info->file_mapped == MAP_FAILED)
	{
		perror("mmap_log_file");
		exit(EXIT_FAILURE);
	}
	if (close(file_fd) == -1)
	{
		//munmap(new_file_info->file_mapped, LOG_FILE_SIZE);
		perror("close_log_fd");
		exit(EXIT_FAILURE);
	}
	new_file_info->is_writable = true;
	add_log_file_to_chain(files_info, new_file_info);
}
