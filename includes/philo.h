/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamison <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 13:57:30 by rmamison          #+#    #+#             */
/*   Updated: 2022/09/20 16:39:21 by rmamison         ###   ########.fr       */
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
#define EAT 1
#define SLEEP 2
#define THINK 3

#define INIT 4
#define DESTROY 5

typedef struct s_philo{
	int	x;
	struct	s_arg *param;
}	t_philo;


typedef struct s_arg{
int			nb_of_philo;
int			time_to_die;
int			time_to_eat;
int			time_to_sleep; 
int			nb_each_philo_eat; //argv optionnel
int			oldtime;
int			*x;
struct timeval		time;
long long int		time_start;
long long int		last_eat;
pthread_t		*thread;
pthread_mutex_t		*mutex;
}	t_arg;

/*------------*/
void	msg_error(const char *s, t_arg *param);
int	ft_atoi(const char *str);
void	init_arg(t_arg **param, char **av);
void	init_and_destroy_mutex(t_arg **param, int flag);
//nb of philo = nb of thread = nb fourchette

#endif
