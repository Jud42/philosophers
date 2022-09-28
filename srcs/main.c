/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamison <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 13:51:13 by rmamison          #+#    #+#             */
/*   Updated: 2022/09/28 18:19:36 by rmamison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

void	*routine(void *arg)
{
	t_philo	*philo;
		
	philo = (t_philo *)arg;

	while (1)
	{
		//check if i can take a fork
		pthread_mutex_lock(&philo->param->fork[(*philo).x]);
		pthread_mutex_lock(&philo->param->fork[((*philo).x + 1) % philo->param->nb_of_philo]);
		eat(philo);
		pthread_mutex_unlock(&philo->param->fork[((*philo).x + 1) % philo->param->nb_of_philo]);
		pthread_mutex_unlock(&philo->param->fork[(*philo).x]);
		//sleep_philo(philo);
		//think(philo);
		if (died(philo))
			break ;
	}
	free(philo);
	return (NULL);
}

int	main(int argc, char *argv[])
{
	int		j;
	t_arg	*param;
	t_philo	*philo;
	
	param = NULL;
	j = -1;
	check_error_input(argc, argv);
	init_arg(&param, argv);
	init_and_destroy_mutex(&param, INIT);
	while(++j < param->nb_of_philo)
	{
		philo = malloc(sizeof(struct s_philo));
		philo->x = j;
		philo->state = 0;
		philo->param = param;
		if (pthread_create(&param->thread[j], NULL, \
					&routine,(void *)philo))
			msg_error("error: pthread_create\n", philo);
		usleep(1000);
	}
	j = -1;
	while(++j < param->nb_of_philo)
	{
		if (pthread_join(param->thread[j], NULL))//(void**)&ret2) != 0)
			msg_error("error: pthread_join\n", philo);
	}
	init_and_destroy_mutex(&param, DESTROY);
//	free(philo);
	free(param->last_eat);
	free(param);
//	printf("%d\n", i);
//	gettimeofday(&time, NULL);
//	printf("time ===> %d\n, %d", time.tv_sec, time.tv_usec);
	return (0);
}
