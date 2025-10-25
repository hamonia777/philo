/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwpark <jinwpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 06:03:59 by jinwpark          #+#    #+#             */
/*   Updated: 2025/10/25 09:49:48 by jinwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_lifetime(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (get_time() < philo->info->start_time)
		usleep(100);
	pthread_mutex_lock(philo->info->lock);
	philo->last_time = philo->info->start_time;
	pthread_mutex_unlock(philo->info->lock);
	if (philo->id % 2 == 0)
		ft_usleep(philo->info->time_eat / 2, philo);
	while (1)
	{
		if (check_death(philo))
			break ;
		pthread_mutex_lock(philo->info->lock);
		if (philo->info->must_eat != -1
			&& philo->eat_count >= philo->info->must_eat)
		{
			pthread_mutex_unlock(philo->info->lock);
			break ;
		}
		pthread_mutex_unlock(philo->info->lock);
		philo_eat(philo);
		if (check_death(philo))
			break ;
		philo_sleep(philo);
		if (check_death(philo))
			break ;
		philo_think(philo);
	}
	return (NULL);
}

void	philo_start(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->philo_num)
	{
		if (pthread_create(&info->philos[i].thread, NULL, philo_lifetime,
				&info->philos[i]) != 0)
			return ;
		i++;
	}
	philo_monitor(info);
	i = 0;
	while (i < info->philo_num)
	{
		pthread_join(info->philos[i].thread, NULL);
		i++;
	}
}
