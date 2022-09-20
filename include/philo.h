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

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include <pthread.h>

typedef struct s_philo{
int	nb_of_philo;
int	time_to_die;
int	time_to_eat;
int	tim_to_sleep; 
int	nb_of_each_philo_must_eat; //argv optionnel

}	t_philo;

//nb of philo = nb of thread = nb fourchette

#endif
