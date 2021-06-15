/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knfonda <knfonda@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 05:57:30 by knfonda           #+#    #+#             */
/*   Updated: 2021/03/09 08:20:42 by knfonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

static void	inc_eat(t_philo *philo)
{
	if (philo->parse->count_eat)
		philo->count_eat++;
	if (philo->parse->count_eat && philo->count_eat == philo->parse->count_eat)
		philo->table->stop_eating++;
}

static int	test(t_philo *philo)
{
	display_output(philo, FORK);
	ft_usleep(philo->parse->time_to_eat, philo);
	if (philo->parse->count_eat)
	{
		sem_wait(philo->table->mutex);
		inc_eat(philo);
		sem_post(philo->table->mutex);
	}
	return (1);
}

static void	take_forks(t_philo *philo, t_table *table)
{
	sem_wait(table->forks);
	sem_wait(table->forks);
	if (philo->table->stop_eating != philo->parse->amount && test(philo) == 1)
	{
		sem_post(philo->table->forks);
		sem_post(philo->table->forks);
		if (philo->table->stop_eating != philo->parse->amount)
			display_output(philo, SLEEP);
		ft_usleep(philo->parse->time_to_sleep, philo);
	}
	else
	{
		sem_post(philo->table->forks);
		sem_post(philo->table->forks);
	}
}

void		*philosopher(void *tmp)
{
	t_philo		*philo;
	t_table		*table;
	pthread_t	th;

	philo = ((t_philo *)tmp);
	table = philo->table;
	philo->last_eating = get_time();
	table->start_time = get_time();
	if (pthread_create(&th, NULL, &monitor, (void *)tmp) != 0)
		return ((void *)1);
	while (philo->table->exit)
		take_forks(philo, table);
	if (pthread_join(th, NULL) != 0)
		return (((void *)1));
	return ((void *)0);
}

int			main(int argc, char **argv)
{
	t_parse		*parse;

	parse = NULL;
	if (!(parse = (t_parse *)malloc(sizeof(t_parse))))
		return (1);
	if (argc != 5 && argc != 6)
	{
		free(parse);
		write(2, "Error\n", 6);
		return (1);
	}
	if (ft_parse(parse, argv) == 1)
	{
		free(parse);
		write(2, "Error\n", 6);
		return (1);
	}
	if (init(parse) == 1)
	{
		write(2, "Error\n", 6);
		return (1);
	}
	return (0);
}
