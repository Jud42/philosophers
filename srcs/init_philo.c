#include "philo.h"

void	check_error_input(int ac, char *av[])
{
	int	i;

	if (ac != 5 && ac != 6)
		msg_error("philo: missing argument\n", NULL);
	else if (ft_atoi(av[1]) <= 0)
		msg_error("error: 1 philosopher minimum\n", NULL);
	i = 0;
	while (av[++i])
		if (!ft_atoi(av[i]))
			msg_error("error: argument not numeric\n", NULL);
}

void	init_arg(t_arg **param, char **av)
{
	/*----malloc----*/
	*param = malloc(sizeof(t_arg));
	if (*param == NULL)
		msg_error("error: malloc()\n", NULL);
	/*----*/
	(*param)->nb_of_philo = ft_atoi(av[1]);
	(*param)->time_to_die = ft_atoi(av[2]);
	(*param)->time_to_eat = ft_atoi(av[3]);
	(*param)->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		(*param)->nb_each_philo_eat = ft_atoi(av[5]);
	else
		(*param)->nb_each_philo_eat = 0;
	/*----malloc----*/
	(*param)->thread = malloc(sizeof(pthread_t) * \
	(*param)->nb_of_philo);
	if (!(*param)->thread)
		msg_error("error: malloc()\n", NULL);	
	/*----*/
	(*param)->fork = malloc(sizeof(pthread_mutex_t) * \
	(*param)->nb_of_philo);
	if (!(*param)->fork)
		msg_error("error: malloc()\n", NULL);	
	/*----*/
	(*param)->last_eat = malloc(sizeof(long long int) * (*param)->nb_of_philo);
	if (!(*param)->last_eat)
		msg_error("error: malloc()\n", NULL);
	/*-------*/
	(*param)->time_start = malloc(sizeof(long long int) * (*param)->nb_of_philo);
	if (!(*param)->time_start)
		msg_error("error: malloc()\n", NULL);
	int i = 0;
	(*param)->time_start[i] = get_time(NULL);
	while (++i < (*param)->nb_of_philo)
		(*param)->time_start[i] = (*param)->time_start[i - 1]; 
	/*-----*/
}

void	init_and_destroy_mutex(t_arg **param, int flag)
{
	int	i;

	i = -1;
	if (flag == INIT)
	{
		while (++i < (*param)->nb_of_philo)
			if (pthread_mutex_init(&(*param)->fork[i], NULL))
				msg_error("error: INIT mutex\n", NULL);
	}
	else if (flag == DESTROY)
	{	
		free((*param)->thread);
		while (++i < (*param)->nb_of_philo)
		{
			if (pthread_mutex_destroy(&(*param)->fork[i]) != 0)
				msg_error("error: DESTROY mutex\n", NULL);
		}
		free((*param)->fork);
	}
}
