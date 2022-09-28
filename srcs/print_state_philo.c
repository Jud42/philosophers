#include "philo.h"

void	print_state(t_philo *philo)
{
	long long int time;

	time = get_time(philo);
	if (philo->state == FORK)
		printf("%lld %d has taken a fork", time, philo->x + 1);
	else if (philo->state == EATING)
		printf("%lld %d is eating", time, philo->x + 1);
	else if (philo->state == SLEEPING)
		printf("%lld %d is sleeping", time, philo->x + 1);
	else if (philo->state == THINKING)
		printf("%lld %d is thinking", time, philo->x + 1);
	printf("\n");
}
