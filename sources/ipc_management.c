#include "lem_ipc.h"
#include "ipc_management.h"

static void init_shm_map(char *shm_addr, const char filler)
{
	for (int x = 0; x < MAP_SIZE; x += MAP_X)
		for (int y = 0; y < MAP_X; ++y)
			*(shm_addr + (x + y)) = filler;
}

t_ipcs *create_ipcs(const int process_count)
{
	t_ipcs *ipcs;

	if (!(ipcs = malloc(sizeof(t_ipcs))))
	{
		perror("malloc_for_ipcs");
		exit(EXIT_FAILURE);
	}
	ipcs->shm_addr = get_shm(SHM_MAP_NAME, MAP_SIZE, process_count);
	if (process_count == 1)
		init_shm_map(ipcs->shm_addr, '.');
	ipcs->sem = get_sem(SEM_NAME, process_count);
	ipcs->mq = get_mq(MQ_NAME, process_count);
	return ipcs;
}

bool	close_ipcs(t_ipcs *ipcs)
{
	bool is_error;

	is_error = false;
	if (close_sem(&ipcs->sem))
		is_error = true;
	if (close_mq(ipcs->mq))
		is_error = true;
	return is_error;
}

void destroy_ipcs(t_ipcs *ipcs, const int process_count)
{
	bool is_error;

	if (process_count != 0)
		return;
	is_error = false;
	if (destroy_shm((void **) &ipcs->shm_addr, SHM_MAP_NAME, MAP_SIZE))
		is_error = true;
	if (destroy_sem(SEM_NAME))
		is_error = true;
	if (destroy_mq(MQ_NAME))
		is_error = true;
	if (is_error)
		exit(EXIT_FAILURE);
}
