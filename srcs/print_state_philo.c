#include "philo.h"

void	print_state(t_philo *philo)
{
	//timestamp = timestamp actuel en ms
	long long int time;

	//time = timeactual ms
	if (philo->state == FORK)
		printf("%ld %d has taken a fork", time, philo->x)
	else if (philo->state == EATING)
		printf("%ld %d is eating", time, philo->x)
	else if (philo->state == SLEEPING)
		printf("%ld %d is sleeping", time, philo->x)
	else if (philo->state == THINKING)
		printf("%ld %d is thinking", time, philo->x)
	else if (philo->state == DIED)
		printf("%ld %d is died", time, philo->x)
}
