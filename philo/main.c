/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahmmous <mahmmous@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 00:21:42 by mahmmous          #+#    #+#             */
/*   Updated: 2026/06/09 06:46:11 by mahmmous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_atoi_strict(const char *str)
{
	long	result;
	int		i;

	result = 0;
	i = 0;
	if (!str || !str[0])
		return (-1);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		result = result * 10 + (str[i] - '0');
		if (result > 2147483647)
			return (-1);
		i++;
	}
	return ((int)result);
}

static int	parse_args(t_data *data, int argc, char **argv)
{
	data->num_philos = ft_atoi_strict(argv[1]);
	data->time_to_die = ft_atoi_strict(argv[2]);
	data->time_to_eat = ft_atoi_strict(argv[3]);
	data->time_to_sleep = ft_atoi_strict(argv[4]);
	data->must_eat_count = -1;
	if (argc == 6)
		data->must_eat_count = ft_atoi_strict(argv[5]);
	if (data->num_philos <= 0 || data->time_to_die <= 0
		|| data->time_to_eat <= 0 || data->time_to_sleep <= 0)
		return (1);
	if (argc == 6 && data->must_eat_count <= 0)
		return (1);
	data->sim_stop = 0;
	return (0);
}

static void	start_simulation(t_data *data)
{
	int	i;

	data->start_time = get_time_ms();
	i = 0;
	while (i < data->num_philos)
	{
		data->philos[i].last_meal_time = data->start_time;
		i++;
	}
	i = 0;
	while (i < data->num_philos)
	{
		pthread_create(&data->philos[i].thread, NULL,
			philosopher_routine, &data->philos[i]);
		i++;
	}
	monitor_routine(data);
	i = 0;
	while (i < data->num_philos)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
	{
		write(2, "Error: wrong number of arguments\n", 33);
		return (1);
	}
	if (parse_args(&data, argc, argv))
	{
		write(2, "Error: invalid arguments\n", 25);
		return (1);
	}
	if (init_data(&data))
	{
		write(2, "Error: init failed\n", 19);
		return (1);
	}
	start_simulation(&data);
	free_all(&data);
	return (0);
}
