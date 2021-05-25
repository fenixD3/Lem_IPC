#include "lem_ipc.h"

void	create_ipcs(t_ipcs *ipcs)
{
	create_shm(ipcs);
	create_sem(ipcs);
	create_mq(ipcs);
}

void	close_ipcs(t_ipcs *ipcs)
{
	close_shm(ipcs);
	close_sem(ipcs);
	close_mq(ipcs);
}

int		get_shm_mmap_size(void)
{
	int page_size;

	page_size = getpagesize();
	return (((MAP_X * MAP_Y - 1) / page_size + 1) * page_size);
}
