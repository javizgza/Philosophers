/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jazarago <jazarago@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 11:55:57 by jazarago          #+#    #+#             */
/*   Updated: 2024/12/16 13:19:55 by jazarago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void    run_inputs(t_philoutils *inputs, char **argv)
{
    inputs->philos_num = ft_mini_atoi(argv[1]);
    inputs->time_to_die = ft_mini_atoi(argv[2]);
    inputs->time_to_eat = ft_mini_atoi(argv[3]);
    inputs->time_to_sleep = ft_mini_atoi(argv[4]);
    if (argv[5])
        inputs->time_to_eat = ft_mini_atoi(argv[5]);
    else
        inputs->time_to_eat = -1;
}

void    run_program(t_mutex *program, t_philoutils *inputs)
{
    program->philosophers = inputs;
    program->death_value = 0;
    pthread_mutex_init(program->dead_value_lock, NULL);
    pthread_mutex_init(program->output_lock, NULL);
    pthread_mutex_init(program->food_lock, NULL);
}