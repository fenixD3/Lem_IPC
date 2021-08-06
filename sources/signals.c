#include "lem_ipc.h"
#include <signal.h>

void delete_handler(int sig_no)
{
	/// TODO организовать удаление процесса
}

void install_disposition(void)
{
	signal(SIGINT, delete_handler);
	signal(SIGTERM, delete_handler);
}

