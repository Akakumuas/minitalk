/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mia <mia@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 19:40:28 by mia               #+#    #+#             */
/*   Updated: 2022/12/16 23:50:02 by mia              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_data
{
    int received_bit;
}   t_data;

size_t	ft_strlen(const char *s);
int		ft_atoi(const char *str);
char	*ft_strdup(const char *s);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

void	ft_received_bit(int signum);
void	ft_received_message(int signum);
void	ft_send_char(int pid, char c);
void	ft_send_message(int pid, char *message);
void	get_message(int signum, siginfo_t *info, void *context);
void	stock_message(char c, int client_pid);
char	*print_message(char *str);


#endif