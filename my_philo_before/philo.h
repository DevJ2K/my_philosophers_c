/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tajavon <tajavon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 19:40:18 by tajavon           #+#    #+#             */
/*   Updated: 2023/12/21 21:12:36 by tajavon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# define RED "\033[1;31m"
# define BLUE "\033[1;34m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define ORANGE "\033[1;38;5;208m"
# define PURPLE "\033[38;5;129m"
# define RESET "\033[0m"

typedef struct s_philo
{
	int				id;
	int				eat_count;
	long int		last_eat;
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
	long int		t_start;
	pthread_mutex_t	print;
	pthread_mutex_t	dead;
	t_philo			*all_philo;
}					t_data;

int			valid_args(int argc, char **argv);
int			ft_error(char *str);
int			ft_atoi(const char *str);
long int	timestamp(void);
void		*philo_life(void *philo_param);
int			ms_sleep(int ms);
void		print_action(t_philo *philo, char c);

#endif
