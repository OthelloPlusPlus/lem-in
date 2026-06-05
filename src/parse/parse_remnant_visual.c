/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_remnant_visual.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohengelm <ohengelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 17:02:53 by ohengelm          #+#    #+#             */
/*   Updated: 2026/04/23 18:55:49 by ohengelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in_visual.h"

void	parse_remnant_visual(t_ss* ss)
{
	t_storage*	s;
	t_storage*	temp;

	s = ss->farm.storage;
	while (s != NULL)
	{
		if (parse_moves(ss, s->array) || \
			false)
		{
			temp = s->next;
			remove_from_storage(&ss->farm.storage, s);
			s = temp;
		}
		else
			s = s->next;
	}
}
