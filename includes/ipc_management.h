#ifndef IPC_MANAGEMENT_H
#define IPC_MANAGEMENT_H

# include <mqueue.h>

char *get_shm(const char *shm_name, long long shm_size);
sem_t *create_sem(const char *sem_name);
mqd_t create_mq(const char *mq_name);

#endif