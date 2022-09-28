/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamison <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 13:57:30 by rmamison          #+#    #+#             */
/*   Updated: 2022/09/28 18:00:11 by rmamison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include <sys/wait.h>

#define FORK 0
#define EATING 1
#define SLEEPING 2
#define THINKING 3
#define DIED 4

#define INIT 5
#define DESTROY 6

typedef struct s_philo{
	int				x;
	int				state;
	struct	s_arg	*param;
}	t_philo;


typedef struct s_arg{
int				nb_of_philo;
int				time_to_die;
int				time_to_eat;
int				time_to_sleep; 
int				nb_each_philo_eat; //argv optionnel
long long int	*time_start;
long long int	*last_eat; //each philo
pthread_t		*thread;
pthread_mutex_t	*fork;
}	t_arg;

/*------------*/
void			msg_error(const char *s, t_philo *philo);
void			check_error_input(int ac, char **av);
int				ft_atoi(const char *str);
void			init_arg(t_arg **param, char **av);
void			init_and_destroy_mutex(t_arg **param, int flag);
long long int	get_time(t_philo *philo);
void			eat(t_philo *philo);
void			sleep_philo(t_philo *philo);	
void			think(t_philo *philo);	
int				died(t_philo *philo);	
void			print_state(t_philo *philo);

//nb of philo = nb of thread = nb fourchette

#endif
