/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_links.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohengelm <ohengelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 19:26:59 by ohengelm          #+#    #+#             */
/*   Updated: 2026/05/15 18:09:42 by ohengelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>	// malloc, free, exit

#include "common.h"

static void	delete_link(t_link* link);

void	delete_links(t_farm* farm)
{
	t_link*	link;
	t_link*	temp;

	link = farm->links;
	while (link != NULL)
	{
		temp = link;
		link = link->next;
		delete_link(temp);
	}
	farm->links = NULL;
}

static void	delete_link(t_link* link)
{
	free(link->name1);
	free(link->name2);
	free(link);
}
