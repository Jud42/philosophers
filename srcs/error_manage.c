/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manage.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamison <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 15:11:44 by rmamison          #+#    #+#             */
/*   Updated: 2022/10/12 16:13:35 by rmamison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	msg_error(const char *s)
{
	write(2, s, ft_strlen(s));
	return (1);
}

int	error_input_exist(int ac, char **av)
{
	int	i;
	int	j;

	if (ac != 5 && ac != 6)
		return (msg_error("philo: missing argument\n"));
	i = 0;
	while (av[++i])
	{
		j = -1;
		while (av[i][++j])
			if (ft_digit(av[i][j]))
				return (msg_error("error: input\n"));
		if (ft_atoi(av[1]) <= 0)
			return (msg_error("error: 1 philosopher minimum\n"));
	}
	return (0);
}
