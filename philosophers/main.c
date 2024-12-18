/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javierzaragozatejeda <javierzaragozatej    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 10:56:50 by jazarago          #+#    #+#             */
/*   Updated: 2024/12/18 13:37:01 by javierzarag      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{	
	t_philoutils	*inputs;
	t_mutex			program;
	pthread_t		*threads;
	int				i;

	if (argc != 5 && argc != 6)
		return (write(1, "Wrong number of arguments.\n", 27));
	if (check_all_args(argv) == 1) 
		return (1);
	
	inputs = malloc(sizeof(t_philoutils) * ft_mini_atoi(argv[1]));
	if (!inputs)
		return (1);
	run_inputs(&inputs[0], argv);
	run_program(&program, &inputs[0]);

	threads = malloc(sizeof(pthread_t) * inputs[0].philos_num);
	if (!threads)
		return (1);
	i = 0;
	while (i < inputs[0].philos_num)
	{
		inputs[i] = inputs[0];
		inputs[i].who = i + 1;
		if (pthread_create(&threads[i], NULL, philos_routine, &inputs[i]) != 0)
			return (1);
		i++;
	}
	i = 0;
	while (i < inputs[0].philos_num)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	free(threads);
	pthread_mutex_destroy(program.dead_value_lock);
	pthread_mutex_destroy(program.output_lock);
	pthread_mutex_destroy(program.food_lock);
	free(program.dead_value_lock);
	free(program.output_lock);
	free(program.food_lock);
	free(inputs);

	return (0);
}
