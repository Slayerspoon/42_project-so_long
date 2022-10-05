/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aionescu <aionescu@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 18:55:17 by aionescu          #+#    #+#             */
/*   Updated: 2021/11/24 19:59:10 by aionescu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	is_rectangular(char **map)
{
	int	verdict;
	int	first_col_count;
	int	col_count;
	int	row_count;

	col_count = 0;
	row_count = 0;
	verdict = 1;
	while (map[row_count] != NULL)
	{
		while (map[row_count][col_count] != '\0')
			col_count++;
		if (row_count == 0)
			first_col_count = col_count;
		if (col_count != first_col_count)
		{
			verdict = 0;
			break ;
		}
		col_count = 0;
		row_count++;
	}
	return (verdict);
}

int	has_walls(char **map)
{
	int	col_index;
	int	row_index;

	col_index = 0;
	row_index = 0;
	while (map[row_index] != NULL)
	{
		while (map[row_index][col_index] != '\0')
		{
			if ((row_index == 0 && map[row_index][col_index] != '1')
				|| (col_index == 0 && map[row_index][col_index] != '1'))
				return (0);
			if (map[row_index + 1] == NULL && map[row_index][col_index] != '1')
				return (0);
			col_index++;
		}
		if (map[row_index][col_index - 1] != '1')
			return (0);
		col_index = 0;
		row_index++;
	}
	return (1);
}

void	analyze_cep(char letter, int *c, int *e, int *p)
{
	if (letter == 'C')
		*c = *c + 1;
	else if (letter == 'E')
		*e = *e + 1;
	else if (letter == 'P')
		*p = *p + 1;
}

int	has_cep(char **map)
{
	int	num_c;
	int	num_e;
	int	num_p;
	int	col_index;
	int	row_index;

	num_c = 0;
	num_e = 0;
	num_p = 0;
	col_index = 0;
	row_index = 0;
	while (map[row_index] != NULL)
	{
		while (map[row_index][col_index] != '\0')
		{
			analyze_cep(map[row_index][col_index], &num_c, &num_e, &num_p);
			col_index++;
		}
		col_index = 0;
		row_index++;
	}
	if (num_c < 1 || num_e < 1 || num_p != 1)
		return (0);
	return (1);
}

char	**error_check_map(char *map_file_path)
{
	char	**game_map;
	int		fd;
	char	*position;

	position = ft_strnstr(map_file_path, ".ber", ft_strlen(map_file_path));
	if (position != NULL && ft_strlen(position) == 4)
		fd = open(map_file_path, O_RDONLY);
	else
		return (NULL);
	if (fd == -1)
		return (NULL);
	game_map = generate_game_map(fd);
	if (game_map == NULL)
		return (NULL);
	if (is_rectangular(game_map) == 0
		|| has_walls(game_map) == 0 || has_cep(game_map) == 0)
	{
		free (game_map);
		return (NULL);
	}
	return (game_map);
}
