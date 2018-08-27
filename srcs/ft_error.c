
#include "main.h"

int		ft_error(const char *str1, const char *str2, const char *str3)
{
	if (str1)
		ft_putstr(str1);
	if (str2)
		ft_putstr(str2);
	if (str3)
		ft_putstr(str3);
	ft_putchar('\n');
	return (-1);
}
