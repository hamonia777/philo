#include "philo.h"

int	check_stop_flag(t_philo *data)
{
    int	stop_flag;

    pthread_mutex_lock(data->info->dead_mutex);
    stop_flag = data->info->is_end;
    pthread_mutex_unlock(data->info->dead_mutex);
    return (stop_flag);
}
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
		if (check_stop_flag(data))
			break ;
		usleep(100);
	}
}

void *philo_lifetime(void *arg)
{
    t_philo *philo;
    int break_flag;

    break_flag = 0;
    philo = (t_philo *) arg;
    while (get_current_time() < philo->info->start_time)
		usleep(100);
	if (philo->id % 2 == 0)
		ft_usleep(philo->info->time_eat / 2,philo);
    while (1) // 이제 이 반복문을 철학자 한명단 얼마나 먹어야하는 must_eat에 따라 조건을 설정하면 되겠지
    {// 시뮬레이션이 아직 끝나지않았는가?(아무도 죽지않았나)
        pthread_mutex_lock(philo->info->lock);
        if(philo->info->is_end)
            break_flag = 1;
        else if(philo->info->must_eat != -1 && philo->eat_count >= philo->info->must_eat)
            break_flag = 1;
        pthread_mutex_unlock(philo->info->lock);
        if (break_flag == 1)
            break;
        else
        {
            philo_eat(philo);
            philo_sleep(philo);
            philo_think(philo);
        }
    }
    return (NULL);
}

void philo_start(t_info *info)
{
    
    int i;
    i = 0;
    while (i < info->philo_num)
    {
        if(pthread_create(&info->philos[i].thread, NULL, philo_lifetime, &info->philos[i]) != 0)
            return ;
        i++;
    }
}