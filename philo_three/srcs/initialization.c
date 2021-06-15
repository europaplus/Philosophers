/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knfonda <knfonda@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 02:30:19 by knfonda           #+#    #+#             */
/*   Updated: 2021/03/09 09:24:11 by knfonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

int		ft_exit(t_philo *philo, int i)
{
	if (philo->table->pid)
		free(philo->table->pid);
	if (philo->parse)
		free(philo->parse);
	if (philo->table)
		free(philo->table);
	if (philo)
		free(philo);
	if (i == 3)
	{
		sem_close(philo->table->mutex);
		sem_close(philo->table->check_eat);
		sem_close(philo->table->forks);
		sem_close(philo->table->check_die);
		sem_close(philo->table->check_time);
		i = 1;
	}
	return (i);
}

int		init_mutex(t_parse *parse, t_table *table)
{
	sem_unlink("forks");
	if ((table->forks =\
	sem_open("forks", O_CREAT, 0666, parse->amount)) == SEM_FAILED)
		return (1);
	sem_unlink("mutex");
	if ((table->mutex =\
	sem_open("mutex", O_CREAT, 0666, 1)) == SEM_FAILED)
		return (1);
	sem_unlink("check_time");
	if ((table->check_time =\
	sem_open("check_time", O_CREAT, 0666, 1)) == SEM_FAILED)
		return (1);
	sem_unlink("check_eat");
	if ((table->check_eat =\
	sem_open("check_eat", O_CREAT, 0666, 0)) == SEM_FAILED)
		return (1);
	sem_unlink("check_die");
	if ((table->check_die =\
	sem_open("check_die", O_CREAT, 0666, 0)) == SEM_FAILED)
		return (1);
	return (0);
}

void	init_philo(t_parse *parse, t_philo *philo, int i, t_table *table)
{
	philo->id = i;
	philo->count_eat = 0;
	philo->table = table;
	philo->parse = parse;
}

int		init_pthreads(t_philo *philo, int i)
{
	if (!(philo->table->pid =\
	(int *)malloc(sizeof(int) * (philo->parse->amount))))
		return (1);
	while (++i < philo->parse->amount)
	{
		((philo->table->pid[i] = fork()) == -1) ? exit(EXIT_FAILURE) : 0;
		if (philo->table->pid[i] == 0)
		{
			philosopher((void *)&philo[i]);
			exit(0);
		}
	}
	i = -1;
	sem_wait(philo->table->check_die);
	while (++i < philo->parse->amount)
		sem_wait(philo->table->check_eat);
	i = -1;
	while (++i < philo->parse->amount)
		kill(philo->table->pid[i], SIGKILL);
	return (0);
}

int		init(t_parse *parse)
{
	t_philo		*philo;
	t_table		*table;
	int			i;

	philo = NULL;
	table = NULL;
	i = -1;
	if (!(table = (t_table *)malloc(sizeof(t_table))))
		return (ft_exit(philo, 1));
	if (!(philo = (t_philo *)malloc(sizeof(t_philo) * parse->amount)))
		return (ft_exit(philo, 1));
	if (init_mutex(parse, table) == 1)
		return (ft_exit(philo, 1));
	table->exit = 1;
	table->stop_eating = 0;
	while (++i < parse->amount)
		init_philo(parse, &philo[i], i, table);
	if (init_pthreads(philo, -1) == 1)
		return (ft_exit(philo, 3));
	sem_close(philo->table->mutex);
	sem_close(philo->table->check_eat);
	sem_close(philo->table->forks);
	sem_close(philo->table->check_die);
	sem_close(philo->table->check_time);
	return (ft_exit(philo, 0));
}
