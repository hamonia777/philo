/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwpark <jinwpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 06:03:40 by jinwpark          #+#    #+#             */
/*   Updated: 2025/10/25 09:46:50 by jinwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	handle_one_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, "has taken a left fork");
	ft_usleep(philo->info->time_die + 10, philo);
	pthread_mutex_unlock(philo->left_fork);
	return (1);
}

static int	take_even_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	if (check_death(philo))
	{
		pthread_mutex_unlock(philo->right_fork);
		return (1);
	}
	print_status(philo, "has taken a right fork");
	pthread_mutex_lock(philo->left_fork);
	if (check_death(philo))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (1);
	}
	print_status(philo, "has taken a left fork");
	return (0);
}

static int	take_odd_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	if (check_death(philo))
	{
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	print_status(philo, "has taken a left fork");
	pthread_mutex_lock(philo->right_fork);
	if (check_death(philo))
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	print_status(philo, "has taken a right fork");
	return (0);
}

static int	take_forks(t_philo *philo)
{
	if (philo->info->philo_num == 1)
		return (handle_one_philo(philo));
	if (philo->id % 2 == 0)
		return (take_even_forks(philo));
	else
		return (take_odd_forks(philo));
}

void	philo_eat(t_philo *philo)
{
	if (take_forks(philo) != 0)
		return ;
	pthread_mutex_lock(philo->info->lock);
	if (philo->info->is_end == 0)
	{
		philo->last_time = get_time();
		printf("%lld %d is eating\n", philo->last_time
			- philo->info->start_time, philo->id);
		philo->eat_count++;
	}
	pthread_mutex_unlock(philo->info->lock);
	ft_usleep(philo->info->time_eat, philo);
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
	long	think_time;

	if (check_death(philo))
		return ;
	print_status(philo, "is thinking");
	if (philo->info->philo_num % 2 != 0)
	{
		think_time = (philo->info->time_eat * 2 - philo->info->time_sleep);
		if (think_time > 0)
			ft_usleep(think_time / 2, philo);
	}
}
