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
	*param = malloc(sizeof(t_arg));
	if (*param == NULL)
	{
		msg_error("error: malloc()\n");
		return(1);
	}
	(*param)->nb_of_philo = ft_atoi(av[1]);
	if (malloc_thread(&(*param)->thread, ft_atoi(av[1])))
		return (1);
	(*param)->fork_atom = malloc(sizeof(atomic_int) * ft_atoi(av[1]));		
	int i = -1;//temp
	while (ft_atoi(av[1]) > ++i)//temp
		(*param)->fork_atom[i] = 0;	
	(*param)->time_to_die = ft_atoi(av[2]);
	(*param)->time_to_eat = ft_atoi(av[3]);
	(*param)->time_to_sleep = ft_atoi(av[4]);
	(*param)->nb_each_philo_eat = 0;
	(*param)->fork = NULL;
	(*param)->print = NULL;
	(*param)->tmp = NULL;
	if (av[5])
		(*param)->nb_each_philo_eat = ft_atoi(av[5]);
	(*param)->end = 0;
	return (0);
}

int	init_philo(t_philo **philo, t_arg **param, int *j)
{
	*philo = malloc(sizeof(t_philo));
	if (*philo == NULL)
		return (msg_error("error: malloc()\n"));
    (*philo)->x = *j + 1;
	(*philo)->state = 0;
	(*philo)->nb_eat = 0;
	(*philo)->fork_right = &(*param)->fork_atom[*j];
	(*philo)->fork_left = &(*param)->fork_atom[(*j + 1) % (*param)->nb_of_philo];
	(*philo)->last_eat = 0;
	if (init_destroy_mutex(&(*philo)->lets_eat, 1, INIT))
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
