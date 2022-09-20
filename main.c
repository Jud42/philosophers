/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamison <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 13:51:13 by rmamison          #+#    #+#             */
/*   Updated: 2022/09/20 16:39:19 by rmamison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "include/philo.h"

int i = 0;

void	*routine()
{
	int	index = -1;
	while (++index < 10000000)
		i++;	
	printf("my pthread [%d]\n", i);
	return (NULL);
}

int	main(int argc, char *argv[])
{
	pthread_t	test[2];

	if (argc < 4)
	{
		printf("philo: missing argument\n");
		return (1);
	}
	int	i = -1;
	while(++i < 2)
	{
		if (pthread_create(&test[i], NULL, &routine, NULL) != 0)
		{
			printf("error: pthread_create\n");
			return (1);
		}
		pthread_join(test[i], NULL);
	}
	return (0);
}
