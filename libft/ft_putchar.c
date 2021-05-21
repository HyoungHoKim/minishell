#include "libft.h"
#include <stdlib.h>

int			ft_putchar(int c)
{
	write(STDOUT_FILENO, &c, 1);
	return (EXIT_SUCCESS);
}
