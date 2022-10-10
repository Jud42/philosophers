/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamison <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 10:12:16 by rmamison          #+#    #+#             */
/*   Updated: 2022/10/04 17:40:11 by rmamison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

void	put_fork(t_philo **philo)
{
	int	i;
	int	nb;

	nb = (*philo)->param->nb_of_philo;
	i = (*philo)->x - 1;
	if (!(*(*philo)->fork_left))
	{
		*(*philo)->fork_left = 1;
		pthread_mutex_unlock(&(*philo)->param->m_fork[(i + 1) % nb]);
	}
	if (!(*(*philo)->fork_right))
	{
		*(*philo)->fork_right = 1;
		pthread_mutex_unlock(&(*philo)->param->m_fork[i]);
	}
}

static int	take_fork(t_philo *philo)
{	
	int	nb;
	int	i;

	nb = philo->param->nb_of_philo;
	if (nb == 1)
		return (1);
	i = philo->x - 1;
	pthread_mutex_lock(&philo->param->m_fork[i]);
	*philo->fork_right = 0;
	pthread_mutex_lock(&philo->param->m_fork[(i + 1) % nb]);
	*philo->fork_left = 0;
	print_state(philo, FORK);
	return (0);
}

void	think(t_philo *philo)
{
	if (!print_state(philo, THINKING))
		return ;
	while (take_fork(philo) && !philo_dead(philo))
		;
}

void	eat(t_philo *philo)
{
	int	nb;

	if (philo_dead(philo))
	{
		put_fork(&philo);
		return ;
	}
	nb = philo->param->nb_of_philo;
	print_state(philo, EATING);
	pthread_mutex_lock(philo->m_eat);
	philo->last_eat = get_time();
	pthread_mutex_unlock(philo->m_eat);
	usleep(philo->param->time_to_eat * 1000);
	philo->nb_eat++;
	put_fork(&philo);
}

void	sleep_philo(t_philo *philo)
{
	if (philo->param->nb_each_philo_eat && \
	philo->param->nb_each_philo_eat == philo->nb_eat)
		return ;
	if(!print_state(philo, SLEEPING))
		return ;
	usleep(philo->param->time_to_sleep * 1000);
}
