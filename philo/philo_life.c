/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tajavon <tajavon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 18:38:25 by tajavon           #+#    #+#             */
/*   Updated: 2023/12/13 18:58:49 by tajavon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	p_eat(t_philo *philo)
{
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
	// La il doit faire une chose, dodo.
	// Mais il faut qu'il puisse lock le print
	// S'il peut il regarde s'il a le temps de dormir et s'il va mourir dans son sommeil
}

void	p_think(t_philo *philo)
{
	// Cette fonction se declenche a son reveil, s'il a la possibilite de manger il mange
	// Sinon il reflechit
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
