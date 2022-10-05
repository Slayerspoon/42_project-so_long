/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aionescu <aionescu@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 21:29:28 by aionescu          #+#    #+#             */
/*   Updated: 2022/01/12 21:13:59 by aionescu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	count_collectibles(char **map)
{
	int	collectibles;
	int	row;
	int	col;

	collectibles = 0;
	row = 0;
	col = 0;
	while (map[row] != NULL)
	{
		while (map[row][col] != '\0')
		{
			if (map[row][col] == 'C')
				collectibles++;
			col++;
		}
		col = 0;
		row++;
	}
	return (collectibles);
}

int	move_p_if_possible(char **map, int dest_row, int dest_col)
{
	int	collectibles_left;

	collectibles_left = count_collectibles(map);
	if (map[dest_row][dest_col] == '0' || map[dest_row][dest_col] == 'C')
	{
		map[dest_row][dest_col] = 'P';
		return (1);
	}
	else if (map[dest_row][dest_col] == 'E')
	{
		if (collectibles_left == 0)
			return (2);
	}
	return (0);
}

int	move_p_on_map(char **map, int row_p, int col_p, char movement)
{
	int	moved;

	moved = 0;
	if (movement == 'U')
		moved = move_p_if_possible(map, row_p - 1, col_p);
	else if (movement == 'D')
		moved = move_p_if_possible(map, row_p + 1, col_p);
	else if (movement == 'L')
		moved = move_p_if_possible(map, row_p, col_p - 1);
	else if (movement == 'R')
		moved = move_p_if_possible(map, row_p, col_p + 1);
	if (moved != 0)
		map[row_p][col_p] = '0';
	return (moved);
}

int	update_map(char **map, char movement)
{
	int	row;
	int	col;
	int	row_p;
	int	col_p;

	row = 0;
	col = 0;
	while (map[row] != NULL)
	{
		while (map[row][col] != '\0')
		{
			if (map[row][col] == 'P')
			{
				row_p = row;
				col_p = col;
			}
			col++;
		}
		col = 0;
		row++;
	}
	return (move_p_on_map(map, row_p, col_p, movement));
}
