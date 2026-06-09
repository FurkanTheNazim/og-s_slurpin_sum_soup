/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahmmous <mahmmous@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 04:13:28 by mahmmous          #+#    #+#             */
/*   Updated: 2026/06/09 06:40:09 by mahmmous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_death(t_data *data, int *all_ate)
{
	int			i;
	long long	elapsed;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_lock(&data->meal_mutex);
		elapsed = get_time_ms() - data->philos[i].last_meal_time;
		if (data->must_eat_count != -1
			&& data->philos[i].meals_eaten < data->must_eat_count)
			*all_ate = 0;
		pthread_mutex_unlock(&data->meal_mutex);
		if (elapsed >= data->time_to_die)
		{
			print_status(&data->philos[i], "died");
			pthread_mutex_lock(&data->stop_mutex);
			data->sim_stop = 1;
			pthread_mutex_unlock(&data->stop_mutex);
			return (1);
		}
		i++;
	}
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_data	*data;
	int		all_ate;

	data = (t_data *)arg;
	while (1)
	{
		all_ate = 1;
		if (check_death(data, &all_ate))
			return (NULL);
		if (data->must_eat_count != -1 && all_ate == 1)
		{
			pthread_mutex_lock(&data->stop_mutex);
			data->sim_stop = 1;
			pthread_mutex_unlock(&data->stop_mutex);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}
