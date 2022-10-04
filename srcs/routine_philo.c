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
int	life_expectancy(t_philo *philo);

void	put_fork(t_philo *philo)
{
	if (philo->fork_left == 1)
	{
		pthread_mutex_unlock(&philo->param->fork[(philo->x + 1) \
		% philo->param->nb_of_philo]);
		philo->fork_left = 0;
	}
	if (philo->fork_right == 1)
	{
		pthread_mutex_unlock(&philo->param->fork[philo->x]);
		philo->fork_right = 0;
	}
}

static void	take_fork(t_philo *philo)
{
	while (!philo->fork_left && !philo->fork_right)
	{
		if (!pthread_mutex_lock(&philo->param->fork[philo->x]))
			philo->fork_right = 1;
		if (!pthread_mutex_lock(&philo->param->fork[(philo->x + 1) \
		% philo->param->nb_of_philo]))
		{
			philo->fork_left = 1;
		}
		if (philo->param->end == DIED)
		{
			put_fork(philo);
			break ;
		}
	}
}

int	life_expectancy(t_philo *philo)
{	
	long long int	time_current;
	
	pthread_mutex_lock(philo->param->print);
	if (philo->param->end == DIED)
	{
		pthread_mutex_unlock(philo->param->print);
		return (DIED);
	}
	time_current = get_time();
	time_current = time_current - philo->last_eat;
	if (time_current > philo->param->time_to_die)
	{
		philo->param->end = DIED;
		printf("%lld %d \033[0;31mis died\033[m\n", \
		get_time() - philo->param->time_start, philo->x + 1);	
		pthread_mutex_unlock(philo->param->print);
		return (DIED);
	}
	pthread_mutex_unlock(philo->param->print);
	return (0);
}

void	think(t_philo *philo)
{
	int	nb;

	if (!print_state(philo, THINKING))
		return ;
	nb = philo->param->nb_of_philo;
	take_fork(philo);
	print_state(philo, FORK);
	put_fork(philo);
}

void	eat(t_philo *philo)
{
	int	nb;

	if (philo->param->end == DIED)
		return ;
	nb = philo->param->nb_of_philo;
	pthread_mutex_lock(&philo->param->fork[philo->x]);
	pthread_mutex_lock(&philo->param->fork[(philo->x + 1) % nb]);
	if (life_expectancy(philo) == DIED)
	{
		pthread_mutex_unlock(&philo->param->fork[(philo->x + 1) \
		% nb]);
		pthread_mutex_unlock(&philo->param->fork[philo->x]);
		return ;
	}
	philo->last_eat = get_time();
	print_state(philo, EATING);
	pthread_mutex_unlock(&philo->param->fork[(philo->x + 1) % nb]);
	philo->fork_left = 0;
	usleep(philo->param->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->param->fork[philo->x]);
	philo->fork_right = 0;
	philo->nb_eat++;
}

void	sleep_philo(t_philo *philo)
{
	if (philo->param->end == DIED)
		return ;
	if(!print_state(philo, SLEEPING))
		return ;
	usleep(philo->param->time_to_sleep * 1000);
}
