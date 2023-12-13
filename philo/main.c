/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tajavon <tajavon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 19:12:24 by tajavon           #+#    #+#             */
/*   Updated: 2023/12/13 18:27:23 by tajavon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	timestamp(void)
{
	struct timeval		tv;

	gettimeofday(&tv, NULL);
	printf("%ld -> ", tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	*philo_life(void *philo_param)
{
	t_philo	*philo;

	philo = (t_philo *)philo_param;
	pthread_mutex_lock(&philo->data->print);
	printf("%s[Philo n.%d] My Turn%s\n", BLUE, philo->id, RESET);
	timestamp();
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
		data->all_philo[i].eat_count = 0;
		data->all_philo[i].r_fork = NULL;
		data->all_philo[i].id = i + 1;
		pthread_mutex_init(&data->all_philo[i].l_fork, NULL);
		if (i == data->nb_philo - 1)
			data->all_philo[i].r_fork = &data->all_philo[0].l_fork;
		else
			data->all_philo[i].r_fork = &data->all_philo[i + 1].l_fork;
		if (pthread_create(&data->all_philo[i].thread, NULL, \
		&philo_life, &data->all_philo[i]) != 0)
			return (-1);
		usleep(10);
		i++;
	}
	usleep(50);
	pthread_mutex_lock(&data->print);
	printf("%sTous les mutex sont initialisees !\n%s", GREEN, RESET);
	pthread_mutex_unlock(&data->print);
	i = 0;
	while (i < data->nb_philo)
		pthread_join(data->all_philo[i++].thread, NULL);
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
	data->forks = malloc(sizeof(int) * data->nb_philo);
	if (!data->forks)
		return ;
	data->forks = memset(data->forks, 1, data->nb_philo * sizeof(int));
	printf("\n");
	data->all_philo = malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->all_philo)
		return free(data->forks);
	init_philo(data);
}

void	free_data(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{

		pthread_mutex_destroy(&data->all_philo[i].l_fork);
		i++;
	}
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
	// printf("ARGC : %d\n", argc);
	(void)argv;
}
