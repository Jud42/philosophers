/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamison <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 15:22:05 by rmamison          #+#    #+#             */
/*   Updated: 2022/10/12 15:23:09 by rmamison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_ptr_philo(t_philo ***ptr_philo, t_arg **param)
{
	*ptr_philo = malloc(sizeof(t_philo *) * (*param)->nb_of_philo);
	if (!ptr_philo)
		return (1);
	return (0);
}
