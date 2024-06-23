/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacobs <bjacobs@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 11:55:04 by bjacobs           #+#    #+#             */
/*   Updated: 2022/12/10 11:57:13 by bjacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_FD_H
# define FT_PRINTF_FD_H

int	print_c(char c, int fd);
int	print_s(char *s, int fd);
int	print_u(unsigned int n, int fd);
int	print_x(unsigned int n, char c, int fd);
int	print_d(int n, int fd);
int	print_p(unsigned long long n, int fd);

#endif
