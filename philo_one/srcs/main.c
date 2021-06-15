/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knfonda <knfonda@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 05:57:30 by knfonda           #+#    #+#             */
/*   Updated: 2021/03/09 09:12:22 by knfonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

static void	inc_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->output_m);
	if (philo->parse->count_eat)
		philo->count_eat++;
	if (philo->parse->count_eat && philo->count_eat == philo->parse->count_eat)
		philo->table->stop_eating++;
	pthread_mutex_unlock(&philo->table->output_m);
}

static void	put_forks(t_philo *philo, t_table *table)
{
	pthread_mutex_unlock(&table->forks[philo->left_fork]);
	pthread_mutex_unlock(&table->forks[philo->right_fork]);
	ft_usleep(philo->parse->time_to_sleep, philo);
}

static void	take_forks(t_philo *philo, t_table *table)
{
	pthread_mutex_lock(&table->forks[philo->left_fork]);
	pthread_mutex_lock(&table->forks[philo->right_fork]);
	if (table->exit == 0)
	{
		pthread_mutex_unlock(&table->forks[philo->left_fork]);
		pthread_mutex_unlock(&table->forks[philo->right_fork]);
		return ;
	}
	display_output(philo, FORK);
	display_output(philo, FORK);
	display_output(philo, EAT);
	if (philo->parse->count_eat)
		inc_eat(philo);
	pthread_mutex_lock(&philo->table->mutex);
	philo->last_eating = get_time();
	pthread_mutex_unlock(&philo->table->mutex);
	ft_usleep(philo->parse->time_to_eat, philo);
	display_output(philo, SLEEP);
	display_output(philo, THINK);
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
	while (table->exit)
	{
		take_forks(philo, table);
		put_forks(philo, table);
	}
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
