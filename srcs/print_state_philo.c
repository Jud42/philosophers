#include "philo.h"

int	print_state(t_philo *philo, int state)
{
	long long int	time;
	int	x_temp;

	pthread_mutex_lock(philo->param->print);
	if (philo->param->end == DIED)
		return (pthread_mutex_unlock(philo->param->print));
	time = philo->param->time_start;
	x_temp = philo->x % philo->param->nb_of_philo + 1;
	if (state == THINKING)
		printf("%lld %d is thinking", \
			get_time() - time, x_temp);
	else if (state == FORK)
		printf("%lld %d has taken a fork", \
			get_time() - time, x_temp);
	else if (state == EATING)
		printf("%lld %d is eating", \
			get_time() - time, x_temp);
	else if (state == SLEEPING)
		printf("%lld %d is sleeping", \
			get_time() - time, x_temp);
	printf("\n");
	pthread_mutex_unlock(philo->param->print);
	return (TRUE);
}
