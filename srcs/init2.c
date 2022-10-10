#include "philo.h"

int     create_ptr_philo(t_philo ***ptr_philo, t_arg **param)
{
        *ptr_philo = malloc(sizeof(t_philo *) * (*param)->nb_of_philo);
        if (!ptr_philo)
                return (1);
        return (0);
}
