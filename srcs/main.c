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

static void check_up(t_philo ***tm_philo, t_arg **param)
{
	int	j;
	t_philo **philo;

	philo = *tm_philo;
	j = 0;
	usleep((*param)->time_to_eat * 1000);
	while (!(*param)->end)
	{
		if (j == (*param)->nb_of_philo)
			j %= (*param)->nb_of_philo;
		if (life_expectancy(philo[j]))
		{
			put_fork(philo[j]);
			break ;
		}
	}
	free(philo);
}

static int	create_ptr_philo(t_philo ***ptr_philo, t_arg **param)
{
	*ptr_philo = malloc(sizeof(t_philo *) * (*param)->nb_of_philo);
	if (!ptr_philo)
		return (1);
	return (0);
}

static int      join_thread(t_arg **param)
{
        int     j;

        j = -1;
        while(++j < (*param)->nb_of_philo)
        {
                if (pthread_join((*param)->thread[j], NULL))
                        return (msg_error("error: pthread_join\n"));
        }
        init_destroy_mutex(&(*param)->fork, (*param)->nb_of_philo, DESTROY);
        init_destroy_mutex(&(*param)->print, 1, DESTROY);
        init_destroy_mutex(&(*param)->tmp, 1, DESTROY);
        return (0);
}

void	*philosophers(void *arg)
{
	static int i = 0;
	t_philo	*philo;

	philo = (t_philo *)arg;
	if ((philo->x + 1) % 2 == 0)
		usleep(philo->param->time_to_eat * 1000);
	pthread_mutex_lock(philo->param->tmp);
	philo->last_eat = get_time();
	pthread_mutex_unlock(philo->param->tmp);
	while (1)
	{
		think(philo);
		eat(philo);
		sleep_philo(philo);
		if (philo->param->end == DIED || \
		philo->param->nb_each_philo_eat && \
		philo->nb_eat == philo->param->nb_each_philo_eat)
			break ;
	}
	free(philo);
	return (NULL);
}

int     create_thread(t_arg **param)
{
        int     j;
        int     nb;
        t_philo *philo;
	t_philo **ptr_philo;

        j = -1;
        nb = (*param)->nb_of_philo;
	if (create_ptr_philo(&ptr_philo, param))
		return (1);
        init_destroy_mutex(&(*param)->fork, nb, INIT);
        init_destroy_mutex(&(*param)->print, 1, INIT);
        init_destroy_mutex(&(*param)->tmp, 1, INIT);
        (*param)->time_start = get_time();
        while(++j < nb)
        {
                if (init_philo(&philo, param, &j))
                        return (1);
		ptr_philo[j] = philo;
                if (pthread_create(&(*param)->thread[j], NULL, \
                &philosophers, (void *)philo))
                        return (msg_error("error: pthread_create\n"));
        }
	check_up(&ptr_philo, param);
        return (join_thread(param));
}


int	main(int argc, char *argv[])
{
	t_arg	*param;

	param = NULL;
	if (error_input_exist(argc, argv))
		return (1);
	init_arg(&param, argv);
	if (create_thread(&param))
	{
		free_all(&param);
		return (1);
	}
	free_all(&param);
	return (0);
}
