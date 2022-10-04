#include "philo.h"

void	free_all(t_arg **param)
{
	if ((*param)->print)
		free((*param)->print);
	if ((*param)->fork)
		free((*param)->fork);
	if ((*param)->tmp)
		free((*param)->tmp);
	if ((*param)->thread)
		free((*param)->thread);
	if (*param)
		free(*param);
}
