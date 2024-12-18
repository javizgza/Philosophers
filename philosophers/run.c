/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javierzaragozatejeda <javierzaragozatej    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 11:55:57 by jazarago          #+#    #+#             */
/*   Updated: 2024/12/18 13:38:51 by javierzarag      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void    *philos_routine(void *arg)
{
    t_philoutils *philosopher;

    philosopher = (t_philoutils *)arg;
    while (1)
    {
        pthread_mutex_lock(philosopher->right_fork);
        pthread_mutex_lock(philosopher->left_fork);
        pthread_mutex_lock(philosopher->print);
        printf("%d has taken a fork\n", philosopher->who);
        printf("%d has taken a fork\n", philosopher->who);
        pthread_mutex_unlock(philosopher->print);
        pthread_mutex_lock(philosopher->print);
        printf("%d is eating\n", philosopher->who);
        pthread_mutex_unlock(philosopher->print);
        usleep(philosopher->time_to_eat * 1000);
        pthread_mutex_unlock(philosopher->right_fork);
        pthread_mutex_unlock(philosopher->left_fork);
        pthread_mutex_lock(philosopher->print);
        printf("%d is sleeping\n", philosopher->who);
        pthread_mutex_unlock(philosopher->print);
        usleep(philosopher->time_to_sleep * 1000);
        pthread_mutex_lock(philosopher->print);
        printf("%d is thinking\n", philosopher->who);
        pthread_mutex_unlock(philosopher->print);
    }
}

void    run_inputs(t_philoutils *inputs, char **argv)
{
    inputs->philos_num = ft_mini_atoi(argv[1]);
    inputs->time_to_die = ft_mini_atoi(argv[2]);
    inputs->time_to_eat = ft_mini_atoi(argv[3]);
    inputs->time_to_sleep = ft_mini_atoi(argv[4]);
    if (argv[5])
        inputs->meals = ft_mini_atoi(argv[5]);
    else
        inputs->meals = -1;
}

void    run_program(t_mutex *program, t_philoutils *inputs)
{
    program->philosophers = inputs;
    program->death_value = 0;
    program->dead_value_lock = malloc(sizeof(pthread_mutex_t));
    program->output_lock = malloc(sizeof(pthread_mutex_t));
    program->food_lock = malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(program->dead_value_lock, NULL);
    pthread_mutex_init(program->output_lock, NULL);
    pthread_mutex_init(program->food_lock, NULL);

    inputs->who = 0;
    inputs->right_fork = malloc(sizeof(pthread_mutex_t));
    inputs->left_fork = malloc(sizeof(pthread_mutex_t));
    inputs->print = program->output_lock;
    pthread_mutex_init(inputs->right_fork, NULL);
    pthread_mutex_init(inputs->left_fork, NULL);
}
