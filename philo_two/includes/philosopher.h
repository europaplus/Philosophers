/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knfonda <knfonda@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 22:38:58 by knfonda           #+#    #+#             */
/*   Updated: 2021/03/09 09:24:48 by knfonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H
# include <sys/time.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <semaphore.h>

# define EAT			"is eating\n"
# define SLEEP		"is sleeping\n"
# define THINK		"is thinking\n"
# define DIE			"is died\n"
# define FORK		"taken a fork\n"

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
	struct s_table	*table;
	struct s_parse	*parse;
	uint64_t		last_eating;
}					t_philo;

typedef struct		s_table
{
	int				exit;
	int				stop_eating;
	uint64_t		start_time;
	sem_t			*mutex;
	sem_t			*check_die;
	sem_t			*check_time;
	sem_t			*forks;
}					t_table;

uint64_t			get_time(void);
int					mod(int a, int b);
int					init(t_parse *all);
void				*monitor(void *tmp);
void				*philosopher(void *tmp);
void				ft_usleep(uint64_t time, t_philo *philo);
int					ft_parse(t_parse *parse, char **argv);
int					display_output(t_philo *philo, char *message);

#endif
