/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knfonda <knfonda@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 02:30:19 by knfonda           #+#    #+#             */
/*   Updated: 2021/03/09 08:11:41 by knfonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

int		init_mutex(t_parse *parse, t_table *table)
{
	int		i;

	i = -1;
	if (!(table->forks =\
	(pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * parse->amount)))
		return (1);
	while (++i < parse->amount)
		pthread_mutex_init(&table->forks[i], NULL);
	pthread_mutex_init(&table->mutex, NULL);
	pthread_mutex_init(&table->output_m, NULL);
	pthread_mutex_init(&table->check_die, NULL);
	return (0);
}

void	init_philo(t_parse *parse, t_philo *philo, int i, t_table *table)
{
	philo->id = i;
	philo->count_eat = 0;
	philo->table = table;
	philo->parse = parse;
	philo->left_fork = i;
	philo->right_fork = mod((i + 1), parse->amount);
}

int		ft_exit(t_philo *philo, pthread_t *th, int i)
{
	if (th)
		free(th);
	if (philo->table->forks)
		free(philo->table->forks);
	if (philo->parse)
		free(philo->parse);
	if (philo)
		free(philo);
	return (i);
}

int		init_pthreads(t_philo *philo)
{
	pthread_t	*th1;
	int			i;

	i = -1;
	th1 = NULL;
	if (!(th1 = (pthread_t *)malloc(sizeof(pthread_t) * philo->parse->amount)))
		return (ft_exit(philo, NULL, 1));
	while (++i < philo->parse->amount)
	{
		if (pthread_create(&th1[i], NULL, &philosopher, (void *)&philo[i]) != 0)
			return (ft_exit(philo, th1, 1));
		usleep(100);
	}
	i = -1;
	while (++i < philo->parse->amount)
		if (pthread_join(th1[i], NULL) != 0)
			return (ft_exit(philo, th1, 1));
	pthread_mutex_destroy(&philo->table->output_m);
	pthread_mutex_destroy(&philo->table->mutex);
	pthread_mutex_destroy(&philo->table->check_die);
	i = -1;
	while (++i < philo->parse->amount)
		pthread_mutex_destroy(&philo->table->forks[i]);
	return (ft_exit(philo, th1, 0));
}

int		init(t_parse *parse)
{
	t_philo		*philo;
	t_table		table;
	int			i;

	i = -1;
	if (!(philo = (t_philo *)malloc(sizeof(t_philo) * parse->amount)))
		return (ft_exit(NULL, NULL, 1));
	if (init_mutex(parse, &table) == 1)
		return (ft_exit(philo, NULL, 1));
	while (++i < parse->amount)
		init_philo(parse, &philo[i], i, &table);
	table.exit = 1;
	table.stop_eating = 0;
	if (init_pthreads(philo) == 1)
		return (ft_exit(philo, NULL, 1));
	return (0);
}
