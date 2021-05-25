#ifndef LEM_IPC_H
# define LEM_IPC_H

# define TEAM_COUNT 4
# define MAP_X 20
# define MAP_Y 20

# define SHM_MAP_NAME "game_map"
# define SEM_NAME "/game_sem"
# define SEM_DEFAULT_VALUE 1
# define MQ_NAME "/game_mq"

# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <errno.h>
# include <unistd.h>
# include <sys/mman.h>
# include <fcntl.h>
# include <semaphore.h>
# include <mqueue.h>

typedef struct s_ipcs
{
	int		shm_fd;
	char	*shm_addr;
	sem_t	*sem;
	mqd_t	mq;
}		t_ipcs;

typedef struct s_pos
{
	int x;
	int y;
}		t_pos;

typedef struct s_player
{
	int		team_number;
	t_ipcs	*ipcs;
}		t_player;

void	check_input(int ac, char **av);

void	create_ipcs(t_ipcs *ipcs);
void	create_shm(t_ipcs *ipcs);
int		get_shm_mmap_size(void);
void	create_sem(t_ipcs *ipcs);
void	create_mq(t_ipcs *ipcs);

void	close_ipcs(t_ipcs *ipcs);
void	close_shm(t_ipcs *ipcs);
void	close_sem(t_ipcs *ipcs);
void	close_mq(t_ipcs *ipcs);

void	fill_player_info(t_player *player, t_ipcs *ipcs, int team_number);

t_pos	get_start_player_position(void);
void	find_starting_place(t_player *player);

#endif
