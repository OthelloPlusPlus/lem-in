/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohengelm <ohengelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 15:25:47 by ohengelm          #+#    #+#             */
/*   Updated: 2026/05/19 20:03:06 by ohengelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

void	common_functions(t_farm* farm)
{
	prepare_farm(farm);
	parse_from_fd(0, farm);
	connect_links(farm);
	valid_farm(farm);
}
