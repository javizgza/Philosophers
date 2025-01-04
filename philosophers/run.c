/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javierzaragozatejeda <javierzaragozatej    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 11:55:57 by jazarago          #+#    #+#             */
/*   Updated: 2025/01/04 19:18:57 by javierzarag      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	get_current_time(void)
{
	struct timeval	tv;
	
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

void	*death_logic(void *arg)
{
	t_mutex	*program;
	
	program = (t_mutex *)arg;
	usleep(1000); // Add a small delay to allow philosophers to start
	while (1)
	{
		for (int i = 0; i < program->philos_num; i++)
		{
			pthread_mutex_lock(program->dead_value_lock);
			if (program->death_value)
			{
				pthread_mutex_unlock(program->dead_value_lock);
				return NULL;
			}
			pthread_mutex_unlock(program->dead_value_lock);

			pthread_mutex_lock(&program->philosophers[i].meal_time_lock);
			if (get_current_time() - program->philosophers[i].last_meal_time > program->philosophers[i].time_to_die)
			{
				pthread_mutex_unlock(&program->philosophers[i].meal_time_lock);
				pthread_mutex_lock(program->output_lock);
				printf("%d has died\n", program->philosophers[i].who);
				pthread_mutex_unlock(program->output_lock);

				pthread_mutex_lock(program->dead_value_lock);
				program->death_value = 1;
				pthread_mutex_unlock(program->dead_value_lock);
				return NULL;
			}
			pthread_mutex_unlock(&program->philosophers[i].meal_time_lock);
		}
		usleep(1000);
	}
}

void    *philos_routine(void *arg)
{
	t_philoutils	*philosopher;
	int				meals_eaten;
	
	meals_eaten = 0;

	philosopher = (t_philoutils *)arg;
	philosopher->last_meal_time = get_current_time(); // Initialize last_meal_time correctly
	while (1)
	{
		pthread_mutex_lock(philosopher->program->dead_value_lock);
		if (philosopher->program->death_value)
		{
			pthread_mutex_unlock(philosopher->program->dead_value_lock);
			break;
		}
		pthread_mutex_unlock(philosopher->program->dead_value_lock);

		if (philosopher->who % 2 == 0)
		{
			pthread_mutex_lock(philosopher->right_fork);
			pthread_mutex_lock(philosopher->left_fork);
		}
		else
		{
			pthread_mutex_lock(philosopher->left_fork);
			pthread_mutex_lock(philosopher->right_fork);
		}
		pthread_mutex_lock(philosopher->print);
		printf("%d has taken a fork\n", philosopher->who);
		printf("%d has taken a fork\n", philosopher->who);
		printf("%d is eating\n", philosopher->who);
		pthread_mutex_unlock(philosopher->print);
		/*pthread_mutex_unlock(philosopher->right_fork);
		pthread_mutex_unlock(philosopher->left_fork);*/
		pthread_mutex_lock(&philosopher->meal_time_lock);
		philosopher->last_meal_time = get_current_time();
		usleep(philosopher->time_to_eat * 1000);
		meals_eaten++;
		pthread_mutex_unlock(&philosopher->meal_time_lock);
		pthread_mutex_unlock(philosopher->right_fork);
		pthread_mutex_unlock(philosopher->left_fork);
		if (philosopher->meals != -1 && meals_eaten >= philosopher->meals)
			break;
		pthread_mutex_lock(philosopher->print);
		printf("%d is sleeping\n", philosopher->who);
		pthread_mutex_unlock(philosopher->print);
		usleep(philosopher->time_to_sleep * 1000);
		pthread_mutex_lock(philosopher->print);
		printf("%d is thinking\n", philosopher->who);
		pthread_mutex_unlock(philosopher->print);
	}
	pthread_mutex_unlock(philosopher->right_fork);
	pthread_mutex_unlock(philosopher->left_fork);
	return NULL;
}

void    run_inputs(t_philoutils *inputs, char **argv)
{
	for (int i = 0; i < ft_mini_atoi(argv[1]); i++)
	{
		inputs[i].philos_num = ft_mini_atoi(argv[1]);
		inputs[i].time_to_die = ft_mini_atoi(argv[2]);
		inputs[i].time_to_eat = ft_mini_atoi(argv[3]);
		inputs[i].time_to_sleep = ft_mini_atoi(argv[4]);
		if (argv[5])
			inputs[i].meals = ft_mini_atoi(argv[5]);
		else
			inputs[i].meals = -1;
	}
}

void    run_program(t_mutex *program, t_philoutils *inputs)
{
	program->philosophers = inputs;
	program->philos_num = inputs->philos_num; // Set philos_num in program
	program->death_value = 0;
	program->dead_value_lock = malloc(sizeof(pthread_mutex_t));
	program->output_lock = malloc(sizeof(pthread_mutex_t));
	program->food_lock = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(program->dead_value_lock, NULL);
	pthread_mutex_init(program->output_lock, NULL);
	pthread_mutex_init(program->food_lock, NULL);

	pthread_mutex_t *forks = malloc(sizeof(pthread_mutex_t) * program->philos_num);
	for (int i = 0; i < program->philos_num; i++)
	{
		pthread_mutex_init(&forks[i], NULL);
	}

	for (int i = 0; i < program->philos_num; i++)
	{
		inputs[i].who = i + 1; // Start numbering from 1
		inputs[i].right_fork = &forks[i];
		inputs[i].left_fork = &forks[(i + 1) % program->philos_num];
		inputs[i].print = program->output_lock;
		inputs[i].last_meal_time = get_current_time(); // Initialize last_meal_time correctly
		inputs[i].program = program; // Pass the program struct to each philosopher
		pthread_mutex_init(&inputs[i].meal_time_lock, NULL); // Initialize meal_time_lock
	}

	pthread_t monitor_thread;
	pthread_create(&monitor_thread, NULL, death_logic, program);
	// Create philosopher threads
	for (int i = 0; i < program->philos_num; i++)
	{
		pthread_t philosopher_thread;
		pthread_create(&philosopher_thread, NULL, philos_routine, &program->philosophers[i]);
	}
	pthread_join(monitor_thread, NULL); // Wait for the monitor thread to finish

	// Clean up resources
	for (int i = 0; i < program->philos_num; i++)
	{
		pthread_mutex_destroy(&forks[i]);
		pthread_mutex_destroy(&inputs[i].meal_time_lock); // Destroy meal_time_lock
	}
	free(forks);
	pthread_mutex_destroy(program->dead_value_lock);
	pthread_mutex_destroy(program->output_lock);
	pthread_mutex_destroy(program->food_lock);
	free(program->dead_value_lock);
	free(program->output_lock);
	free(program->food_lock);
}
