/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamison <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 10:12:16 by rmamison          #+#    #+#             */
/*   Updated: 2022/10/12 17:04:39 by rmamison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

static void	put_fork(t_philo **philo)
{
	pthread_mutex_unlock((*philo)->m_fork_right);
	pthread_mutex_unlock((*philo)->m_fork_left);
}

static void	take_fork(t_philo **philo)
{	
	pthread_mutex_lock((*philo)->m_fork_right);
	if (!print_state(*philo, FORK))
	{
		pthread_mutex_unlock((*philo)->m_fork_right);
		return ;
	}
	pthread_mutex_lock((*philo)->m_fork_left);
	if (!print_state(*philo, FORK))
	{
		pthread_mutex_unlock((*philo)->m_fork_left);
		return ;
	}
}

void	think(t_philo *philo)
{
	if (!print_state(philo, THINKING))
		return ;
	take_fork(&philo);
}

void	eat(t_philo *philo)
{
	if (!print_state(philo, EATING))
	{
		put_fork(&philo);
		return ;
	}
	pthread_mutex_lock(philo->m_eat);
	philo->last_eat = get_time();
	pthread_mutex_unlock(philo->m_eat);
	ft_usleep(philo->param->time_to_eat);
	philo->nb_eat++;
	put_fork(&philo);
}

void	sleep_philo(t_philo *philo)
{
	if (!print_state(philo, SLEEPING))
		return ;
	ft_usleep(philo->param->time_to_sleep);
}
