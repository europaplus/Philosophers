/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knfonda <knfonda@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 06:56:05 by knfonda           #+#    #+#             */
/*   Updated: 2021/03/09 09:35:41 by knfonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

void		ft_usleep(uint64_t time, t_philo *philo)
{
	uint64_t			start;
	struct timeval		tv;

	gettimeofday(&tv, NULL);
	start = tv.tv_sec * 1000;
	start += tv.tv_usec / 1000;
	time = time + start;
	while (1)
	{
		pthread_mutex_lock(&philo->table->output_m);
		gettimeofday(&tv, NULL);
		pthread_mutex_unlock(&philo->table->output_m);
		start = tv.tv_sec * 1000;
		start += tv.tv_usec / 1000;
		if (tv.tv_usec < 0)
		{
			tv.tv_sec--;
			tv.tv_usec += 1000000;
		}
		if (start >= time)
			break ;
		if (philo->table->exit == 0 && (!philo->parse->count_eat))
			break ;
	}
}

uint64_t	get_time(void)
{
	uint64_t			mill_sec;
	struct timeval		tv1;

	gettimeofday(&tv1, NULL);
	mill_sec = tv1.tv_sec * 1000;
	mill_sec += tv1.tv_usec / 1000;
	if (tv1.tv_usec < 0)
	{
		tv1.tv_sec--;
		tv1.tv_usec += 1000000;
	}
	return (mill_sec);
}

int			mod(int a, int b)
{
	int		r;

	r = a % b;
	if (r < 0)
		return (r + b);
	else
		return (r);
}

int			display_output(t_philo *philo, char *message)
{
	uint64_t	time;

	pthread_mutex_lock(&philo->table->output_m);
	time = get_time() - philo->table->start_time;
	if (philo->table->exit == 0)
	{
		pthread_mutex_unlock(&philo->table->output_m);
		return (0);
	}
	printf("%llu %d %s", time, (philo->id + 1), message);
	pthread_mutex_unlock(&philo->table->output_m);
	return (0);
}

void		*monitor(void *tmp)
{
	t_philo		*philo;
	uint64_t	limit;

	philo = ((t_philo *)tmp);
	while (philo->table->exit)
	{
		pthread_mutex_lock(&philo->table->mutex);
		if (philo->parse->count_eat\
		&& philo->table->stop_eating == philo->parse->amount)
			philo->table->exit = 0;
		limit = get_time() - philo->last_eating;
		if ((limit >= philo->parse->time_to_die && philo->table->exit != 0))
		{
			philo->table->exit = 0;
			printf("%llu %d %s", (get_time() - philo->table->start_time),\
			(philo->id + 1), DIE);
		}
		pthread_mutex_unlock(&philo->table->mutex);
		usleep(1000);
	}
	return ((void *)0);
}
