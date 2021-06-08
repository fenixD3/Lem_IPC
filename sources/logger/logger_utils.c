#include "logger.h"
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>

void write_to_log(t_logger *logger, const char *format, ...)
{
	size_t len;
	t_files *curr_log;
	va_list args;

	sem_wait(logger->sem);
	va_start(args, format);
	len = vsprintf(logger->buff, format, args);
	va_end(args);
	curr_log = logger->files_info;
	while (curr_log && curr_log->next && curr_log->is_writable)
	{
		if (*curr_log->available_space < len)
		{
			create_log_file(&logger->files_info);
			curr_log = logger->files_info;
			break;
		}
		curr_log = curr_log->next;
	}
	snprintf(curr_log->file_mapped + (LOG_FILE_SIZE - *curr_log->available_space), len + 1, "%s", logger->buff);
	*curr_log->available_space -= len;
	sem_post(logger->sem);
}
