/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_visuals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohengelm <ohengelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 20:49:27 by ohengelm          #+#    #+#             */
/*   Updated: 2026/05/28 20:58:18 by ohengelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in_visual.h"

static void	delete_pngs(t_png* png);
static void delete_texture(mlx_texture_t* texture);
static void	delete_images(mlx_t* mlx, t_img* img, t_ant* ant);

void	delete_visuals(t_visual* visual, t_ants* ants)
{
	delete_pngs(&visual->png);
	delete_images(visual->mlx, &visual->img, ants->ants);
}

static void	delete_pngs(t_png* png)
{
	delete_texture(png->background);
	delete_texture(png->start);
	delete_texture(png->room);
	delete_texture(png->end);
	delete_texture(png->ant);
}

static void delete_texture(mlx_texture_t* texture)
{
	if (texture != NULL)
		mlx_delete_texture(texture);
}

static void	delete_images(mlx_t* mlx, t_img* img, t_ant* ant)
{
	mlx_delete_image(mlx, img->background);
	mlx_delete_image(mlx, img->start);
	mlx_delete_image(mlx, img->room);
	mlx_delete_image(mlx, img->end);
	mlx_delete_image(mlx, img->mode);
	mlx_delete_image(mlx, img->info_ants);
	mlx_delete_image(mlx, img->info_turns);
	mlx_delete_image(mlx, img->pause);
	while (ant != NULL)
	{
		mlx_delete_image(mlx, ant->img);
		ant = ant->next;
	}
}
