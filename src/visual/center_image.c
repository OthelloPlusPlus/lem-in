/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   center_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohengelm <ohengelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 16:16:03 by ohengelm          #+#    #+#             */
/*   Updated: 2026/04/17 16:18:50 by ohengelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in_visual.h"

void	center_image(mlx_image_t* img, int32_t inst, int32_t posx, int32_t posy)
{
	img->instances[inst].x = posx - img->width / 2;
	img->instances[inst].y = posy - img->height / 2;
}
