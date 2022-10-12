/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamison <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 13:57:30 by rmamison          #+#    #+#             */
/*   Updated: 2022/10/12 15:55:46 by rmamison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdatomic.h>
# include <sys/time.h>
# include <sys/wait.h>

# define TRUE 1
# define FORK 2
# define EATING 3
# define SLEEPING 4
# define THINKING 5
# define DIED 6
# define INIT 7
# define DESTROY 8

typedef struct s_philo{
	int					x;
	int					nb_eat;
	long long int		last_eat;
	pthread_mutex_t		*m_eat;
	pthread_mutex_t		*m_fork_left;
	pthread_mutex_t		*m_fork_right;
	struct s_arg		*param;
}	t_philo;

typedef struct s_arg{
	int				nb_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_each_philo_eat;
	int				end;
	int				died;
	int				*fork_on_table;
	long long int	time_start;
	pthread_t		*thread;
	pthread_mutex_t	*m_print;
	pthread_mutex_t	*m_fork;
	pthread_mutex_t	*m_life;
}	t_arg;

	/*----------ERROR-MANAGE-----------*/
int				msg_error(const char *s);
int				error_input_exist(int ac, char **av);
	/*------------INIT-----------*/
int				init_arg(t_arg **param, char **av);
int				init_philo(t_philo **philo, t_arg **param, int *j);
int				init_destroy_mutex(pthread_mutex_t **mut, int nb, int flag);
int				create_ptr_philo(t_philo ***ptr_philo, t_arg **param);
	/*---ROUTINE-PHILO---*/
void			eat(t_philo *philo);
void			sleep_philo(t_philo *philo);	
void			think(t_philo *philo);	
int				print_state(t_philo *philo, int state);
	/*----MAIN------*/
int				create_thread(t_arg **param);
void			*philosophers(void *arg);
	/*---UTILS---*/
int				ft_atoi(const char *str);
int				ft_strlen(const char *s);
int				ft_digit(int c);	
long long int	get_time(void);
	/*-------*/
void			clean_arg(t_arg **param);
void			clean_philo(t_philo ***philo, int nb);
void			life_expectancy(t_philo **tmp_philo, t_arg **param);
int				philo_dead(t_philo *philo);
void			ft_usleep(long time);
#endif
