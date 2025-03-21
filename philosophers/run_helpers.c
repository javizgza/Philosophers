/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javierzaragozatejeda <javierzaragozatej    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 16:18:13 by javierzarag       #+#    #+#             */
/*   Updated: 2025/03/21 11:05:13 by javierzarag      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "philosophers.h"

void    run_inputs(t_philoutils *inputs, char **argv)
{
	int idx = 0;
	while (idx < ft_mini_atoi(argv[1]))
	{
		inputs[idx].philos_num = ft_mini_atoi(argv[1]);
		inputs[idx].time_to_die = ft_mini_atoi(argv[2]);
		inputs[idx].time_to_eat = ft_mini_atoi(argv[3]);
		inputs[idx].time_to_sleep = ft_mini_atoi(argv[4]);
		if (argv[5])
			inputs[idx].meals = ft_mini_atoi(argv[5]);
		else
			inputs[idx].meals = -1;
		idx++;
	}
}

void    run_program(t_mutex *program, t_philoutils *inputs)
{
	pthread_mutex_t *forks;
	int idx;

	program->philosophers = inputs;
	program->philos_num = inputs->philos_num;
	program->death_value = 0;
	init_mutexes(program);
	forks = malloc(sizeof(pthread_mutex_t) * program->philos_num);
	idx = 0;
	while (idx < program->philos_num)
	{
		pthread_mutex_init(&forks[idx], NULL);
		idx++;
	}
	init_philosophers(inputs, program, forks);
	create_threads(program);
	clean_up(program, forks);
}

void init_mutexes(t_mutex *program)
{
	program->dead_value_lock = malloc(sizeof(pthread_mutex_t));
	program->output_lock = malloc(sizeof(pthread_mutex_t));
	program->food_lock = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(program->dead_value_lock, NULL);
	pthread_mutex_init(program->output_lock, NULL);
	pthread_mutex_init(program->food_lock, NULL);
}

void init_philosophers(t_philoutils *inputs, t_mutex *program, pthread_mutex_t *forks)
{
	int idx;

	idx = 0;
	while (idx < program->philos_num)
	{
		inputs[idx].who = idx + 1;
		inputs[idx].right_fork = &forks[idx];
		inputs[idx].left_fork = &forks[(idx + 1) % program->philos_num];
		inputs[idx].print = program->output_lock;
		inputs[idx].last_meal_time = get_current_time();
		inputs[idx].program = program;
		pthread_mutex_init(&inputs[idx].meal_time_lock, NULL);
		idx++;
	}
}

void create_threads(t_mutex *program)
{
	pthread_t monitor_thread;
	int idx;

	pthread_create(&monitor_thread, NULL, death_logic, program);
	idx = 0;
	while (idx < program->philos_num)
	{
		pthread_t philosopher_thread;
		pthread_create(&philosopher_thread, NULL, philos_routine, &program->philosophers[idx]);
		idx++;
	}
	pthread_join(monitor_thread, NULL);
}
