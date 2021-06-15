/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knfonda <knfonda@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 06:56:05 by knfonda           #+#    #+#             */
/*   Updated: 2021/03/09 09:31:09 by knfonda          ###   ########.fr       */
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
		sem_wait(philo->table->check_time);
		gettimeofday(&tv, NULL);
		sem_post(philo->table->check_time);
		start = tv.tv_sec * 1000;
		start += tv.tv_usec / 1000;
		if (tv.tv_usec < 0)
		{
			tv.tv_sec--;
			tv.tv_usec += 1000000;
		}
		if (start >= time)
			break ;
		if (philo->table->exit == 0)
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

int			ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	if (s1 == NULL)
		return (-1);
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

int			display_output(t_philo *philo, char *message)
{
	uint64_t	time;

	sem_wait(philo->table->mutex);
	time = get_time() - philo->table->start_time;
	if (ft_strcmp(message, FORK) == 0 && philo->table->exit != 0)
	{
		printf("%llu %d %s", time, (philo->id) + 1, message);
		printf("%llu %d %s", time, (philo->id) + 1, message);
		printf("%llu %d %s", time, (philo->id) + 1, EAT);
		philo->last_eating = get_time();
	}
	else if (philo->table->exit != 0)
	{
		printf("%llu %d %s", time, (philo->id) + 1, SLEEP);
		printf("%llu %d %s", time, (philo->id) + 1, THINK);
	}
	sem_post(philo->table->mutex);
	return (0);
}

void		*monitor(void *tmp)
{
	t_philo		*philo;
	uint64_t	limit;
	int			i;

	philo = ((t_philo *)tmp);
	while (philo->table->exit)
	{
		sem_wait(philo->table->mutex);
		check_eat(philo);
		limit = get_time() - philo->last_eating;
		if ((limit >= philo->parse->time_to_die && philo->table->exit != 0))
		{
			philo->table->exit = 0;
			printf("%llu %d %s",\
			(get_time() - philo->table->start_time), (philo->id) + 1, DIE);
			i = -1;
			sem_post(philo->table->check_die);
			while (++i < philo->parse->amount)
				sem_post(philo->table->check_eat);
			return ((void *)0);
		}
		sem_post(philo->table->mutex);
	}
	return ((void *)0);
}
