#include <unistd.h>
#include "logger.h"

int	get_log_file_size(void)
{
	return (256 * getpagesize());
}

