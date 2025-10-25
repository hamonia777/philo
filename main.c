/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwpark <jinwpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 06:03:48 by jinwpark          #+#    #+#             */
/*   Updated: 2025/10/25 09:49:20 by jinwpark         ###   ########.fr       */
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

static void	cleanup_on_error(t_info *info)
{
	if (info->forks)
		free(info->forks);
	if (info->philos)
		free(info->philos);
	if (info->lock)
	{
		pthread_mutex_destroy(info->lock);
		free(info->lock);
	}
	if (info->dead_mutex)
	{
		pthread_mutex_destroy(info->dead_mutex);
		free(info->dead_mutex);
	}
	if (info->meal_mutex)
	{
		pthread_mutex_destroy(info->meal_mutex);
		free(info->meal_mutex);
	}
	free(info);
}

static int	init_and_validate(t_info **info, char **argv, int argc)
{
	*info = malloc(sizeof(t_info));
	if (!*info)
		return (1);
	if (info_init(*info, argv, argc))
	{
		printf("error : wrong arg\n");
		cleanup_on_error(*info);
		return (1);
	}
	if (philo_init(*info))
	{
		cleanup_on_error(*info);
		return (1);
	}
	return (0);
}

static void	init_start_time(t_info *info)
{
	int	i;

	i = 0;
	info->start_time = get_time();
	while (i < info->philo_num)
		info->philos[i++].last_time = info->start_time;
}

int	main(int argc, char **argv)
{
	t_info	*info;

	if (argc != 5 && argc != 6)
	{
		printf("error : wrong arg\n");
		return (1);
	}
	if (init_and_validate(&info, argv, argc))
		return (1);
	init_start_time(info);
	philo_start(info);
	philo_cleanup(info);
	return (0);
}
