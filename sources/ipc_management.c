#include "lem_ipc.h"
#include "ipc_lib.h"

static void init_shm_map(char *shm_addr, const char filler)
{
	for (int x = 0; x < MAP_SIZE; x += MAP_X)
		for (int y = 0; y < MAP_X; ++y)
			*(shm_addr + (x + y)) = filler;
}

t_ipcs *create_ipcs(const int process_count, const int team_number)
{
	t_ipcs *ipcs;

	if (!(ipcs = malloc(sizeof(t_ipcs))))
	{
		perror("malloc_for_ipcs");
		exit(EXIT_FAILURE);
	}
	ipcs->shm_addr = get_shm(SHM_MAP_NAME, MAP_SIZE, process_count);
	if (process_count == 1)
		init_shm_map(ipcs->shm_addr, MAP_FILLER);
	ipcs->sem = get_sem(SEM_NAME, process_count, SEM_DEFAULT_VALUE);
	ipcs->mq = get_mq(MQ_NAME, process_count, team_number);
	if (!(ipcs->mq_attrs = malloc(sizeof(t_mq_attr))))
	{
		perror("malloc_mq_attrs");
		exit(EXIT_FAILURE);
	}
	if (mq_getattr(ipcs->mq, ipcs->mq_attrs) == -1)
	{
		perror("mq_getattr");
		exit(EXIT_FAILURE);
	}
	return ipcs;
}

char *create_msg_buff(const long max_msg_size)
{
	char *buff;

	if (!(buff = malloc(sizeof(char) * (max_msg_size + 1))))
	{
		perror("malloc_mq_buff");
		exit(EXIT_FAILURE);
	}
	return buff;
}

void destroy_ipcs(t_ipcs *ipcs)
{
	bool is_error;

	is_error = false;
	if (destroy_shm((void **) &ipcs->shm_addr, SHM_MAP_NAME, MAP_SIZE))
		is_error = true;
	if (destroy_sem(SEM_NAME))
		is_error = true;
	destroy_mq(MQ_NAME, TEAM_COUNT);
	if (is_error)
		exit(EXIT_FAILURE);
}
