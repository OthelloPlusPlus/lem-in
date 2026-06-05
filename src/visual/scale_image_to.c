/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scale_image_to.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohengelm <ohengelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 16:54:37 by ohengelm          #+#    #+#             */
/*   Updated: 2026/04/24 21:12:39 by ohengelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in_visual.h"

inline static double	calc_scale(double width, double height);

void	scale_image_to(mlx_image_t* img, double width, double height)
{
	double	scale;

	scale = calc_scale(img->width, img->height);
	width = ft_max(img->width, width);
	height = ft_max(img->height, height);
	if (calc_scale(width, height) > scale)
		width = height * scale;
	if (calc_scale(width, height) < scale)
		height = width / scale;
	mlx_resize_image(img, width, height);
}

inline static double	calc_scale(double width, double height)
{
	return (width / height);
}
