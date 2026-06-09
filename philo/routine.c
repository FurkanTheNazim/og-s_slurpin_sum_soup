/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahmmous <mahmmous@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 03:37:50 by mahmmous          #+#    #+#             */
/*   Updated: 2026/06/09 06:57:47 by mahmmous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_stop(t_philo *philo)
{
	int	stopped;

	pthread_mutex_lock(&philo->data->stop_mutex);
	stopped = philo->data->sim_stop;
	pthread_mutex_unlock(&philo->data->stop_mutex);
	return (stopped);
}

static void	eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
	}
	print_status(philo, "is eating");
	pthread_mutex_lock(&philo->data->meal_mutex);
	philo->last_meal_time = get_time_ms();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->meal_mutex);
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(10);
	while (!check_stop(philo))
	{
		if (philo->data->num_philos == 1)
		{
			pthread_mutex_lock(philo->left_fork);
			print_status(philo, "has taken a fork");
			ft_usleep(philo->data->time_to_die);
			pthread_mutex_unlock(philo->left_fork);
			return (NULL);
		}
		eat(philo);
		print_status(philo, "is sleeping");
		ft_usleep(philo->data->time_to_sleep);
		print_status(philo, "is thinking");
		if (philo->data->num_philos % 2 != 0)
			ft_usleep(1);
	}
	return (NULL);
}
