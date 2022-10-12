/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamison <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 15:30:51 by rmamison          #+#    #+#             */
/*   Updated: 2022/10/12 16:48:20 by rmamison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

int	ft_strlen(const char *s)
{
	int	i;

	if (!*s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_digit(int c)
{
	if (c >= 48 && c <= 57)
		return (0);
	return (!0);
}

int	ft_atoi(const char *str)
{
	int	ret;
	int	negative;

	ret = 0;
	negative = 1;
	while (*str && *str == ' ' || *str == '\t' || *str == '\r')
		str++;
	if (*str == '+' || *str == '-')
		if (*str++ == '-')
			negative = -1;
	while (*str && *str >= 48 && *str <= 57)
		ret = ret * 10 + (*str++ - '0');
	return (ret * negative);
}

long long int	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) != 0)
		return (msg_error("error: gettimeofday()\n"));
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_usleep(long time)
{
	long int	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(time / 10);
}
