#include "philo.h"

int	print_state(t_philo *philo, int state)
{
	long long int	time;

	pthread_mutex_lock(philo->param->m_print);
	if (philo_dead(philo))
		return (pthread_mutex_unlock(philo->param->m_print));
	time = philo->param->time_start;
	if (state == THINKING)
		printf("%lld %d is thinking", \
			get_time() - time, philo->x);
	else if (state == FORK)
		printf("%lld %d has taken a fork", \
			get_time() - time, philo->x);
	else if (state == EATING)
		printf("%lld %d is eating", \
			get_time() - time, philo->x);
	else if (state == SLEEPING)
		printf("%lld %d is sleeping", \
			get_time() - time, philo->x);
	printf("\n");
	pthread_mutex_unlock(philo->param->m_print);
	return (TRUE);
}
