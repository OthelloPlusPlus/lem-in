/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect_links.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohengelm <ohengelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 19:14:20 by ohengelm          #+#    #+#             */
/*   Updated: 2026/05/26 18:49:37 by ohengelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>	// NULL

#include "common.h"

static void	add_rooms_to_links(t_link* link, t_room* list);
static void	add_links_to_rooms(t_room* room, t_link* links);
static int	count_links_containing_room(t_room* room, t_link* link);
static void	add_links_to_array(t_room* room, t_link* link);

void	connect_links(t_farm* farm)
{
	add_rooms_to_links(farm->links, farm->rooms.list);
	add_links_to_rooms(farm->rooms.list, farm->links);
}

static void	add_rooms_to_links(t_link* link, t_room* list)
{
	while (link != NULL)
	{
		link->room1 = find_room_by_name(list, link->name1);
		if (link->room1 == NULL)
			error_exit(ERR_ROOM_LINK(link->name1, link->name2));
		link->room2 = find_room_by_name(list, link->name2);
		if (link->room2 == NULL)
			error_exit(ERR_ROOM_LINK(link->name2, link->room1->name));
		link = link->next;
	}
}

static void	add_links_to_rooms(t_room* room, t_link* links)
{
	int	count;

	while (room != NULL)
	{
		count = count_links_containing_room(room, links);
		room->links = ft_calloc(count + 1, sizeof(t_link*));
		if (room->links == NULL)
			error_exit(ERR_CALLOC);
		add_links_to_array(room, links);
		room = room->next;
	}
}

static int	count_links_containing_room(t_room* room, t_link* link)
{
	int	count;

	count = 0;
	while (link != NULL)
	{
		if (room == link->room1 || room == link->room2)
			++count;
		link = link->next;
	}
	return (count);
}

static void	add_links_to_array(t_room* room, t_link* link)
{
	int	i;

	i = 0;
	while (link != NULL)
	{
		if (link->room1 == room)
			room->links[i++] = link->room2;
		else if (link->room2 == room)
			room->links[i++] = link->room1;
		link = link->next;
	}
}
