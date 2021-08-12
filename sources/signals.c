#include "lem_ipc.h"

bool check_interrupt_flag()
{
	printf("Check Interrupt flag: %d\n", interrupt_flag);
	fflush(stdout);
	write(STDOUT_FILENO, "check_interrupt\0\n", 17);
	if (interrupt_flag)
	{
		write(STDOUT_FILENO, "check_interrupt: OK\0\n", 21);
		interrupt_flag = 0;
		return true;
	}
	return false;
}

void delete_handler(__attribute__((unused))int sig_no)
{
	install_disposition();
	interrupt_flag = 1;
	printf("Handler Interrupt flag: %d\n", interrupt_flag);
	fflush(stdout);
}

void install_disposition(void)
{
	signal(SIGINT, delete_handler);
}
