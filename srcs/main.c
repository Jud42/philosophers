/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamison <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 13:51:13 by rmamison          #+#    #+#             */
/*   Updated: 2022/10/12 18:58:19 by rmamison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

static int	join_thread(t_arg **param, t_philo **philo)
{
	int	j;

	j = -1;
	while (++j < (*param)->nb_of_philo)
	{
		if (pthread_join((*param)->thread[j], NULL))
			return (msg_error("error: pthread_join\n"));
	}
	clean_philo(&philo, (*param)->nb_of_philo);
	init_destroy_mutex(&(*param)->m_fork, (*param)->nb_of_philo, DESTROY);
	init_destroy_mutex(&(*param)->m_print, 1, DESTROY);
	init_destroy_mutex(&(*param)->m_life, 1, DESTROY);
	return (0);
}

static void	check_up(t_philo **tm_philo, t_arg **param)
{
	int	nb;

	nb = (*param)->nb_of_philo;
	usleep((*param)->time_to_die / 2 * 1000);
	while ((*param)->died == 0 && (*param)->end != nb)
	{
		usleep(500);
		life_expectancy(tm_philo, param);
	}
	if ((*param)->nb_of_philo == 1)
		pthread_mutex_unlock(tm_philo[0]->m_fork_right);
}

void	*philosophers(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->x % 2 == 0)
		usleep(1000);
	philo->last_eat = get_time();
	while (1)
	{
		think(philo);
		eat(philo);
		sleep_philo(philo);
		if (philo->param->died || \
		philo->param->nb_each_philo_eat && \
		philo->nb_eat == philo->param->nb_each_philo_eat)
			break ;
	}
	if (philo->param->nb_each_philo_eat)
		philo->param->end++;
	return (NULL);
}

int	create_thread(t_arg **param)
{
	int		j;
	int		nb;
	t_philo	*philo;
	t_philo	**ptr_philo;

	nb = (*param)->nb_of_philo;
	if (create_ptr_philo(&ptr_philo, param))
		return (1);
	(*param)->time_start = get_time();
	j = -1;
	while (++j < nb)
	{
		if (init_philo(&philo, param, &j))
			return (1);
		ptr_philo[j] = philo;
		if (pthread_create(&(*param)->thread[j], NULL, \
		&philosophers, (void *)philo))
			return (msg_error("error: pthread_create\n"));
	}
	check_up(ptr_philo, param);
	return (join_thread(param, ptr_philo));
}

int	main(int argc, char *argv[])
{
	t_arg	*param;

	param = NULL;
	if (error_input_exist(argc, argv))
		return (1);
	if (init_arg(&param, argv))
	{
		clean_arg(&param);
		return (1);
	}
	if (create_thread(&param))
	{
		clean_arg(&param);
		return (1);
	}
	clean_arg(&param);
	return (0);
}
