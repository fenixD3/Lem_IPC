#ifndef LOGGER_H
# define LOGGER_H

#include <semaphore.h>

typedef struct s_log_ipcs
{
	int		shm_fd;
	char	*shm_addr;
	sem_t	*sem;
}	t_log_ipcs;

typedef struct s_files
{
	char			file_name[30];
	char			*file_mapped;
	struct s_files	*next;
}	t_files;

typedef struct s_logger
{
	t_files		*files_info;
	t_log_ipcs	ipcs;
}	t_logger;

# define LOG_PATH "./log_"
# define LOG_FORMATION(name) #name
# define LOG_MIDDLEWARE_FORMATION(path, num) LOG_FORMATION(path##num)
# define LOG_NAME(path, num) LOG_MIDDLEWARE_FORMATION(path, num)

t_files	*create_log();
int		get_log_file_size(void);

#endif
