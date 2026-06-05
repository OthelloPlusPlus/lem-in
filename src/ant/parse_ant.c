/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ant.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohengelm <ohengelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 16:10:12 by ohengelm          #+#    #+#             */
/*   Updated: 2026/04/16 17:13:57 by ohengelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

bool	parse_ant(t_farm* farm, char* line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!ft_isdigit(line[i]))
			return (false);
		++i;
	}
	farm->ants.count = ft_atoi(line);
	return (true);
}
