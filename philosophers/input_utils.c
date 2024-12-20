/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javierzaragozatejeda <javierzaragozatej    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:13:18 by jazarago          #+#    #+#             */
/*   Updated: 2024/12/18 11:11:35 by javierzarag      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_all_args(char **argv)
{
	if (ft_mini_atoi(argv[1]) <= 0 || check_if_num(argv[1]) == 1)
		return (write(1, "Error in number of philosophers.\n", 33));
	if (ft_mini_atoi(argv[2]) <= 0 || check_if_num(argv[2]) == 1)
		return (write(1, "Error in time to die.\n", 23));
	if (ft_mini_atoi(argv[3]) <= 0 || check_if_num(argv[3]) == 1)
		return (write(1, "Error in time to eat.\n", 23));
	if (ft_mini_atoi(argv[4]) <= 0 || check_if_num(argv[4]) == 1)
		return (write(1, "Error in time to sleep.\n", 25));
	if (argv[5] && (ft_mini_atoi(argv[5]) <= 0 || check_if_num(argv[5]) == 1))
		return (write(1, "Error in number os meals for each philo.\n", 41));

	return (0);
}

int check_if_num(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (1);
		i++;
	}
	return (0);
}

int ft_mini_atoi(char *str)
{
    int res;

    res = 0;
    while (*str >= '0' && *str <= '9')
    {
        res = res * 10 + *str - '0';
        str++;
    }
    return (res);
}
