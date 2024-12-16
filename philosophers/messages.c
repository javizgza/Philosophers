/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jazarago <jazarago@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 13:29:30 by jazarago          #+#    #+#             */
/*   Updated: 2024/12/16 13:30:20 by jazarago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void    think(t_philoutils *philo)
{
    pthread_mutex_lock(philo->print);
    printf("%d is thinking\n", philo->who);
    pthread_mutex_unlock(philo->print);
}

void    eat(t_philoutils *philo)
{
    pthread_mutex_lock(philo->print);
    printf("%d is eating\n", philo->who);
    pthread_mutex_unlock(philo->print);
}

void    sleep(t_philoutils *philo)
{
    pthread_mutex_lock(philo->print);
    printf("%d is sleeping\n", philo->who);
    pthread_mutex_unlock(philo->print);
}

void    dead(t_philoutils *philo)
{
    pthread_mutex_lock(philo->print);
    printf("%d died\n", philo->who);
    pthread_mutex_unlock(philo->print);
}

