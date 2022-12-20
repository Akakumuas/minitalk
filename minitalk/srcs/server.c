/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mia <mia@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 03:59:23 by mia               #+#    #+#             */
/*   Updated: 2022/12/16 23:33:02 by mia              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void    get_message(int signum, siginfo_t *info, void *context)
{
    static unsigned char c = 0;
    static unsigned char bit = 128;

    (void)context;
    if (signum == SIGUSR1)
        c |= bit;
    if (bit == 1)
    {
        stock_message(c, info->si_pid);
        c = 0;
        bit = 128;
    }
    else
        bit /= 2;
    kill(info->si_pid, SIGUSR2);
}

void    stock_message(char c, int client_pid)
{
    static char *str = NULL;
    char    *dst;
    int     i;

    i = 0;
    dst = malloc(sizeof(char) * (ft_strlen(str) + 2));
    if (!dst)
        return ;
    if (str)
    {
        while (str[i])
        {
            dst[i] = str[i];
            i++;
        }
        free(str);
    }
    dst[i++] = c;
    dst[i] = 0;
    str = ft_strdup(dst);
    if (!c)
    {
        str = print_message(str);
        kill(client_pid, SIGUSR1);
    }
}

char *print_message(char *str)
{
    int i;

    i = -1;
    while (str[++i])
	    ft_putchar_fd(str[i], 1);
	ft_putchar_fd('\n', 1);
	free(str);
	return (NULL);
}

int main (void)
{
    struct sigaction sa;

    sa.sa_sigaction = get_message;
    sa.sa_flags = SA_SIGINFO;
    sigemptyset( &sa.sa_mask );
	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
    sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
    while (1)
        pause();
}