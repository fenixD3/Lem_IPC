#include "logger.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>

t_files	*create_log(void)
{
	t_files		*file_info;
	int			file_fd;
	static int	log_postfix;

	if (!(file_info = malloc(sizeof(t_files))))
	{
		perror("malloc_file_info");
		exit(EXIT_FAILURE);
	}
	sprintf(file_info->file_name, "%s%d", LOG_PATH, log_postfix++);
	if ((file_fd = open(file_info->file_name, O_CREAT | O_RDWR, 0777)) == -1)
	{
		perror("create_log");
		exit(EXIT_FAILURE);
	}
	file_info->file_mapped = mmap(0, get_log_file_size(),
	PROT_WRITE | PROT_READ, MAP_SHARED, file_fd, 0);
	if (file_info->file_mapped == MAP_FAILED)
	{
		perror("mmap_log_file");
		exit(EXIT_FAILURE);
	}
	if (close(file_fd) == -1)
	{
		perror("close_log_fd");
		exit(EXIT_FAILURE);
	}
	return (file_info);
}
