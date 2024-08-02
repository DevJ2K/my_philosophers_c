/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tajavon <tajavon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 19:40:18 by tajavon           #+#    #+#             */
/*   Updated: 2024/08/03 00:43:18 by tajavon          ###   ########.fr       */
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

# define FRENCH 0
# define COLORS 1

# if COLORS == 1
#  define RED "\033[1;31m"
#  define BLUE "\033[1;34m"
#  define GREEN "\033[1;32m"
#  define YELLOW "\033[1;33m"
#  define CYAN "\033[1;36m"
#  define WHITE "\033[1;37m"
#  define ORANGE "\033[1;38;5;208m"
#  define PURPLE "\033[38;5;129m"
#  define RESET "\033[0m"
# else
#  define RED "\033[0m"
#  define BLUE "\033[0m"
#  define GREEN "\033[0m"
#  define YELLOW "\033[0m"
#  define CYAN "\033[0m"
#  define WHITE "\033[0m"
#  define ORANGE "\033[0m"
#  define PURPLE "\033[0m"
#  define RESET "\033[0m"
# endif

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
	int				philo_dead;
	long int		t_start;
	pthread_mutex_t	print;
	pthread_mutex_t	info_die;
	t_philo			*all_philo;
}					t_data;

int			valid_args(int argc, char **argv);
int			ft_error(char *str);
int			ft_atoi(const char *str);
long int	timestamp(void);
void		*philo_life(void *philo_param);
int			ms_sleep(int ms);
void		print_action(t_philo *philo, char c);
void		should_died(t_philo *philo);

#endif
