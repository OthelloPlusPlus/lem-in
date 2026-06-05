/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_links.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohengelm <ohengelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 17:18:17 by ohengelm          #+#    #+#             */
/*   Updated: 2026/05/28 19:17:40 by ohengelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>	// comparison of integers of different signs

#include "lem_in_visual.h"

static void	draw_link(mlx_image_t *img, t_link* link, uint32_t weight, uint32_t col);
static void	prep_line(xyz_u* line, t_link* link, int* sx, int* sy);
static void	place_pixels(mlx_image_t* img, xyz_u* line, uint32_t weight, uint32_t col);
static void	advance_line_pos(xyz_u* line, int* err, int sx, int sy);

void	draw_links(t_farm* farm, t_img* img)
{
	t_link*		link;
	uint32_t	color;
	uint32_t	weight;

	link = farm->links;
	color = rgb(192, 144, 95);
	weight = ft_min(img->room->width, img->room->height) / 4;
	while (link != NULL)
	{
		draw_link(img->background, link, weight, color);
		link = link->next;
	}
}

/**
 * Draws a weighted connection (link) between two rooms as a discrete line
 * rendered onto an mlx image.
 *
 * @param[in] img     Target mlx image buffer.
 * @param[in] link    Link containing the two room endpoints.
 * @param[in] weight  Thickness of the rendered line.
 * @param[in] col     RGBA color used for drawing.
 * 
 * @note ChatGPT assisted design.
 */
static void	draw_link(mlx_image_t *img, t_link* link, uint32_t weight, uint32_t col)
{
	xyz_u	line;
	int		sx;
	int		sy;
	int		err;

	prep_line(&line, link, &sx, &sy);
	err = line.w - line.h;
	while (true)
	{
		place_pixels(img, &line, weight, col);
		if (line.x == link->room2->x && line.y == link->room2->y)
			break ;
		advance_line_pos(&line, &err, sx, sy);
	}
}

static void	prep_line(xyz_u* line, t_link* link, int* sx, int* sy)
{
	line->x = link->room1->x;
	line->y = link->room1->y;
	line->w = abs((int)link->room2->x - (int)line->x);
	line->h = abs((int)link->room2->y - (int)line->y);
	*sx = -1;
	if (line->x < link->room2->x)
		*sx = 1;
	*sy = -1;
	if (line->y < link->room2->y)
		*sy = 1;
}

/**
 * Advances a point along a discrete line toward its target.
 *
 * This performs one iteration of a raster line algorithm
 * (Bresenham-style), updating the current position based on
 * an accumulated error term. It decides whether to step in
 * x, y, or both directions to approximate a straight line
 * on a pixel grid.
 *
 * @param[in,out] line  Current point being advanced.
 * @param[in,out] err   Accumulated error term controlling direction changes.
 * @param[in] sx        Step direction in x (-1 or +1).
 * @param[in] sy        Step direction in y (-1 or +1).
 *
 * @note https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
 */
static void	advance_line_pos(xyz_u* line, int* err, int sx, int sy)
{
	int	e2;

	e2 = (*err) * 2;
	if (e2 > -(int)line->h)
	{
		*err -= line->h;
		line->x += sx;
	}
	if (e2 < (int)line->w)
	{
		*err += line->w;
		line->y += sy;
	}
}

static void place_pixels(mlx_image_t* img, xyz_u* line, uint32_t weight, uint32_t col)
{
	bool	steep;
	int		start;
	int		end;
	int		x;
	int		y;

	steep = line->h > line->w;
	end = weight / 2;
	start = -end;
	while (start <= end)
	{
		x = line->x;
		y = line->y;
		if (steep)
			x += start;
		else
			y += start;
		if (x >= 0 && x < (int)img->width && \
			y >= 0 && y < (int)img->height)
			mlx_put_pixel(img, x, y, col);
		++start;
	}
}
