#include "philo.h"

int     philo_dead(t_philo *philo)
{
        pthread_mutex_lock(philo->param->m_life);
        if (philo->param->state == DIED)
        {
                        pthread_mutex_unlock(philo->param->m_life);
                        return (1);
        }
        return (pthread_mutex_unlock(philo->param->m_life));
}

int     life_expectancy(t_philo **philo, t_arg **param)
{
        int     i;

        i = -1;
        while (++i < (*param)->nb_of_philo)
        {
                pthread_mutex_lock(philo[i]->m_eat);
                if (get_time() - philo[i]->last_eat > \
                philo[i]->param->time_to_die)
                {
                        pthread_mutex_lock(philo[i]->param->m_life);
                        philo[i]->param->state = DIED;
                        pthread_mutex_unlock(philo[i]->param->m_life);
                        pthread_mutex_lock(philo[i]->param->m_print);
                        printf("%lld %d \033[0;31mis died\033[m\n", \
                        get_time() - philo[i]->param->time_start, \
                        philo[i]->x);
                        pthread_mutex_unlock(philo[i]->param->m_print);
                        pthread_mutex_unlock(philo[i]->m_eat);
                        return (DIED);
                }
                pthread_mutex_unlock(philo[i]->m_eat);
        }
        return (0);
}


