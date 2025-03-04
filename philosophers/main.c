/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javierzaragozatejeda <javierzaragozatej    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 10:56:50 by jazarago          #+#    #+#             */
/*   Updated: 2025/03/04 19:54:12 by javierzarag      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int init_inputs(t_philoutils **inputs, char **argv)
{
    *inputs = malloc(sizeof(t_philoutils) * ft_mini_atoi(argv[1]));
    if (!*inputs)
        return (1);
    run_inputs(&(*inputs)[0], argv);
    return (0);
}

int	main(int argc, char **argv)
{	
	t_philoutils	*inputs;
	t_mutex			program;

	if (argc != 5 && argc != 6)
		return (write(2, "Wrong number of arguments.\n", 27));
	if (check_all_args(argv) == 1) 
		return (1);
	if (init_inputs(&inputs, argv) == 1)
		return (1);
	run_program(&program, inputs);

	free(inputs);
	return (0);
}
