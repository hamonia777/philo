/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwpark <jinwpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 06:04:25 by jinwpark          #+#    #+#             */
/*   Updated: 2025/10/24 08:33:27 by jinwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

struct	s_philo;

typedef struct s_info
{
	int				philo_num;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				must_eat;
	int				is_end;
	long long		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*lock;
	pthread_mutex_t	*dead_mutex;
	pthread_mutex_t	*meal_mutex;
	struct s_philo	*philos;
}					t_info;

typedef struct s_philo
{
	int				id;
	int				eat_count;
	long long		last_time;
	pthread_t		thread;
	t_info			*info;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}					t_philo;

int					ft_atoi(const char *str);
long				get_time(void);
void				ft_usleep(long time, t_philo *data);
int					check_death(t_philo *philo);
int					print_status(t_philo *philo, char *msg);
int					check_death(t_philo *philo);
int					info_init(t_info *info, char **argv, int argc);
int					philo_init(t_info *info);
void				philo_start(t_info *info);
void				philo_eat(t_philo *philo);
void				philo_sleep(t_philo *philo);
void				philo_think(t_philo *philo);
void				philo_monitor(t_info *info);

#endif
