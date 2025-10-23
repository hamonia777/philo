/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwpark <jinwpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 06:03:40 by jinwpark          #+#    #+#             */
/*   Updated: 2025/10/24 08:33:03 by jinwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork");
	}
	return (0);
}

void	philo_eat(t_philo *philo)
{
	if (take_forks(philo) != 0)
		return ;
	if (check_death(philo))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return ;
	}
	if (philo->eat_count < philo->info->must_eat || philo->info->must_eat == -1)
	{
		pthread_mutex_lock(philo->info->lock);
		philo->last_time = get_time();
		if (philo->info->is_end == 0)
		{
			printf("%lld %d is eating\n", philo->last_time
				- philo->info->start_time, philo->id);
			philo->eat_count++;
		}
		pthread_mutex_unlock(philo->info->lock);
		ft_usleep(philo->info->time_eat, philo);
	}
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	philo_sleep(t_philo *philo)
{
	if (check_death(philo))
		return ;
	print_status(philo, "is sleeping");
	ft_usleep(philo->info->time_sleep, philo);
}

void	philo_think(t_philo *philo)
{
	if (check_death(philo))
		return ;
	print_status(philo, "is thinking");
}
