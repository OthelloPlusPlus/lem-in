/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohengelm <ohengelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 13:38:41 by ohengelm          #+#    #+#             */
/*   Updated: 2026/05/15 20:14:20 by ohengelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>	// va_list
#include <errno.h>	// errno
#include <string.h>	// strerror
#include <stdlib.h>	// exit

#include <libft.h>
#include <colors.h>

void	error_exit(int __status, const char *msg, ...)
{
	va_list	args;

	va_start(args, msg);
	if (__status != 0)
		ft_dprintf(2, "#! "C_RED"Error:"C_RESET" ");
	ft_vdprintf(2, msg, args);
	va_end(args);
	ft_dprintf(2, "\n");
	if (errno > 0)
		ft_dprintf(2, "#! %i: %s\n", errno, strerror(errno));
	if (__status == 0)
		__status += errno;
	exit(__status);
}
