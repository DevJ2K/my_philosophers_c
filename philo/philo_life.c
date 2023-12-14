/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tajavon <tajavon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 18:38:25 by tajavon           #+#    #+#             */
/*   Updated: 2023/12/14 11:59:55 by tajavon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	p_eat(t_philo *philo)
{
	t_data	*data;
	int		l_fork_id;

	data = philo->data;
	if (philo->id % 2 == 0)
		ms_sleep(data->t_eat);
	if (philo->id == 1)
		l_fork_id = data->nb_philo - 1;
	else
		l_fork_id = philo->id - 2;
	if (data->forks[l_fork_id] && data->forks[philo->id - 1])
	{
		// les locks et manger
		pthread_mutex_lock(&philo->l_fork);
		pthread_mutex_lock(philo->r_fork);
		data->forks[l_fork_id] = 0;
		data->forks[philo->id - 1] = 0;
		pthread_mutex_lock(&data->print);
		print_action(philo, 'f');
		print_action(philo, 'e');
		ms_sleep(data->t_eat);
		pthread_mutex_unlock(&data->print);
		data->forks[l_fork_id] = 1;
		data->forks[philo->id - 1] = 1;
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(&philo->l_fork);
	}
	else
		return ;
			// p_think(philo);

	// Exemple id = 2;
	// Deja faut verifier s'il ne sera pas mort a la fin du repas
	// Verifier que forks[0] (fourchette de droite) et forks[1] (sa fourchette) == 1;
	// Si oui, ca lock, ca met les fourchettes indispo et ca mange
	// Si non, ca attend que les fourchettes soit dispo

	// lock(print)
	// S'il a reussi a lock, timestamp_in_ms X has taken a fork
	// Sinon, timestamp_in_ms X is thinking

	// Puis il libere les fourchettes et unlock tous,
	// Direct apres il doit aller dormir
}

void	p_sleep(t_philo *philo)
{
	(void)philo;
	// La il doit faire une chose, dodo.
	// Mais il faut qu'il puisse lock le print
	// S'il peut il regarde s'il a le temps de dormir et s'il va mourir dans son sommeil
}

void	p_think(t_philo *philo)
{
	(void)philo;
	// Cette fonction se declenche a son reveil, s'il a la possibilite de manger il mange
	// Sinon il reflechit
}

void	*philo_life(void *philo_param)
{
	t_philo	*philo;

	philo = (t_philo *)philo_param;
	p_eat(philo);
	pthread_mutex_lock(&philo->data->print);
	printf("%s[Philo n.%d] My Turn%s\n", BLUE, philo->id, RESET);
	timestamp();
	printf("Je mange je fais ma vie.\n");
	pthread_mutex_unlock(&philo->data->print);
	return ((void *)0);
}
