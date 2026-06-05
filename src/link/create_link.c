/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_link.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohengelm <ohengelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 18:48:54 by ohengelm          #+#    #+#             */
/*   Updated: 2026/05/15 18:09:19 by ohengelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>	// malloc, free, exit

#include "common.h"

t_link* create_link(char* name1, char* name2)
{
	t_link*	link;

	if (name1 == NULL || name2 == NULL)
		return (NULL);
	link = ft_calloc(1, sizeof(t_link));
	if (link == NULL)
		return (NULL);
	link->name1 = ft_strdup(name1);
	link->name2 = ft_strdup(name2);
	if (link->name1 == NULL || link->name2 == NULL)
	{
		free(link->name1);
		free(link->name2);
		free(link);
		return (NULL);
	}
	return (link);
}
