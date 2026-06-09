/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahmmous <mahmmous@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 04:13:28 by mahmmous          #+#    #+#             */
/*   Updated: 2026/06/09 06:15:58 by mahmmous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *monitor_routine(void *arg)
{
    t_data *data;
    int  i;
    long long elapsed;

    data = (t_data *)arg;
    while(1)
    {
        i = 0;
        while(i < data->num_philos)
        {
            pthread_mutex_lock(&data->meal_mutex);
            elapsed = get_time_ms() - data->philos[i].last_meal_time;
            pthread_mutex_unlock(&data->meal_mutex);
            if(elapsed >= data->time_to_die)
            {
                print_status(&data->philos[i], "died");
                pthread_mutex_lock(&data->stop_mutex);
                data->sim_stop = 1;
                pthread_mutex_unlock(&data->stop_mutex);
                return (NULL);
            }
            i++;
        }
        usleep(1000);
    }
}