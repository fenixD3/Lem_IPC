#include "lem_ipc.h"
#include <signal.h>

void delete_handler(__attribute__((unused))int sig_no)
{
	install_disposition();
	char *process_cnt_file;

	get_or_create_mapped_file(FILE_PROCESS_NAME, sizeof(int), (void **)&process_cnt_file);
	if (*process_cnt_file == 1)
	{
		shm_unlink(SHM_MAP_NAME);
		sem_unlink(SEM_NAME);
		for (int i = 1; i <= TEAM_COUNT; ++i)
		{
			char mq_name[32] = {'\0'};
			sprintf(mq_name, "%s%s%d", MQ_NAME, "_", i);
			mq_unlink(mq_name);
		}
		unlink(FILE_PROCESS_NAME);
	}
	exit(EXIT_SUCCESS);
}

void install_disposition(void)
{
	signal(SIGINT, delete_handler);
}
