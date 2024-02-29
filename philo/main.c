/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tajavon <tajavon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 19:12:24 by tajavon           #+#    #+#             */
/*   Updated: 2023/12/22 12:59:45 by tajavon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_data_philo(t_philo *philo, t_data *data, int i)
{
	philo->data = data;
	philo->eat_count = 0;
	philo->r_fork = NULL;
	philo->id = i + 1;
	philo->last_eat = timestamp();
	if (i == data->nb_philo - 1)
		philo->r_fork = &data->all_philo[0].l_fork;
	else
		philo->r_fork = &data->all_philo[i + 1].l_fork;
}

static void	init_philo(t_data *data)
{
	int	i;

	i = 0;
	data->t_start = timestamp();
	while (i < data->nb_philo)
		pthread_mutex_init(&data->all_philo[i++].l_fork, NULL);
	i = 0;
	while (i < data->nb_philo)
	{
		init_data_philo(&data->all_philo[i], data, i);
		if (pthread_create(&data->all_philo[i].thread, NULL, \
		&philo_life, &data->all_philo[i]) != 0)
			break ;
		usleep(200);
		i++;
	}
	i = 0;
	while (i < data->nb_philo)
		pthread_join(data->all_philo[i++].thread, NULL);
}

static void	init_data(t_data *data, char **args, int argc)
{
	data->nb_philo = ft_atoi(args[0]);
	data->t_die = ft_atoi(args[1]);
	data->t_eat = ft_atoi(args[2]);
	data->t_sleep = ft_atoi(args[3]);
	data->philo_dead = 0;
	if (argc == 6)
		data->must_eat = ft_atoi(args[4]);
	else
		data->must_eat = -1;
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->info_die, NULL);
	data->all_philo = malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->all_philo)
		return ;
	init_philo(data);
}

static void	free_data(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
		pthread_mutex_destroy(&data->all_philo[i++].l_fork);
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->info_die);
	free(data->all_philo);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (!valid_args(argc, argv))
		return (1);
	init_data(&data, &argv[1], argc);
	free_data(&data);
}
