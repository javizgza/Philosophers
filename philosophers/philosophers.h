/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javierzaragozatejeda <javierzaragozatej    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:17:00 by jazarago          #+#    #+#             */
/*   Updated: 2024/12/18 11:11:35 by javierzarag      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philoutils
{
    pthread_t        *thread;
    int              philos_num;
    int              who;
    int              time_to_die;
    int              time_to_eat;
    int              time_to_sleep;
    int              meals;
    pthread_mutex_t  *right_fork;
    pthread_mutex_t  *left_fork;
    pthread_mutex_t  *food_dish;
    pthread_mutex_t  *dead;
    pthread_mutex_t  *print;
    
    
}           t_philoutils;

typedef struct s_mutex
{
    int              death_value;
    pthread_mutex_t  *dead_value_lock;
    pthread_mutex_t  *output_lock;
    pthread_mutex_t  *food_lock;

    t_philoutils     *philosophers;
}           t_mutex;


/* FUNCTIONS */
int ft_mini_atoi(char *str);
int	check_all_args(char **argv);
int ft_atoi(char *str);
int check_if_num(char *str);
void    *philos_routine(void *arg);
void    run_inputs(t_philoutils *inputs, char **argv);
void    run_program(t_mutex *program, t_philoutils *inputs);

#endif
