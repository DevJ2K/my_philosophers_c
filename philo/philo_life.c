/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tajavon <tajavon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 18:38:25 by tajavon           #+#    #+#             */
/*   Updated: 2024/02/15 14:10:06 by tajavon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	take_fork(t_philo *philo, t_data *data)
{
	if (philo->id % 2 != 0)
	{
		pthread_mutex_lock(philo->r_fork);
		should_died(philo);
		if (data->philo_dead >= 1)
		{
			pthread_mutex_unlock(philo->r_fork);
			return (0);
		}
		print_action(philo, 'f');
		pthread_mutex_lock(&philo->l_fork);
		print_action(philo, 'f');
		return (1);
	}
	pthread_mutex_lock(&philo->l_fork);
	should_died(philo);
	if (data->philo_dead >= 1)
	{
		pthread_mutex_unlock(&philo->l_fork);
		return (0);
	}
	print_action(philo, 'f');
	pthread_mutex_lock(philo->r_fork);
	print_action(philo, 'f');
	return (1);
}

static void	p_eat(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (take_fork(philo, data) == 0)
		return ;
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

static void	p_action(t_philo *philo, char action)
{
	if (action == 's')
	{
		if (philo->data->philo_dead >= 1)
			return ;
		print_action(philo, 's');
		ms_sleep(philo->data->t_sleep);
	}
	if (action == 't')
	{
		if (philo->data->philo_dead >= 1)
			return ;
		print_action(philo, 't');
	}
	if (action == 'e')
		p_eat(philo);
}

void	should_died(t_philo *philo)
{
	t_data		*data;
	long int	cur_time;

	data = philo->data;
	pthread_mutex_lock(&data->info_die);
	cur_time = timestamp();
	if (philo->last_eat + data->t_die < cur_time + data->t_eat)
	{
		if (data->philo_dead == 0)
			print_action(philo, 'd');
		data->philo_dead++;
		pthread_mutex_unlock(&data->info_die);
		return ;
	}
	pthread_mutex_unlock(&data->info_die);
}

void	*philo_life(void *philo_param)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)philo_param;
	i = 0;
	while (1)
	{
		if (philo->data->philo_dead >= 1)
			break ;
		if (philo->data->nb_philo == 1)
		{
			ms_sleep(philo->data->t_die);
			print_action(philo, 'd');
			break ;
		}
		if (philo->data->must_eat != -1 && i == philo->data->must_eat)
			break ;
		if (i != 0)
			p_action(philo, 't');
		p_action(philo, 'e');
		p_action(philo, 's');
		i++;
	}
	return ((void *)0);
}
