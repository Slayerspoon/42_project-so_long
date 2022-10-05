/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_game_map.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aionescu <aionescu@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 19:52:14 by aionescu          #+#    #+#             */
/*   Updated: 2022/01/06 18:27:36 by aionescu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	read_to_line(char *temp_line, int fd)
{
	int	line_count;
	int	char_count;

	line_count = 0;
	char_count = 0;
	while (read(fd, &temp_line[char_count], 1) != 0)
	{
		char_count++;
		if (temp_line[char_count - 1] == '\n')
			line_count++;
	}
	if (char_count == 0)
		return (0);
	else
		line_count++;
	return (line_count);
}

void	count_cols(int *first_row, int *current_row, char c, int *nl_found)
{
	if (c == '\n')
	{
		*nl_found = *nl_found + 1;
	}
	else
	{
		if (*nl_found == 0)
			*first_row = *first_row + 1;
		else
			*current_row = *current_row + 1;
	}
}

int	determine_number_of_cols(char *temp_line)
{
	int	first_row;
	int	current_row;
	int	index;
	int	nl_found;

	index = 0;
	first_row = 0;
	current_row = 0;
	nl_found = 0;
	while (temp_line[index] != '\0')
	{
		count_cols(&first_row, &current_row, temp_line[index], &nl_found);
		if (nl_found >= 2 && temp_line[index] == '\n')
		{
			if (first_row != current_row)
				return (-1);
		}
		if (temp_line[index] == '\n')
			current_row = 0;
		index++;
	}
	if (first_row != current_row)
		return (-1);
	return (first_row);
}

void	line_to_map(char **created_map, char *temp_line)
{
	int		temp_line_index;
	int		line_index;
	int		char_index;

	temp_line_index = 0;
	line_index = 0;
	char_index = 0;
	while (temp_line[temp_line_index] != '\0')
	{
		if (temp_line[temp_line_index] == '\n')
		{
			created_map[line_index][char_index] = '\0';
			line_index++;
			char_index = 0;
		}
		else
		{
			created_map[line_index][char_index] = temp_line[temp_line_index];
			char_index++;
		}
		temp_line_index++;
	}
	created_map[line_index][char_index] = '\0';
	created_map[line_index + 1] = NULL;
}

char	**generate_game_map(int fd)
{
	char	**generated_map;
	char	*temp_line;
	int		number_of_lines;
	int		number_of_cols;
	int		row_index;

	temp_line = ft_calloc(1000000, 1);
	number_of_lines = read_to_line(temp_line, fd);
	number_of_cols = determine_number_of_cols(temp_line);
	if (number_of_lines == 0 || number_of_cols < 0)
	{
		free(temp_line);
		return (NULL);
	}
	row_index = 0;
	generated_map = (char **)malloc(sizeof(char *) * (number_of_lines + 1));
	while (row_index < number_of_lines)
	{
		generated_map[row_index] = (char *)malloc(number_of_cols + 1);
		row_index++;
	}
	line_to_map(generated_map, temp_line);
	free(temp_line);
	return (generated_map);
}
