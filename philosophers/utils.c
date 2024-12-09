/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jazarago <jazarago@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 13:01:10 by jazarago          #+#    #+#             */
/*   Updated: 2024/11/27 13:11:03 by jazarago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"

int ft_sleep(size_t ms)
{
    size_t start;

    start = gettimeofday(ms, start);
    while (gettimeofday(ms, start) - start < ms)
        usleep(100);
    return(0);
}