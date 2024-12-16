/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jazarago <jazarago@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 10:56:50 by jazarago          #+#    #+#             */
/*   Updated: 2024/12/16 13:19:24 by jazarago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{	
	if (argc != 5 && argc != 6)
		return (write(1, "Wrong number of arguments.\n", 27));
	if (check_all_args(argv) == 1)
		return (1);
	
}