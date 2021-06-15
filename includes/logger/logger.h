#ifndef LOGGER_H
#define LOGGER_H

#include <semaphore.h>
#include <stdbool.h>

typedef struct s_files
{
	char *file_name_shm;
	char *file_mapped;
	size_t *available_space_shm;
	bool is_writable;
	struct s_files *next;
} t_files;

typedef struct s_logger
{
	t_files *files_info;
	char buff[256];
	sem_t *sem;
} t_logger;

#define LOG_PATH "./log_"
#define LOG_SHM_FILE_NAME "/log_shm_name"
#define LOG_FILE_NAME_SIZE 30
#define LOG_FILE_SIZE (256 * getpagesize())
#define LOG_SEM_NAME "/log_sem"
#define LOG_SHM_SIZE_NAME "/log_shm_size"

t_logger *create_logger(const int process_count);
void create_log_file(t_files **files_info, const int process_count);

void write_to_log(t_logger *logger, const int process_count, const char *format, ...);

void destroy_logger(t_logger *logger, const int process_count);

#endif
