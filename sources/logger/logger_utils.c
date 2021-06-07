#include <unistd.h>
#include "logger.h"
#include <stdio.h>
#include <string.h>

void write_to_log(t_logger *logger, const char *to_log)
{
	size_t len;
	t_files *curr_log;

	len = strlen(to_log) + 1;
	sem_wait(logger->sem);
	curr_log = logger->files_info;
	while (curr_log && curr_log->is_writable)
	{
		if (*curr_log->available_space > len)
		{
			create_log_file(&logger->files_info);
			curr_log = logger->files_info;
			break;
		}
		curr_log = curr_log->next;
	}
	sprintf(curr_log->file_mapped, "%s\n", to_log);
	sem_post(logger->sem);
}
