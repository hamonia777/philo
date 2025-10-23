#include "philo.h"

void philo_eat(t_philo *philo)
{
    if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(philo->right_fork);
        printf("%lld %d has taken a right fork\n",get_current_time()- philo->info->start_time, philo->id);
        pthread_mutex_lock(philo->left_fork);
        printf("%lld %d has taken a left fork\n",get_current_time()- philo->info->start_time, philo->id);
    }
    else
    {
        pthread_mutex_lock(philo->left_fork);
        printf("%lld %d has taken a left fork\n",get_current_time()- philo->info->start_time, philo->id);
        pthread_mutex_lock(philo->right_fork);
        printf("%lld %d has taken a right fork\n",get_current_time()- philo->info->start_time, philo->id);        
    }
	// if (check_stop_flag(philo))
	// {
	// 	pthread_mutex_unlock(philo->left_fork);
	// 	pthread_mutex_unlock(philo->right_fork);
	// 	return ;
	// }    
    if(philo->eat_count < philo->info->must_eat || philo->info->must_eat == -1)
    {
        pthread_mutex_lock(philo->info->lock);
        philo->last_time = get_current_time();
        printf("%lld %d is eating \n",philo->last_time - philo->info->start_time,philo->id);
        philo->eat_count++;
        pthread_mutex_unlock(philo->info->lock);
        usleep(philo->info->time_eat * 1000);
    }
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
}

void philo_sleep(t_philo *philo)
{
    long long current;
    current = get_current_time();
    pthread_mutex_lock(philo->info->lock);
    if (philo->info->is_end == 0)
        printf("%lld %d is sleeping\n",current - philo->info->start_time, philo->id);
    pthread_mutex_unlock(philo->info->lock);
    usleep(philo->info->time_sleep * 1000);
}

void philo_think(t_philo *philo)
{
    long long current;

    current = get_current_time();
    pthread_mutex_lock(philo->info->lock);
    if (philo->info->is_end == 0)
        printf("%lld %d is thinking\n",current - philo->info->start_time, philo->id);
    pthread_mutex_unlock(philo->info->lock);
}