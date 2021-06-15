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

typedef struct s_ipcs
{
	char	*shm_addr;
	sem_t	*sem;
	mqd_t	mq;
} t_ipcs;

typedef struct s_pos
{
	int x;
	int y;
} t_pos;

typedef struct s_player
{
	int team_number;
	t_pos position;
	t_ipcs *ipcs;
	t_logger *logger;
	int *process_count_mapped;
} t_player;

void check_input(int ac, char **av);

t_ipcs *create_ipcs(const int process_count);

bool close_ipcs(t_ipcs *ipcs);
bool close_sem(sem_t **sem);
bool close_mq(mqd_t mq);
void destroy_ipcs(t_ipcs *ipcs, const int process_count);

void fill_player_info(t_player *player, int team_number);
t_pos get_start_player_position(void);
void find_starting_place(t_player *player);
void delete_player(t_player *player);

bool check_death(const t_player *player);
bool check_occupied_cell(const char *shm_addr, const int x, const int y);

#endif
