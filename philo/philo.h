/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tajavon <tajavon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 19:40:18 by tajavon           #+#    #+#             */
/*   Updated: 2023/12/09 19:24:11 by tajavon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# define RED "\033[31m"
# define BLUE "\033[34m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define ORANGE "\033[38;5;208m"
# define PURPLE "\033[38;5;129m"
# define RESET "\033[0m"

typedef struct s_philo
{
	int				id;
	int				eat_times;
	pthread_t		thread;
	pthread_mutex_t	l_fork;
	pthread_mutex_t	*r_fork;
	struct s_data	*data;
}					t_philo;

typedef struct s_data
{
	int				nb_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				must_eat;
	int				*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	dead;
	t_philo			*all_philo;
}					t_data;

int		valid_args(int argc, char **argv);
int		ft_error(char *str);
int		ft_atoi(const char *str);

#endif
