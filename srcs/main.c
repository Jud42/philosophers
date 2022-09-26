/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamison <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 13:51:13 by rmamison          #+#    #+#             */
/*   Updated: 2022/09/20 16:39:19 by rmamison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

void	*routine(void *arg)
{
	//int	index = -1;
	//static	int x = 0;
	//pthread_mutex_t mut = *(pthread_mutex_t *)arg;
	//int	*ret = malloc(sizeof(int));
	struct s_philo	*philo = (struct s_philo *)arg;
	printf("%d\n", (*philo).x + 1);
	//pthread_mutex_lock(&philo->param->mutex[(*philo).x]);
	//pthread_mutex_lock(&philo->param->mutex[((*philo).x + 1) % philo->param->nb_of_philo]);
	//printf("eat ==> %d\n", (*philo).x + 1);
	//usleep(10000);
	//pthread_mutex_unlock(&philo->param->mutex[((*philo).x + 1) % philo->param->nb_of_philo]);
	//pthread_mutex_unlock(&philo->param->mutex[(*philo).x]);
	//free(philo);
	return (NULL);
}

int	main(int argc, char *argv[])
{
	int	j;
	int	*ret;
	int	*ret2;
	struct timeval time;
	t_arg	*param;
	struct s_philo	*philo;
	
	param = NULL;
	if (argc != 5 && argc != 6)
		msg_error("philo: missing argument\n", NULL);
	else if (ft_atoi(argv[1]) <= 0)
		msg_error("missing philosophers: minimum 1 philo\n", NULL);
	j = -1;
	init_arg(&param, argv);
	init_and_destroy_mutex(&param, INIT);
	philo = malloc(sizeof(struct s_philo) * param->nb_of_philo);
	while(++j < param->nb_of_philo)
	{
		//philo = malloc(sizeof(struct s_philo));
		philo[j].x = j;
		philo[j].param = param;
		if (pthread_create(&param->thread[j], NULL, &routine,(void *)&philo[j]))
			msg_error("error: pthread_create\n", param);
		//free(philo->x);
		usleep(1000);
	}
	j = -1;
	while(++j < param->nb_of_philo)
	{
		if (pthread_join(param->thread[j], NULL))//(void**)&ret2) != 0)
			msg_error("error: pthread_join\n", param);
	}
	init_and_destroy_mutex(&param, DESTROY);
	free(philo);
	free(param);
//	printf("%d\n", i);
//	gettimeofday(&time, NULL);
//	printf("time ===> %d\n, %d", time.tv_sec, time.tv_usec);
	return (0);
}
