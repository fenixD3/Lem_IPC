#ifnde LOGGER_H
# define LOGGER_H

typedef struct s_logger
{
	typedef struct s_files
	{
		FILE			*file_fd;
		struct s_files	*next;
	}	t_files;
}	t_logger;

#endif
