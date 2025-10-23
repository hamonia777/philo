#include "philo.h"

void info_init(t_info *info,char **argv, int argc)
{
    info->philo_num = ft_atoi(argv[1]);
    info->time_die = ft_atoi(argv[2]);
    info->time_eat = ft_atoi(argv[3]);
    info->time_sleep = ft_atoi(argv[4]);
    if(argc == 6)
        info->must_eat = ft_atoi(argv[5]);
    else
        info->must_eat = -1;
}
long long   get_current_time()
{
    struct timeval  time;

    if (gettimeofday(&time, NULL) == -1)
        return (-1);
    return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}
int philo_init(t_info *info)
{
    int i;
    info->philos = malloc(sizeof(t_philo) * info->philo_num);
    info->forks = malloc(sizeof(pthread_mutex_t) * info->philo_num);
    info->lock = malloc(sizeof(pthread_mutex_t));
    info->meal_mutex = malloc(sizeof(pthread_mutex_t));
    info->dead_mutex = malloc(sizeof(pthread_mutex_t));
    if (!info->philos || !info->forks || !info->lock || !info->dead_mutex || !info->meal_mutex)
        return (1);
    info->is_end = 0;
    if (pthread_mutex_init(info->lock, NULL) != 0 || pthread_mutex_init(info->dead_mutex, NULL) != 0 || pthread_mutex_init(info->meal_mutex, NULL) != 0)
        return (1);
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