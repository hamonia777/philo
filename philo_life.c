/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwpark <jinwpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 06:03:59 by jinwpark          #+#    #+#             */
/*   Updated: 2025/10/24 08:43:00 by jinwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_lifetime(void *arg)
{
	t_philo	*philo;
	int		break_flag;

	break_flag = 0;
	philo = (t_philo *)arg;
	while (get_time() < philo->info->start_time)
		usleep(100);
	if (philo->id % 2 == 0)
		ft_usleep(philo->info->time_eat / 2, philo);
	while (1)
	{
		pthread_mutex_lock(philo->info->lock);
		if (philo->info->is_end || (philo->info->must_eat != -1
				&& philo->eat_count >= philo->info->must_eat))
			break_flag = 1;
		pthread_mutex_unlock(philo->info->lock);
		if (break_flag == 1)
			break ;
		else
		{
			philo_eat(philo);
			philo_sleep(philo);
			philo_think(philo);
		}
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
