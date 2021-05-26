#ifndef LOGGER_H
# define LOGGER_H

/// TODO продумать, как использовать logger меж процессами с расширением файлов!

typedef struct s_files
{
	int				file_fd;
	char			*file_mapped;
	struct s_files	*next;
}	t_files;

typedef struct s_logger
{
	t_files files_info;
}	t_logger;

# define LOG_PATH "./log_"

void	create_log(t_files *files_info);
int		get_log_file_size(void);

#endif
