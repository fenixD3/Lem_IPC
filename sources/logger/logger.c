#include "logger.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>

void	create_log(t_files *files_info)
{
	t_files	*file_info;

	file_info = malloc(sizeof(t_files));
	if (file_info == NULL)
	{
		perror("malloc_file_info");
		exit(EXIT_FAILURE);
	}
	file_info->file_fd = open(LOG_PATH, O_CREAT | O_RDWR, 0777);
	if (file_info->file_fd == -1)
	{
		perror("create_log");
		exit(EXIT_FAILURE);
	}
	file_info->file_mapped = mmap(0, get_log_file_size(),
	PROT_WRITE | PROT_READ, MAP_SHARED, file_info->file_fd, 0);
	if (file_info->file_mapped == MAP_FAILED)
	{
		perror("mmap_log_file");
		exit(EXIT_FAILURE);
	}
}
