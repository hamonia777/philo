/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_util2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwpark <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 08:34:06 by jinwpark          #+#    #+#             */
/*   Updated: 2025/10/24 08:34:15 by jinwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	mytime;
	long			result;

	gettimeofday(&mytime, NULL);
	result = ((size_t)mytime.tv_sec * 1000) + ((size_t)mytime.tv_usec / 1000);
	return (result);
}

void	ft_usleep(long time, t_philo *data)
{
	long	finish;

	finish = get_time() + time;
	while (get_time() < finish)
	{
		if (check_death(data))
			break ;
		usleep(100);
	}
}

int	print_status(t_philo *philo, char *msg)
{
	long long	current;
	int			should_print;

	current = get_time();
	pthread_mutex_lock(philo->info->lock);
	should_print = (philo->info->is_end == 0);
	if (should_print)
		printf("%lld %d %s\n", current - philo->info->start_time, philo->id,
			msg);
	pthread_mutex_unlock(philo->info->lock);
	return (should_print);
}

int	check_death(t_philo *philo)
{
	int	is_dead;

	pthread_mutex_lock(philo->info->lock);
	is_dead = philo->info->is_end;
	pthread_mutex_unlock(philo->info->lock);
	return (is_dead);
}
