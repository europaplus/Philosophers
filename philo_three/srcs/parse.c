/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knfonda <knfonda@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 06:57:39 by knfonda           #+#    #+#             */
/*   Updated: 2021/03/08 13:19:48 by knfonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

static int	numeric(int i, char **argv)
{
	int		j;
	int		number;

	number = 0;
	j = -1;
	while (argv[i][++j])
	{
		if (argv[i][j] - 48 < 0 || argv[i][j] - 48 > 9)
			return (-1);
		number = number * 10;
		number = number + (argv[i][j] - '0');
	}
	return (number);
}

static int	ft_parse_norm(t_parse *parse, char **argv)
{
	if ((parse->amount = numeric(1, argv)) == -1)
		return (-1);
	if ((parse->time_to_die = numeric(2, argv)) == -1)
		return (-1);
	if ((parse->time_to_eat = numeric(3, argv)) == -1)
		return (-1);
	if ((parse->time_to_sleep = numeric(4, argv)) == -1)
		return (-1);
	return (0);
}

int			ft_parse(t_parse *parse, char **argv)
{
	if (ft_parse_norm(parse, argv) == -1)
		return (1);
	if (argv[5])
	{
		if ((parse->count_eat = numeric(5, argv)) == -1)
			return (1);
	}
	else
		parse->count_eat = 0;
	if (parse->amount < 2 || parse->time_to_die <= 0\
	|| parse->time_to_eat <= 0 || parse->time_to_sleep <= 0)
		return (1);
	return (0);
}
