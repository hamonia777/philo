/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwpark <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 09:47:16 by jinwpark          #+#    #+#             */
/*   Updated: 2025/10/25 09:47:18 by jinwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_philosopher_dead(t_philo *philo)
{
	long long	current_time;

	current_time = get_time();
	if ((current_time - philo->last_time) > philo->info->time_die)
	{
		philo->info->is_end = 1;
		printf("%lld %d died\n", current_time - philo->info->start_time,
			philo->id);
		return (1);
	}
	return (0);
}

static int	are_all_philos_full(t_info *info)
{
	int	i;
	int	full_philos_count;

	if (info->must_eat == -1)
		return (0);
	i = 0;
	full_philos_count = 0;
	while (i < info->philo_num)
	{
		pthread_mutex_lock(info->lock);
		if (info->philos[i].eat_count >= info->must_eat)
			full_philos_count++;
		pthread_mutex_unlock(info->lock);
		i++;
	}
	if (full_philos_count == info->philo_num)
	{
		pthread_mutex_lock(info->lock);
		info->is_end = 1;
		pthread_mutex_unlock(info->lock);
		return (1);
	}
	return (0);
}

void	philo_monitor(t_info *info)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < info->philo_num)
		{
			pthread_mutex_lock(info->lock);
			if (is_philosopher_dead(&info->philos[i]))
			{
				pthread_mutex_unlock(info->lock);
				return ;
			}
			pthread_mutex_unlock(info->lock);
			i++;
		}
		if (are_all_philos_full(info))
			return ;
		usleep(1000);
	}
}
