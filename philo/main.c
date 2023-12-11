/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tajavon <tajavon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 19:12:24 by tajavon           #+#    #+#             */
/*   Updated: 2023/12/11 19:05:46 by tajavon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_life(void *philo_param)
{
	t_philo	*philo;

	philo = (t_philo *)philo_param;
	printf("%s[Philo n.%d] My Turn%s\n", BLUE, philo->id, RESET);
	printf("Je mange je fais ma vie.\n");
	pthread_mutex_unlock(&philo->data->print);
	return ((void *)0);
}

int	init_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		data->all_philo[i].data = data;
		data->all_philo[i].eat_times = 0;
		data->all_philo[i].r_fork = NULL;
		data->all_philo[i].id = i + 1;
		pthread_mutex_init(&data->all_philo[i].l_fork, NULL);
		if (i == data->nb_philo - 1)
			data->all_philo[i].r_fork = &data->all_philo[0].l_fork;
		else
			data->all_philo[i].r_fork = &data->all_philo[i + 1].l_fork;
		pthread_mutex_lock(&data->print);
		pthread_create(&data->all_philo[i].thread, NULL, \
		&philo_life, &data->all_philo[i]);
		i++;
	}
	pthread_mutex_lock(&data->print);
	printf("%sTous les mutex sont initialisees !\n%s", GREEN, RESET);
	pthread_mutex_unlock(&data->print);
	return (0);
}

void	init_data(t_data *data, char **args, int argc)
{
	data->nb_philo = ft_atoi(args[0]);
	data->t_die = ft_atoi(args[1]);
	data->t_eat = ft_atoi(args[2]);
	data->t_sleep = ft_atoi(args[3]);
	if (argc == 6)
		data->must_eat = ft_atoi(args[4]);
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->dead, NULL);
	data->all_philo = malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->all_philo)
		return ;
	init_philo(data);
}

void	free_data(t_data *data)
{
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->dead);
	free(data->all_philo);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (!valid_args(argc, argv))
		return (1);
	init_data(&data, &argv[1], argc);
	free_data(&data);
	printf("ARGC : %d\n", argc);
	(void)argv;
}
