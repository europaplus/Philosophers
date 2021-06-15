/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knfonda <knfonda@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 22:38:58 by knfonda           #+#    #+#             */
/*   Updated: 2021/03/09 09:23:48 by knfonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define EAT			"is eating\n"
# define SLEEP		"is sleeping\n"
# define THINK		"is thinking\n"
# define DIE			"is died\n"
# define FORK		"taken a fork\n"
# define EATING		1
# define HUNGRY		0

typedef struct		s_parse
{
	int				amount;
	uint64_t		time_to_eat;
	uint64_t		time_to_die;
	uint64_t		time_to_think;
	uint64_t		time_to_sleep;
	int				count_eat;
}					t_parse;

typedef	struct		s_philo
{
	int				id;
	int				count_eat;
	int				left_fork;
	int				right_fork;
	struct s_table	*table;
	struct s_parse	*parse;
	uint64_t		last_eating;
}					t_philo;

typedef struct		s_table
{
	int				exit;
	int				stop_eating;
	uint64_t		start_time;
	pthread_mutex_t	mutex;
	pthread_mutex_t	*forks;
	pthread_mutex_t	output_m;
	pthread_mutex_t	check_die;
}					t_table;

int					init(t_parse *all);
void				*philosopher(void *tmp);
int					ft_parse(t_parse *parse, char **argv);
int					display_output(t_philo *philo, char *message);
void				*monitor(void *tmp);
int					mod(int a, int b);
uint64_t			get_time(void);
void				ft_usleep(uint64_t time, t_philo *philo);
#endif
