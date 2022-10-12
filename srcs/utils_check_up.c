/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_check_up.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamison <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 15:33:31 by rmamison          #+#    #+#             */
/*   Updated: 2022/10/12 18:58:50 by rmamison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->param->m_life);
	if (philo->param->died)
	{
		pthread_mutex_unlock(philo->param->m_life);
		return (1);
	}
	return (pthread_mutex_unlock(philo->param->m_life));
}

void	life_expectancy(t_philo **philo, t_arg **param)
{
	int	i;

	i = -1;
	while (++i < (*param)->nb_of_philo)
	{
		if ((*param)->nb_each_philo_eat && \
		philo[i]->nb_eat == (*param)->nb_each_philo_eat)
			continue ;
		pthread_mutex_lock(philo[i]->m_eat);
		if (get_time() - philo[i]->last_eat > philo[i]->param->time_to_die)
		{
			pthread_mutex_unlock(philo[i]->m_eat);
			pthread_mutex_lock((*param)->m_life);
			(*param)->died = 1;
			pthread_mutex_unlock((*param)->m_life);
			pthread_mutex_lock(philo[i]->param->m_print);
			printf("%lld %d \033[0;31mis died\033[m\n", \
			get_time() - (*param)->time_start, philo[i]->x);
			pthread_mutex_unlock((*param)->m_print);
			return ;
		}
		pthread_mutex_unlock(philo[i]->m_eat);
	}
}
