/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_links.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohengelm <ohengelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 19:00:32 by ohengelm          #+#    #+#             */
/*   Updated: 2026/05/26 18:40:56 by ohengelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>	// NULL

#include "common.h"

static void	print_header(t_link* links);
static void	print_link(t_link* link);

void	print_links(t_link* links)
{
	print_header(links);
	while (links != NULL)
	{
		print_link(links);
		links = links->next;
	}
}

static void	print_header(t_link* links)
{
	u_int32_t	count;

	count = 0;
	while (links != NULL)
	{
		++count;
		links = links->next;
	}
	ft_printf("\n# Links %u\n", count);
}

static void	print_link(t_link* link)
{
	ft_printf("%s-%s\n", link->name1, link->name2);
}
