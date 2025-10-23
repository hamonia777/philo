/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwpark <jinwpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 06:03:48 by jinwpark          #+#    #+#             */
/*   Updated: 2025/10/24 08:27:08 by jinwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_cleanup(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->philo_num)
	{
		pthread_mutex_destroy(&info->forks[i]);
		i++;
	}
	pthread_mutex_destroy(info->lock);
	pthread_mutex_destroy(info->meal_mutex);
	pthread_mutex_destroy(info->dead_mutex);
	free(info->forks);
	free(info->philos);
	free(info->lock);
	free(info->dead_mutex);
	free(info->meal_mutex);
	free(info);
}

int	main(int argc, char **argv)
{
	int		i;
	t_info	*info;

	i = 0;
	if (argc != 5 && argc != 6)
	{
		printf("error : wrong arg");
		return (1);
	}
	info = malloc(sizeof(t_info));
	if (!info)
		return (1);
	if (info_init(info, argv, argc))
	{
		printf("error : wrong arg");
		return (1);
	}
	if (philo_init(info))
		return (1);
	info->start_time = get_time();
	while (i < info->philo_num)
		info->philos[i++].last_time = info->start_time;
	philo_start(info);
	philo_cleanup(info);
	return (0);
}
