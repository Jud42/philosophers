/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamison <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 10:12:16 by rmamison          #+#    #+#             */
/*   Updated: 2022/09/28 14:44:06 by rmamison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

long long int	get_time(t_philo *philo)
{
	struct	timeval	time;

	if (gettimeofday(&time, NULL) != 0)
		msg_error("error: gettimeofday()\n", philo);
	return (time.tv_usec);
}

void	eat(t_philo *philo)
{
	long long int time_current;

	time_current = get_time(philo);
	if (philo->param->time_start[philo->x])
	{
		time_current =	time_current - philo->param->time_start[philo->x]; 
		philo->param->time_start[philo->x] = 0;
	}
	else
		time_current = time_current - philo->param->last_eat[philo->x];
	if (time_current > philo->param->time_to_die)
	{
		philo->state = DIED;
		return ;
	}
	philo->state = FORK;
	print_state(philo);
	philo->state = EATING;
	philo->param->last_eat[philo->x] = get_time(philo);
	print_state(philo);
	usleep(philo->param->time_to_eat);
}

void	sleep_philo(t_philo *philo)
{
	if (philo->state == DIED)
		return ;
	philo->state = SLEEPING;
	usleep(philo->param->time_to_eat);
}

void	think(t_philo *philo)
{
	if (philo->state == DIED)
		return ;
	philo->state = THINKING;
	print_state(philo);
}

int	died(t_philo *philo)
{
	if (philo->state == DIED)
	{	
		print_state(philo);
		return (1);
	}
	return (0);
}
