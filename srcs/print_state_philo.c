/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_state_philo.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamison <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 15:29:35 by rmamison          #+#    #+#             */
/*   Updated: 2022/10/12 15:29:47 by rmamison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_state(t_philo *philo, int state)
{
	long long int	time;

	pthread_mutex_lock(philo->param->m_print);
	if (philo_dead(philo))
		return (pthread_mutex_unlock(philo->param->m_print));
	time = philo->param->time_start;
	if (state == THINKING)
		printf("%lld\e[0;36m %d is thinking\e[m", \
			get_time() - time, philo->x);
	else if (state == FORK)
		printf("%lld\e[0;33m %d has taken a fork\e[m", \
			get_time() - time, philo->x);
	else if (state == EATING)
		printf("%lld\e[0;37m %d is eating\e[m", \
			get_time() - time, philo->x);
	else if (state == SLEEPING)
		printf("%lld\e[0;35m %d is sleeping\e[m", \
			get_time() - time, philo->x);
	printf("\n");
	pthread_mutex_unlock(philo->param->m_print);
	return (TRUE);
}
