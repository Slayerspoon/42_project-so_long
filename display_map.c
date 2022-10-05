/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aionescu <aionescu@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 19:08:57 by aionescu          #+#    #+#             */
/*   Updated: 2021/12/16 20:58:18 by aionescu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	determine_image(char char_from_map, char dolphin_facing)
{
	if (char_from_map == '0')
		return (7);
	else if (char_from_map == '1')
		return (6);
	else if (char_from_map == 'C')
		return (4);
	else if (char_from_map == 'E')
		return (5);
	else
	{
		if (dolphin_facing == 'D')
			return (0);
		else if (dolphin_facing == 'L')
			return (1);
		else if (dolphin_facing == 'R')
			return (2);
		else
			return (3);
	}
}

void	display_map(t_vars vars, void **imgs, char **map, char dolphin_facing)
{
	int	row;
	int	col;
	int	img_index;
	int	x;
	int	y;

	row = 0;
	col = 0;
	x = 0;
	y = 0;
	while (map[row] != NULL)
	{
		while (map[row][col] != '\0')
		{
			x = col * 32;
			img_index = determine_image(map[row][col], dolphin_facing);
			mlx_put_image_to_window(vars.mlx, vars.win, imgs[img_index], x, y);
			col++;
		}
		y = y + 32;
		col = 0;
		row++;
	}
}
