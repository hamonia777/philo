#include "philo.h"

void philo_cleanup(t_info *info)
{
    int i = 0;
    while (i < info->philo_num)
    {
        pthread_mutex_destroy(&info->forks[i]); // 포크 뮤텍스 파괴
        i++;
    }
    pthread_mutex_destroy(info->lock); // 공용 락 파괴

    free(info->forks);   // 포크 배열 해제
    free(info->philos);  // 철학자 배열 해제
    free(info->lock);    // 공용 락 해제
    free(info);          // info 구조체 해제
}

int main(int argc,char **argv)
{
    int i;

    i = 0;
    if(argc != 5 && argc != 6)
    {
        printf("error : wrong arg");
        return (1);
    }
    t_info *info;
    info = malloc(sizeof(t_info));
    if(!info)
        return (1);    
    info_init(info, argv, argc);
    if(philo_init(info))
        return (1);
    info->start_time = get_current_time();
    while (i < info->philo_num)
    {
        info->philos[i].last_time = info->start_time;
        i++;
    }        
    printf("Philos: %d\n", info->philo_num);
    printf("Die: %d\n", info->time_die);
    printf("Eat: %d\n", info->time_eat);
    printf("Sleep: %d\n", info->time_sleep);
    printf("Must eat: %d\n", info->must_eat);
    philo_start(info);
    philo_monitor(info);
    i = 0;
    while (i < info->philo_num)
    {
        pthread_join(info->philos[i].thread, NULL);
        i++;
    }
    philo_cleanup(info);
}