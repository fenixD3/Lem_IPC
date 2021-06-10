#ifndef IPC_MANAGEMENT_H
#define IPC_MANAGEMENT_H

# include <mqueue.h>

char *get_shm(const char *shm_name, size_t shm_size);
sem_t *create_sem(const char *sem_name);
mqd_t create_mq(const char *mq_name);
bool get_or_create_mapped_file(const char *file_shm_name, void **file_mapped);

bool destroy_shm(void **shm_addr, const char *shm_name, size_t shm_size);
bool destroy_sem(const char *sem_name);
bool destroy_mq(const char *mq_name);

#endif
