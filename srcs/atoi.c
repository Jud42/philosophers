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
void	msg_error(const char *s, t_arg *param)
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
		*str++;
	if (*str == '+' || *str == '-')
		if (*str++ == '-')
			negative = -1;
	while (*str && *str >= 48 && *str <= 57)
		ret = ret * 10 + (*str++ - '0');
	return (ret * negative);	
}

void	init_arg(t_arg **param, char **av)
{
	*param = malloc(sizeof(t_arg));
	if (*param == NULL)
		msg_error("error: malloc()\n", NULL);
	(*param)->nb_of_philo = ft_atoi(av[1]);
	(*param)->time_to_die = ft_atoi(av[2]);
	(*param)->time_to_eat = ft_atoi(av[3]);
	(*param)->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		(*param)->nb_each_philo_eat = ft_atoi(av[5]);
	else
		(*param)->nb_each_philo_eat = 0;
	(*param)->thread = malloc(sizeof(pthread_t) * \
	(*param)->nb_of_philo);
	if (!(*param)->thread)
		msg_error("error: malloc()\n", *param);	
	(*param)->mutex = malloc(sizeof(pthread_mutex_t) * \
	(*param)->nb_of_philo);
	if (!(*param)->mutex)
		msg_error("error: malloc()\n", *param);	
	(*param)->last_eat = malloc(sizeof(long long int) * (*param)->nb_of_philo);
	if (!(*param)->last_eat)
		msg_error("error: malloc()\n", *param);	
	if (!gettimeofday(&(*param)->time, NULL))
		(*param)->time_start = (*param)->time.tv_usec;
}

void	init_and_destroy_mutex(t_arg **param, int flag)
{
	int	i;

	i = -1;
	if (flag == INIT)
	{
		while (++i < (*param)->nb_of_philo)
			if (pthread_mutex_init(&(*param)->mutex[i], NULL))
				msg_error("error: INIT mutex\n", *param);
	}
	else if (flag == DESTROY)
	{	
		free((*param)->thread);
		while (++i < (*param)->nb_of_philo)
		{
			if (pthread_mutex_destroy(&(*param)->mutex[i]) != 0)
				msg_error("error: DESTROY mutex\n", *param);
		}
		free((*param)->mutex);
	}
}
