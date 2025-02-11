/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javierzaragozatejeda <javierzaragozatej    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 16:17:58 by javierzarag       #+#    #+#             */
/*   Updated: 2025/02/04 16:55:55 by javierzarag      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void clean_up(t_mutex *program, pthread_mutex_t *forks)
{
	int	idx; // Declare at top

	idx = 0;
	while (idx < program->philos_num)
	{
		pthread_mutex_destroy(&forks[idx]);
		pthread_mutex_destroy(&program->philosophers[idx].meal_time_lock);
		idx++;
	}
	free(forks);
	pthread_mutex_destroy(program->dead_value_lock);
	pthread_mutex_destroy(program->output_lock);
	pthread_mutex_destroy(program->food_lock);
	free(program->dead_value_lock);
	free(program->output_lock);
	free(program->food_lock);
}
