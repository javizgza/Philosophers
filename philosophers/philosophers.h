/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javierzaragozatejeda <javierzaragozatej    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:17:00 by jazarago          #+#    #+#             */
/*   Updated: 2025/01/04 18:17:07 by javierzarag      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

// Forward declaration of t_mutex
typedef struct s_mutex t_mutex;

typedef struct s_philoutils
{
    pthread_t        *thread;
    int              philos_num;
    int              who;
    int              time_to_die;
    int              time_to_eat;
    int              time_to_sleep;
    int              meals;
    long             last_meal_time; // Changed to long for consistency with get_current_time
    pthread_mutex_t  *right_fork;
    pthread_mutex_t  *left_fork;
    pthread_mutex_t  *food_dish;
    pthread_mutex_t  *dead;
    pthread_mutex_t  *print;
    pthread_mutex_t  meal_time_lock; // Add meal_time_lock
    t_mutex          *program; // Add reference to program struct
    int              meals_eaten; // Add meals_eaten to track the number of meals eaten
}           t_philoutils;

typedef struct s_mutex
{
    int              death_value;
    int              philos_num; // Added philos_num to s_mutex
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
long get_current_time(void);
void    *death_logic(void   *arg);

#endif
