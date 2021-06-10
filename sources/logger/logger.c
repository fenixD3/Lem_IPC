#include "logger.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>

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

	if (!(new_file_info = malloc(sizeof(t_files))))
	{
		perror("malloc_file_info");
		exit(EXIT_FAILURE);
	}
	const time_t curr_time = time(NULL);
	new_file_info->file_name_shm = get_shm(LOG_SHM_FILE_NAME, LOG_FILE_NAME_SIZE);
	if (*new_file_info->file_name_shm == '\0')
		sprintf(new_file_info->file_name_shm, "%s%s%s", LOG_PATH, ctime(&curr_time), ".txt");
	new_file_info->available_space_shm = (size_t *)get_shm(LOG_SHM_SIZE_NAME, sizeof(size_t));
	if (get_or_create_mapped_file(new_file_info->file_name_shm, LOG_FILE_SIZE, (void **)&new_file_info->file_mapped))
		*new_file_info->available_space_shm = LOG_FILE_SIZE;
	new_file_info->is_writable = true;
	add_log_file_to_chain(files_info, new_file_info);
}

void destroy_logger(t_logger *logger)
{
	bool is_error;
	t_files *curr_file;

	is_error = false;
	curr_file = logger->files_info;
	while(curr_file)
	{
		if (destroy_shm((void **)&curr_file->file_name_shm, LOG_SHM_FILE_NAME, LOG_FILE_NAME_SIZE))
			is_error = true;
		if (destroy_shm((void **)&curr_file->available_space_shm, LOG_SHM_SIZE_NAME, sizeof(size_t)))
			is_error = true;
		if (munmap(curr_file->file_mapped, LOG_FILE_SIZE) == -1)
		{
			perror("munmap_log_file");
			is_error = true;
		}
		curr_file = curr_file->next;
	}
	destroy_sem(LOG_SEM_NAME);
	free(logger);
	if (is_error)
		exit(EXIT_FAILURE);
}
