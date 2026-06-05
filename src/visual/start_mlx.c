/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohengelm <ohengelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 20:08:32 by ohengelm          #+#    #+#             */
/*   Updated: 2026/05/15 18:26:16 by ohengelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>	// access
#include <stdlib.h>	// malloc, free, exit

#include "lem_in_visual.h"

static void				adjust_window_size(mlx_t* mlx);
static void				load_textures(t_png* png);
static mlx_texture_t*	load_png(size_t count, ...);
static void				shift_array(mlx_texture_t* texture);
static void				add_background(t_visual* visual);

void	start_mlx(t_visual* visual)
{
	visual->mlx = mlx_init(100, 100, "LEM-IN", false);
	adjust_window_size(visual->mlx);
	load_textures(&visual->png);
	add_background(visual);
}

static void	adjust_window_size(mlx_t* mlx)
{
	int32_t	w;
	int32_t	h;

	mlx_get_monitor_size(0, &w, &h);
	mlx_set_window_size(mlx, w / 3, h / 2);
}

static void	load_textures(t_png* png)
{
	png->background = load_png(1, "assets/img/background.png");
	png->ant = load_png(1, "assets/img/ant.png");
	png->room = load_png(1, "assets/img/room.png");
	png->start = load_png(2, "assets/img/start.png", "assets/img/end.png");
	if (png->start == NULL)
	{
		png->start = load_png(1, "assets/img/room.png");
		shift_array(png->start);
	}
	png->end = load_png(2, "assets/img/end.png", "assets/img/start.png");
	if (png->end == NULL)
	{
		png->end = load_png(1, "assets/img/room.png");
		shift_array(png->end);
	}
}

static mlx_texture_t*	load_png(size_t count, ...)
{
	va_list	ap;
	char*	path;

	va_start(ap, count);
	while (count > 0)
	{
		path = va_arg(ap, char*);
		if (!access(path, R_OK))
			return (mlx_load_png(path));
		--count;
	}
	return (NULL);
}

static void	shift_array(mlx_texture_t* texture)
{
	uint32_t*	pixels;
	uint32_t	bytesx4;
	uint32_t	i;

	if (texture == NULL)
		return ;
	pixels = (uint32_t*)texture->pixels;
	i = 0;
	bytesx4 = texture->height * texture->width;
	while (i < bytesx4)
	{
		pixels[i] = ((pixels[i] & 0xFFFFFF00) << 1) | (pixels[i] & 0xFF);
		++i;
	}
}

static void	add_background(t_visual* visual)
{
	if (visual->png.background != NULL)
		visual->img.background = mlx_texture_to_image(visual->mlx, visual->png.background);
	else
	{
		visual->img.background = mlx_new_image(visual->mlx, 1, 1);
		mlx_put_pixel(visual->img.background, 0, 0, rgb(64, 32, 0));
	}
	mlx_resize_image(visual->img.background, visual->mlx->width, visual->mlx->height);
	mlx_image_to_window(visual->mlx, visual->img.background, 0, 0);
}
