#include "philo.h"

static int	ft_strlen(const char *s)
{
	int	i;

	if (!*s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	msg_error(const char *s, t_philo *philo)
{
	if (!s)
		return ;
	write(2, s, ft_strlen(s));
	exit (EXIT_FAILURE);
}

int	ft_atoi(const char *str)
{
	int	ret;
	int	negative;

	ret = 0;
	negative = 1;
	while (*str && *str == ' ' || *str == '\t' || *str == '\r')
		str++;
	if (*str == '+' || *str == '-')
		if (*str++ == '-')
			negative = -1;
	while (*str && *str >= 48 && *str <= 57)
		ret = ret * 10 + (*str++ - '0');
	return (ret * negative);	
}
