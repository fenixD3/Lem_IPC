#ifndef IPC_LIB_H
#define IPC_LIB_H

#include <mqueue.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct mq_attr t_mq_attr;

typedef struct s_ipcs
{
	char	*shm_addr;
	sem_t	*sem;
	mqd_t	mq;
	t_mq_attr *mq_attrs;
} t_ipcs;

char *get_shm(const char *shm_name, size_t shm_size, const int process_count);
sem_t *get_sem(const char *sem_name, const int process_count, const int default_value);
mqd_t get_mq(const char *mq_name_prefix, const int process_count, const int team_number);
bool get_or_create_mapped_file(const char *file_name, size_t file_size, void **file_mapped);

bool destroy_shm(void **shm_addr, const char *shm_name, size_t shm_size);
bool destroy_sem(const char *sem_name);
void destroy_mq(const char *mq_name_prefix, const int team_count);

bool remove_file(const char *file_name);

bool close_ipcs(t_ipcs *ipcs);
bool close_sem(sem_t **sem);
bool close_mq(mqd_t mq);

bool check_occupied_cell(const char *map_addr, const int x, const int y,const int map_bound);
bool check_out_of_map_bound(const int x, const int y, const int map_bound);
int get_number_from_map(
	const char *map_addr,
	const int x_offset,
	const int y_offset,
	const int number_length,
	const int map_bound);

#endif
