/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mia <mia@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 20:16:40 by mia               #+#    #+#             */
/*   Updated: 2022/12/16 23:20:34 by mia              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_data  g_data;

void    ft_received_bit(int signum)
{
    (void)signum;
    g_data.received_bit = 1;
}

void ft_receive_message(int signum)
{
    if (signum == SIGUSR1)
    {
        ft_putstr_fd("received\n", 1);
        exit(0);
    }
}

void    ft_send_char(int pid, char c)
{
    int i;

    i = 7;
    while (i >= 0)
    {
        if ((c >> i) & 1)
            kill(pid, SIGUSR1);
        else
            kill(pid, SIGUSR2);
        sleep(1);
        while (!g_data.received_bit)
        {
            pause();
            g_data.received_bit = 0;
        }
        i--;
    }
}

void ft_send_message(int pid, char *message)
{
    size_t  i;

    i = -1;
    while (++i <= ft_strlen(message))
        ft_send_char(pid, message[i]);
}

int main(int ac, char **av)
{
    g_data.received_bit = 0;
    signal(SIGUSR1, ft_receive_message);
    signal(SIGUSR2, ft_received_bit);
    if (ac == 3 && !(ft_atoi(av[1]) <= 0))
        ft_send_message(ft_atoi(av[1]), av[2]);
    else
        ft_putstr_fd("Incorrect number of argument", 1);
    return (0);

}