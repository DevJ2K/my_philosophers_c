/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tajavon <tajavon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 18:30:57 by tajavon           #+#    #+#             */
/*   Updated: 2023/12/08 19:06:39 by tajavon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	only_numbers(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ('0' <= str[i] && str[i] <= '9')
			i++;
		else
			return (0);
	}
	return (1);
}

int	valid_args(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
		return (ft_error("Invalid number of arguments.") - 1);
	i = 1;
	while (i < argc)
	{
		if (!only_numbers(argv[i]))
			return (ft_error("Some arguments are not numbers.") - 1);
		i++;
	}
	return (1);
}
