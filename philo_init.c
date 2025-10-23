/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwpark <jinwpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 06:04:37 by jinwpark          #+#    #+#             */
/*   Updated: 2025/10/24 07:04:29 by jinwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	info_init(t_info *info, char **argv, int argc)
{
	info->philo_num = ft_atoi(argv[1]);
	info->time_die = ft_atoi(argv[2]);
	info->time_eat = ft_atoi(argv[3]);
	info->time_sleep = ft_atoi(argv[4]);
	info->is_end = 0;
	info->philos = malloc(sizeof(t_philo) * info->philo_num);
	info->forks = malloc(sizeof(pthread_mutex_t) * info->philo_num);
	info->lock = malloc(sizeof(pthread_mutex_t));
	info->meal_mutex = malloc(sizeof(pthread_mutex_t));
	info->dead_mutex = malloc(sizeof(pthread_mutex_t));
	if (!info->philos || !info->forks || !info->lock || !info->dead_mutex
		|| !info->meal_mutex)
		return (1);
	if (pthread_mutex_init(info->lock, NULL) != 0
		|| pthread_mutex_init(info->dead_mutex, NULL) != 0
		|| pthread_mutex_init(info->meal_mutex, NULL) != 0)
		return (1);
	if (argc == 6)
		info->must_eat = ft_atoi(argv[5]);
	else
		info->must_eat = -1;
	if (info->philo_num <= 0 || info->time_die <= 0 || info->time_eat <= 0
		|| info->time_sleep <= 0)
		return (1);
	return (0);
}

int	philo_init(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->philo_num)
	{
		if (pthread_mutex_init(&info->forks[i], NULL) != 0)
			return (1);
		info->philos[i].id = i + 1;
		info->philos[i].eat_count = 0;
		info->philos[i].info = info;
		info->philos[i].left_fork = &info->forks[i];
		info->philos[i].right_fork = &info->forks[(i + 1) % info->philo_num];
		i++;
	}
	return (0);
}
