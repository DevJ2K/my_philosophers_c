/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tajavon <tajavon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 18:34:22 by tajavon           #+#    #+#             */
/*   Updated: 2023/12/22 12:33:37 by tajavon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	timestamp(void)
{
	struct timeval		tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	ms_sleep(int ms)
{
	return (usleep(ms * 1000));
}

static void	print_in_french(t_philo *philo, char c, long spent_time)
{
	int		id;

	id = philo->id;
	if (c == 'f')
		printf("%s%ld %d a pris une fourchette\n%s", \
		GREEN, spent_time, id, RESET);
	else if (c == 'e')
		printf("%s%ld %d mange\n%s", ORANGE, spent_time, id, RESET);
	else if (c == 's')
		printf("%s%ld %d dort\n%s", CYAN, spent_time, id, RESET);
	else if (c == 'd')
		printf("%s%ld %d est mort\n%s", RED, spent_time, id, RESET);
	else if (c == 't')
		printf("%s%ld %d reflechit..\n%s", WHITE, spent_time, id, RESET);
}

void	print_action(t_philo *philo, char c)
{
	int		id;
	long	spent_time;

	spent_time = timestamp() - philo->data->t_start;
	pthread_mutex_lock(&philo->data->print);
	id = philo->id;
	if (FRENCH)
		print_in_french(philo, c, spent_time);
	else
	{
		if (c == 'f')
			printf("%s%ld %d has taken a fork\n%s", \
			GREEN, spent_time, id, RESET);
		else if (c == 'e')
			printf("%s%ld %d is eating\n%s", ORANGE, spent_time, id, RESET);
		else if (c == 's')
			printf("%s%ld %d is sleeping\n%s", CYAN, spent_time, id, RESET);
		else if (c == 'd')
			printf("%s%ld %d died\n%s", RED, spent_time, id, RESET);
		else if (c == 't')
			printf("%s%ld %d is thinking\n%s", WHITE, spent_time, id, RESET);
	}
	pthread_mutex_unlock(&philo->data->print);
}

/// @brief The ft_atoi() function converts the initial portion of the string
/// pointed to by str to int representation.
/// @param str The string you want to convert to int.
/// @return The string convert to int.
int	ft_atoi(const char *str)
{
	int	nb;
	int	i;
	int	is_neg;

	nb = 0;
	i = 0;
	is_neg = 1;
	while ((9 <= str[i] && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			is_neg *= -1;
		i++;
	}
	while ('0' <= str[i] && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - 48);
		i++;
	}
	return (nb * is_neg);
}
