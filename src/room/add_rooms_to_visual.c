/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_rooms_to_visual.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohengelm <ohengelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 20:50:52 by ohengelm          #+#    #+#             */
/*   Updated: 2026/05/26 16:25:07 by ohengelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in_visual.h"

static void		calculate_range(t_room* room, xyz_u* scope);
static void		adjust_coordinates(t_rooms* rooms, xyz_u* scope);
static uint32_t	calc_coordinate(double pos, uint32_t count, uint32_t size);
static void		add_room_images(t_rooms* rooms, t_visual* visual);
static void		add_room_image(t_visual* visual, t_room* room, t_rooms* rooms);
static mlx_image_t*	create_room_image(mlx_t* mlx, mlx_texture_t* png, t_rooms* rooms);

void	add_rooms_to_visual(t_rooms* rooms, t_visual* visual)
{
	xyz_u	scope;

	calculate_range(rooms->list, &scope);
	visual->step_size = ft_max(scope.w / 2, scope.h / 2);
	visual->step_size = ft_max(visual->step_size, 16);
	rooms->w = ft_max(visual->mlx->width / (scope.w + 2), 1);
	rooms->h = ft_max(visual->mlx->height / (scope.h + 2), 1);
	adjust_coordinates(rooms, &scope);
	add_room_images(rooms, visual);
}

static void	calculate_range(t_room* room, xyz_u* scope)
{
	if (room == NULL)
		return ;
	scope->x = room->x;
	scope->y = room->y;
	scope->w = room->x;
	scope->h = room->y;
	while (room != NULL)
	{
		scope->x = ft_min(scope->x, room->x);
		scope->y = ft_min(scope->y, room->y);
		scope->w = ft_max(scope->w, room->x);
		scope->h = ft_max(scope->h, room->y);
		room = room->next;
	}
	scope->w -= scope->x - 1;
	scope->h -= scope->y - 1;
}

static void	adjust_coordinates(t_rooms* rooms, xyz_u* scope)
{
	t_room*	room;

	room = rooms->list;
	while (room != NULL)
	{
		room->x = calc_coordinate(room->x - scope->x, scope->w, rooms->w);
		room->y = calc_coordinate(room->y - scope->y, scope->h, rooms->h);
		room = room->next;
	}
}

static uint32_t calc_coordinate(double pos, uint32_t count, uint32_t size)
{
	if (count <= 1)
		return (size * 1.5);
	return (size * (1 + pos + (pos / (count - 1))));
}

static void	add_room_images(t_rooms* rooms, t_visual* visual)
{
	t_room*	room;

	visual->img.room = create_room_image(visual->mlx, visual->png.room, rooms);
	visual->img.start = create_room_image(visual->mlx, visual->png.start, rooms);
	visual->img.end = create_room_image(visual->mlx, visual->png.end, rooms);
	room = rooms->list;
	while (room != NULL)
	{
		if (room == rooms->start)
			room->img = visual->img.start;
		else if (room == rooms->end)
			room->img = visual->img.end;
		else
			room->img = visual->img.room;
		add_room_image(visual, room, rooms);
		room = room->next;
	}
}

static void	add_room_image(t_visual* visual, t_room* room, t_rooms* rooms)
{
	room->inst = mlx_image_to_window(visual->mlx, room->img, 0, 0);
	center_image(room->img, room->inst, room->x, room->y);
	room->label = mlx_put_string(visual->mlx, room->name, 0, 0);
	scale_image_to(room->label, rooms->w / 2, rooms->h / 2);
	center_image(room->label, 0, room->x, room->y);
}

static mlx_image_t*	create_room_image(mlx_t* mlx, mlx_texture_t* png, t_rooms* rooms)
{
	mlx_image_t*	img;

	if (png)
		img = mlx_texture_to_image(mlx, png);
	else
	{
		img = mlx_new_image(mlx, 1, 1);
		if (img)
			mlx_put_pixel(img, 0, 0, rgb(255, 0, 0));
	}
	if (img)
		mlx_resize_image(img, rooms->w, rooms->h);
	return (img);
}
