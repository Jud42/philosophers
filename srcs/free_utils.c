#include "philo.h"

void	clean_arg(t_arg **param)
{
	if ((*param)->m_print)
		free((*param)->m_print);
	if ((*param)->m_fork)
		free((*param)->m_fork);	
	if ((*param)->fork_on_table)
		free((*param)->fork_on_table);
	if ((*param)->m_life)
		free((*param)->m_life);
	if ((*param)->thread)
		free((*param)->thread);
	if (*param)
		free(*param);
}

void	clean_philo(t_philo ***philo, int nb)
{
	int	i;
	
	i = -1;
	while (++i < nb)
	{
		init_destroy_mutex(&((*philo)[i]->m_eat), 1, DESTROY);
		free((*philo)[i]->m_eat);
		free((*philo)[i]);
	}
	free(*philo);
}
