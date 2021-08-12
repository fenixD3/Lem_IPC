#include "lem_ipc.h"

bool check_interrupt_flag()
{
	if (g_interrupt_flag)
	{
		g_interrupt_flag = 0;
		return true;
	}
	return false;
}

void delete_handler(__attribute__((unused))int sig_no)
{
	install_disposition();
	g_interrupt_flag = 1;
}

void install_disposition(void)
{
	signal(SIGINT, delete_handler);
}
