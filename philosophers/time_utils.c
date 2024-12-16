/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jazarago <jazarago@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 13:18:15 by jazarago          #+#    #+#             */
/*   Updated: 2024/12/16 13:22:07 by jazarago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void get_current_time(void)
{
    struct timeval tv;
    struct tm *tm_info;

    gettimeofday(&tv, NULL);

    tm_info = localtime(&tv.tv_sec);

    printf("Hora actual: %02d:%02d:%02d.%06ld\n",
           tm_info->tm_hour, tm_info->tm_min, tm_info->tm_sec, tv.tv_usec);
}


