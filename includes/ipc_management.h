#ifndef IPC_MANAGEMENT_H
#define IPC_MANAGEMENT_H

# include <mqueue.h>

char *get_shm(const char *shm_name, size_t shm_size, const int process_count);
sem_t *get_sem(const char *sem_name, const int process_count);
mqd_t get_mq(const char *mq_name, const int process_count);

bool get_or_create_mapped_file(const char *file_name, size_t file_size, void **file_mapped);

bool destroy_shm(void **shm_addr, const char *shm_name, size_t shm_size);
bool destroy_sem(const char *sem_name);
bool destroy_mq(const char *mq_name);

bool remove_file(const char *file_name);

#endif
