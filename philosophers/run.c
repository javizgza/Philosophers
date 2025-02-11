/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javierzaragozatejeda <javierzaragozatej    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 11:55:57 by jazarago          #+#    #+#             */
/*   Updated: 2025/02/04 16:55:55 by javierzarag      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	start_time;

long	get_current_time(void)
{
	struct timeval	tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

long	get_elapsed_time(void)
{
	return get_current_time() - start_time;
}

void precise_usleep(long duration_ms) {
    long start_time = get_current_time();
    while ((get_current_time() - start_time) < duration_ms) {
        usleep(100);
    }
}

void	*death_logic(void *arg)
{
	t_mutex	*program;
	int		idx;

	program = (t_mutex *)arg;
	usleep(5000);
	while (1)
	{
		idx = 0;
		while (idx < program->philos_num)
		{
			pthread_mutex_lock(program->dead_value_lock);
			if (program->death_value)
			{
				pthread_mutex_unlock(program->dead_value_lock);
				return NULL;
			}
			if (program->finished_meals_count == program->philos_num)
			{
				pthread_mutex_unlock(program->dead_value_lock);
				return NULL;
			}
			pthread_mutex_unlock(program->dead_value_lock);
			pthread_mutex_lock(&program->philosophers[idx].meal_time_lock);
			if (get_current_time() - program->philosophers[idx].last_meal_time > program->philosophers[idx].time_to_die)
			{
				pthread_mutex_unlock(&program->philosophers[idx].meal_time_lock);
				pthread_mutex_lock(program->output_lock);
				printf("%ld %d died\n", get_elapsed_time(), program->philosophers[idx].who);
				pthread_mutex_unlock(program->output_lock);
				pthread_mutex_lock(program->dead_value_lock);
				program->death_value = 1;
				pthread_mutex_unlock(program->dead_value_lock);
				return NULL;
			}
			pthread_mutex_unlock(&program->philosophers[idx].meal_time_lock);
			idx++;
		}
		usleep(1000);
	}
}

void    *philos_routine(void *arg)
{
	t_philoutils	*philosopher;
	int				meals_eaten;

	philosopher = (t_philoutils *)arg;
	meals_eaten = 0;

	philosopher->last_meal_time = get_current_time();
	if (philosopher->who % 2 != 0)
		usleep(1000);
	while (1)
	{
		pthread_mutex_lock(philosopher->program->dead_value_lock);
		if (philosopher->program->death_value)
			break ;
		pthread_mutex_unlock(philosopher->program->dead_value_lock);
		if (philosopher->program->death_value)
			break ;
		precise_usleep(1);
		if (philosopher->program->death_value)
			break ;
		pthread_mutex_lock(philosopher->right_fork);
		if (philosopher->program->death_value)
			break ;
		pthread_mutex_lock(philosopher->left_fork);
		if (philosopher->program->death_value)
			break ;
		pthread_mutex_lock(philosopher->print);
		if (philosopher->program->death_value)
			break ;
		printf("%ld %d has taken a fork\n", get_elapsed_time(), philosopher->who);
		printf("%ld %d has taken a fork\n", get_elapsed_time(), philosopher->who);
		printf("%ld %d is eating\n", get_elapsed_time(), philosopher->who);
		pthread_mutex_unlock(philosopher->print);
		if (philosopher->program->death_value)
			break ;
		pthread_mutex_lock(&philosopher->meal_time_lock);
		if (philosopher->program->death_value)
			break ;
		philosopher->last_meal_time = get_current_time();
		precise_usleep(philosopher->time_to_eat);
		meals_eaten++;
		if (philosopher->program->death_value)
			break ;
		pthread_mutex_unlock(&philosopher->meal_time_lock);
		if (philosopher->program->death_value)
			break ;
		pthread_mutex_unlock(philosopher->right_fork);
		pthread_mutex_unlock(philosopher->left_fork);
		if (philosopher->meals != -1 && meals_eaten >= philosopher->meals)
		{
			pthread_mutex_lock(philosopher->program->dead_value_lock);
			philosopher->program->finished_meals_count++;
			pthread_mutex_unlock(philosopher->program->dead_value_lock);
			break;
		}
		if (philosopher->program->death_value)
			break ;
		pthread_mutex_lock(philosopher->print);
		if (philosopher->program->death_value)
			break ;
		printf("%ld %d is sleeping\n", get_elapsed_time(), philosopher->who);
		pthread_mutex_unlock(philosopher->print);
		if (philosopher->program->death_value)
			break ;
		precise_usleep(philosopher->time_to_sleep);
		if (philosopher->program->death_value)
			break ;
		pthread_mutex_lock(philosopher->print);
		if (philosopher->program->death_value)
			break ;
		printf("%ld %d is thinking\n", get_elapsed_time(), philosopher->who);
		pthread_mutex_unlock(philosopher->print);
		if (philosopher->program->death_value)
			break ;
		if (philosopher->meals != -1 && meals_eaten >= philosopher->meals)
			break;
	}
	pthread_mutex_unlock(philosopher->right_fork);
	pthread_mutex_unlock(philosopher->left_fork);
	return NULL;
}

void    run_inputs(t_philoutils *inputs, char **argv)
{
	int i = 0;
	while (i < ft_mini_atoi(argv[1]))
	{
		inputs[i].philos_num = ft_mini_atoi(argv[1]);
		inputs[i].time_to_die = ft_mini_atoi(argv[2]);
		inputs[i].time_to_eat = ft_mini_atoi(argv[3]);
		inputs[i].time_to_sleep = ft_mini_atoi(argv[4]);
		if (argv[5])
			inputs[i].meals = ft_mini_atoi(argv[5]);
		else
			inputs[i].meals = -1;
		i++;
	}
}

void    run_program(t_mutex *program, t_philoutils *inputs)
{
	int i;

	start_time = get_current_time(); // Capture the start time

	program->philosophers = inputs;
	program->philos_num = inputs->philos_num;
	program->death_value = 0;
	program->finished_meals_count = 0;
	program->dead_value_lock = malloc(sizeof(pthread_mutex_t));
	program->output_lock = malloc(sizeof(pthread_mutex_t));
	program->food_lock = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(program->dead_value_lock, NULL);
	pthread_mutex_init(program->output_lock, NULL);
	pthread_mutex_init(program->food_lock, NULL);

	pthread_mutex_t *forks = malloc(sizeof(pthread_mutex_t) * program->philos_num);
	i = 0;
	while (i < program->philos_num)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}

	i = 0;
	while (i < program->philos_num)
	{
		inputs[i].who = i + 1;
		inputs[i].right_fork = &forks[i];
		inputs[i].left_fork = &forks[(i + 1) % program->philos_num];
		inputs[i].print = program->output_lock;
		inputs[i].last_meal_time = get_current_time();
		inputs[i].program = program;
		pthread_mutex_init(&inputs[i].meal_time_lock, NULL);
		i++;
	}

	pthread_t monitor_thread;
	pthread_create(&monitor_thread, NULL, death_logic, program);
	i = 0;
	while (i < program->philos_num)
	{
		pthread_t philosopher_thread;
		pthread_create(&philosopher_thread, NULL, philos_routine, &program->philosophers[i]);
		i++;
	}
	pthread_join(monitor_thread, NULL);

	i = 0;
	while (i < program->philos_num)
	{
		pthread_mutex_destroy(&forks[i]);
		pthread_mutex_destroy(&inputs[i].meal_time_lock);
		i++;
	}
	free(forks);
	pthread_mutex_destroy(program->dead_value_lock);
	pthread_mutex_destroy(program->output_lock);
	pthread_mutex_destroy(program->food_lock);
	free(program->dead_value_lock);
	free(program->output_lock);
	free(program->food_lock);
}
