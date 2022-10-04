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
int	life_expectancy(t_philo *philo);

int	philo_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->param->tmp);
	if (philo->param->end == DIED)
	{
			pthread_mutex_unlock(philo->param->tmp);
			return (1);
	}
	return (pthread_mutex_unlock(philo->param->tmp));
}

void	put_fork(t_philo *philo)
{
	int	i;
	int	nb;

	nb = philo->param->nb_of_philo;
	i = philo->x - 1;
	if (*philo->fork_left == philo->x)
	{
		pthread_mutex_lock(&philo->param->fork[i]);
		*philo->fork_left = 0;
		pthread_mutex_unlock(&philo->param->fork[i]);
	}
	if (*philo->fork_right == philo->x)
	{
		pthread_mutex_lock(&philo->param->fork[(i + 1) % nb]);
		*philo->fork_right = 0;
		pthread_mutex_unlock(&philo->param->fork[(i + 1) % nb]);
	}
}

static int	take_fork(t_philo *philo)
{	
	int	nb;
	int	i;

	if (philo_dead(philo))
		return (1);
	nb = philo->param->nb_of_philo;
	i = philo->x - 1;
	if ( nb != 1 && !(*philo->fork_left) && !(*philo->fork_right))
	{
		pthread_mutex_lock(&philo->param->fork[i]);
		*philo->fork_right = philo->x;
		pthread_mutex_unlock(&philo->param->fork[i]);
		pthread_mutex_lock(&philo->param->fork[(i + 1) % nb]);
		*philo->fork_left = philo->x;
		print_state(philo, FORK);
		pthread_mutex_unlock(&philo->param->fork[(i + 1) % nb]);
		return (1);
	}
	return (0);
}

int	life_expectancy(t_philo *philo)
{	
	long long int	time_current;
	
	pthread_mutex_lock(philo->param->tmp);
	if (philo->param->end == DIED)
	{
		pthread_mutex_unlock(philo->param->tmp);
		return (DIED);
	}
	time_current = get_time();
	time_current = time_current - philo->last_eat;
	if (time_current > philo->param->time_to_die)
	{
		//pthread_mutex_lock(philo->param->print);
		philo->param->end = DIED;
		printf("%lld %d \033[0;31mis died\033[m\n", \
		//pthread_mutex_unlock(philo->param->print);
		get_time() - philo->param->time_start, philo->x);	
		pthread_mutex_unlock(philo->param->tmp);
		return (DIED);
	}
	pthread_mutex_unlock(philo->param->tmp);
	return (0);
}

void	think(t_philo *philo)
{
	if (!print_state(philo, THINKING))
		return ;
	while (!take_fork(philo))
		;
}

void	eat(t_philo *philo)
{
	int	nb;

	if (philo_dead(philo))
		return ;
	nb = philo->param->nb_of_philo;
	pthread_mutex_lock(philo->lets_eat);
	if (life_expectancy(philo) == DIED)
	{
		pthread_mutex_unlock(philo->lets_eat);
		return ;
	}
	philo->last_eat = get_time();
	print_state(philo, EATING);
	usleep(philo->param->time_to_eat * 1000);
	pthread_mutex_unlock(philo->lets_eat);
	philo->nb_eat++;
	put_fork(philo);
}

void	sleep_philo(t_philo *philo)
{
	if(!print_state(philo, SLEEPING))
		return ;
	usleep(philo->param->time_to_sleep * 1000);
}
