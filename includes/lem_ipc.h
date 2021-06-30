#ifndef LEM_IPC_H
#define LEM_IPC_H

#define TEAM_COUNT 4
#define MAP_X 20
#define MAP_SIZE MAP_X * MAP_X

#define SHM_MAP_NAME "game_map"
#define SEM_NAME "/game_sem"
#define SEM_DEFAULT_VALUE 1
#define MQ_NAME "/game_mq"

#define FILE_PROCESS_NAME "./process.txt"

#define MAP_FILLER '.'

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <semaphore.h>
#include <mqueue.h>

#include "logger.h"

typedef struct mq_attr t_mq_attr;

typedef struct s_ipcs
{
	char	*shm_addr;
	sem_t	*sem;
	mqd_t	mq;
	t_mq_attr *mq_attrs;
} t_ipcs;

typedef struct s_pos
{
	int x;
	int y;
} t_pos;

typedef struct s_player
{
	int team_number;
	int team_players;
	t_pos position;
	t_ipcs *ipcs;
	char *msg_buff;
	t_logger *logger;
	int *process_count_mapped;
} t_player;

typedef enum e_direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	NONE
} t_direction;

extern void (*g_moving[4])(t_player *, const char);

void check_input(int ac, char **av);

t_ipcs *create_ipcs(const int process_count, const int team_number);

bool close_ipcs(t_ipcs *ipcs);
bool close_sem(sem_t **sem);
bool close_mq(mqd_t mq);
void destroy_ipcs(t_ipcs *ipcs, const int team_players);

void fill_player_info(t_player *player, int team_number);
char *create_msg_buff(const long max_msg_size);
void init_player(t_player *player);
t_pos get_start_player_position(void);
void find_starting_place(t_player *player);
void delete_player(t_player *player);

bool check_death(const t_player *player);
bool check_occupied_cell(const char *map_addr, const int x, const int y);

void game_loop(t_player *player);
t_pos find_enemy(t_pos player_position, const char *map_addr, const int team_number);
bool get_message(t_player *player);
t_pos get_enemy_position(t_player *player);
void move_to(t_player *player, const t_pos *enemy_pos);
t_direction get_direction(const t_pos *player_pos, const t_pos *enemy_pos);

void move_up(t_player *player, const char free_space_filler);
void move_down(t_player *player, const char free_space_filler);
void move_left(t_player *player, const char free_space_filler);
void move_right(t_player *player, const char free_space_filler);

#endif
