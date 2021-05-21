#include "lem-ipc.h"
#include <sys/mman.h>
#include <fcntl.h>

void create_shm(void)
{
	int shm;

	shm = shm_open(SHM_MAP_NAME, O_CREAT | O_RDWR | O_EXCL, 0777);
}
