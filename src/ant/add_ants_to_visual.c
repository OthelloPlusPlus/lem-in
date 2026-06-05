/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_ants_to_visual.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohengelm <ohengelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 20:16:58 by ohengelm          #+#    #+#             */
/*   Updated: 2026/06/04 19:06:28 by ohengelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>	// malloc, free, exit

#include "lem_in_visual.h"

static void	calc_txtr_size(mlx_texture_t* png, t_rooms* rooms, xyz_u* size);
static void	tattoo_ant(mlx_t* mlx, mlx_image_t* ant, u_int32_t id);
static void	tatoo_stencil(mlx_image_t* dst, mlx_image_t* src);
static void	adjust_ant_z_axis(t_ant* ants);

void	add_ants_to_visual(t_farm* farm, t_visual* visual)
{
	t_ant*	ant;
	xyz_u	size;

	ant = farm->ants.ants;
	calc_txtr_size(visual->png.ant, &farm->rooms, &size);
	while (ant != NULL)
	{
		if (visual->png.ant)
			ant->img = mlx_texture_to_image(visual->mlx, visual->png.ant);
		else
		{
			ant->img = mlx_new_image(visual->mlx, 1, 1);
			mlx_put_pixel(ant->img, 0, 0, rgb(123, 0, 123));
			mlx_resize_image(ant->img, size.w, size.h);
		}
		mlx_resize_image(ant->img, size.w, size.h);
		tattoo_ant(visual->mlx, ant->img, ant->id);
		ant->inst = mlx_image_to_window(visual->mlx, ant->img, 0, 0);
		center_image(ant->img, 0, ant->x, ant->y);
		ant->room = NULL;
		ant->img->enabled = false;
		ant = ant->next;
	}
	adjust_ant_z_axis(farm->ants.ants);
}

static void	calc_txtr_size(mlx_texture_t* png, t_rooms* rooms, xyz_u* size)
{
	double	ratio;
	double	comp;

	// Set maximum size for texture
	size->w = rooms->w;
	size->h = rooms->h;
	if (png != NULL)
	{
		// Adjust size to texture size
		size->w = ft_min(png->width, rooms->w);
		size->h = ft_min(png->height, rooms->h);
		// Calculate ratio of texture
		ratio = (double) png->width / png->height;
	}
	else
		// set default ratio
		ratio = 0.69;
	// Adjust size to match texture ratio
	comp = (double) size->w / size->h;
	if (comp > ratio)
		size->w = size->h * ratio;
	if (comp < ratio)
		size->h = size->w / ratio;
}

static void	tattoo_ant(mlx_t* mlx, mlx_image_t* ant, u_int32_t id)
{
	mlx_image_t*	stencil;
	char*			design;

	design = ft_itoa(id);
	stencil = mlx_put_string(mlx, design, 0, 0);
	free(design);
	scale_image_to(stencil, ant->width / 3, ant->height / 3);
	tatoo_stencil(ant, stencil);
	mlx_delete_image(mlx, stencil);
}

static void	tatoo_stencil(mlx_image_t* dst, mlx_image_t* src)
{
	uint32_t*	pixels;
	uint32_t	top;
	uint32_t	left;
	uint32_t	i;
	uint32_t	max;
	uint32_t	a;

	pixels = (uint32_t *)src->pixels;
	top = 0;
	if (dst->height > src->height)
		top = (dst->height - src->height) / 2;
	left = 0;
	if (dst->width > src->width)
		left = (dst->width - src->width) / 2;
	i = 0;
	max = src->width * src->height;
	while (i < max)
	{
		a = (pixels[i] >> 24) & 0xFF;
		if (a)
			mlx_put_pixel(dst, left + i % src->width, top + i / src->width, rgb(0, a, 0));
		++i;
	}
}

static void	adjust_ant_z_axis(t_ant* ant)
{
	int32_t	z;

	if (ant == NULL)
		return ;
	z = ant->img->instances[ant->inst].z;
	while (ant->next != NULL)
	{
		z = ft_min(z, ant->next->img->instances[ant->next->inst].z);
		ant = ant->next;
	}
	while (ant != NULL)
	{
		ant->img->instances[ant->inst].z = z++;
		ant = ant->prev;
	}
}
