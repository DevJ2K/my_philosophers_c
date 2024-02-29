/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tajavon <tajavon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 18:38:25 by tajavon           #+#    #+#             */
/*   Updated: 2023/12/21 21:40:05 by tajavon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	p_eat(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (philo->id % 2 != 0)
	{
		pthread_mutex_lock(philo->r_fork);
		print_action(philo, 'f');
		pthread_mutex_lock(&philo->l_fork);
		print_action(philo, 'f');
	}
	else
	{
		pthread_mutex_lock(&philo->l_fork);
		print_action(philo, 'f');
		pthread_mutex_lock(philo->r_fork);
		print_action(philo, 'f');
	}
	print_action(philo, 'e');
	philo->eat_count++;
	ms_sleep(philo->data->t_eat);
	philo->last_eat = timestamp();
	if (philo->id % 2 != 0)
	{
		pthread_mutex_unlock(&philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(&philo->l_fork);
	}
}

void	p_sleep(t_philo *philo)
{
	(void)philo;
	t_data	*data;

	data = philo->data;
	print_action(philo, 's');

	ms_sleep(philo->data->t_sleep);
}

void	p_think(t_philo *philo)
{
	(void)philo;
	print_action(philo, 't');
}

void	should_died(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (philo->last_eat != -1)
	{
		if (philo->last_eat + data->t_die <
			philo->last_eat + data->t_eat + data->t_sleep)
			{
				print_action(philo, 'd');
				exit (1);
			}
	}
	else
	{
		if (data->t_start + data->t_die <
			data->t_start + data->t_eat + data->t_sleep)
			{
				print_action(philo, 'd');
				exit (1);
			}
	}
	// data = philo->data;
	// data->t_die
	// if ((philo->last_eat + data.) - timestamp())
}

void	*philo_life(void *philo_param)
{
	t_philo	*philo;

	philo = (t_philo *)philo_param;
	int i = 0;
	while (i < 10)
	{
		should_died(philo);
		// pthread_mutex_lock(&philo->data->print);
		// printf("%s[Philo n.%d] My Turn%s\n", BLUE, philo->id, RESET);
		// printf("Je mange je fais ma vie.\n");
		// pthread_mutex_unlock(&philo->data->print);
		if (i != 0)
			p_think(philo);
		p_eat(philo);
		p_sleep(philo);
		i++;
	}

	return ((void *)0);
}
