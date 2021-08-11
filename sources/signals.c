#include "lem_ipc.h"

void check_interrupt_flag()
{
	write(STDOUT_FILENO, "check_interrupt\0", 16);
	if (interrupt_flag)
	{
		write(STDOUT_FILENO, "check_interrupt: OK\0", 20);
		interrupt_flag = 0;
		return;
	}
}

void delete_handler(__attribute__((unused))int sig_no)
{
	install_disposition();
	interrupt_flag = 1;
//	write(STDOUT_FILENO, "Caught!", 8);
//	char *process_cnt_file;
//
//	get_or_create_mapped_file(FILE_PROCESS_NAME, sizeof(int), (void **)&process_cnt_file);
//	if (*process_cnt_file == 1)
//	{
//		shm_unlink(SHM_MAP_NAME);
//		sem_unlink(SEM_NAME);
//		for (int i = 1; i <= TEAM_COUNT; ++i)
//		{
//			char mq_name[32] = {'\0'};
//			sprintf(mq_name, "%s%s%d", MQ_NAME, "_", i);
//			mq_unlink(mq_name);
//		}
//		unlink(FILE_PROCESS_NAME);
//	}
//	exit(EXIT_SUCCESS);
}

void install_disposition(void)
{
	signal(SIGINT, delete_handler);
}
