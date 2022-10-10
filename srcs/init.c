#include "philo.h"

int	init_destroy_mutex(pthread_mutex_t **mut, int nb, int flag);
static int	malloc_mutex(pthread_mutex_t **mut, int nb)
{
	*mut = malloc(sizeof(pthread_mutex_t) * nb);
	if (*mut == NULL)
		return (msg_error("error: malloc()\n"));	
	return (0);	
}


static int	malloc_thread(pthread_t **thread, int nb)
{
	*thread = malloc(sizeof(pthread_t) * nb);
	if (*thread == NULL)
		return (msg_error("error: malloc()\n"));
		
	return (0);	
}

int	init_arg(t_arg **param, char **av)
{
	int i;

	*param = malloc(sizeof(t_arg));
	if (*param == NULL)
		return(msg_error("error: malloc()\n"));
	if (malloc_thread(&(*param)->thread, ft_atoi(av[1])))
		return (1);
	(*param)->fork_on_table = malloc(sizeof(int) * ft_atoi(av[1]));
	if (!(*param)->fork_on_table)
		return(msg_error("error: malloc()\n"));
	(*param)->nb_of_philo = ft_atoi(av[1]);
	i = -1;
	while (++i < (*param)->nb_of_philo)
		(*param)->fork_on_table[i] = 1;	
	(*param)->time_to_die = ft_atoi(av[2]);
	(*param)->time_to_eat = ft_atoi(av[3]);
	(*param)->time_to_sleep = ft_atoi(av[4]);
	(*param)->nb_each_philo_eat = 0;
	if (av[5])
		(*param)->nb_each_philo_eat = ft_atoi(av[5]);
	(*param)->state = 0;
	(*param)->end = 0;
	return (0);
}

int	init_philo(t_philo **philo, t_arg **param, int *j)
{
	*philo = malloc(sizeof(t_philo));
	if (*philo == NULL)
		return (msg_error("error: malloc()\n"));
    	(*philo)->x = *j + 1;
	(*philo)->nb_eat = 0;
	(*philo)->fork_right = &(*param)->fork_on_table[*j];
	(*philo)->fork_left = &(*param)->fork_on_table[(*j + 1) \
	% (*param)->nb_of_philo];
	(*philo)->last_eat = 0;
	if (init_destroy_mutex(&(*philo)->m_eat, 1, INIT))
		return (1);
	(*philo)->param = *param;
	return (0);
}

int	init_destroy_mutex(pthread_mutex_t **mut, int nb, int flag)
{
	int	i;

	i = -1;
	if (flag == INIT)
	{
		if (malloc_mutex(mut, nb))
			return (1);
		while (++i < nb)
			if (pthread_mutex_init(&(*mut)[i], NULL))
				return (msg_error("error: INIT mutex\n"));
	}
	else if (flag == DESTROY)
	{
		while (++i < nb)
			if (pthread_mutex_destroy(&(*mut)[i]))
				return (msg_error("error: DESTROY mutex\n"));
	}
	return (0);
}
