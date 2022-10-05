/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_image_array.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aionescu <aionescu@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 20:41:35 by aionescu          #+#    #+#             */
/*   Updated: 2022/01/12 21:52:34 by aionescu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	set_resolution(t_resolution *resolution, t_vars vars)
{
	int	row;
	int	col;

	row = 0;
	col = 0;
	while (vars.map[row] != NULL)
	{
		if (row == 0)
		{
			while (vars.map[row][col] != '\0')
				col++;
		}
		row++;
	}
	resolution->x = 32 * col;
	resolution->y = 32 * row;
	if (resolution->x > 1344 || resolution->y > 678)
		return (1);
	else
		return (0);
}

void	**create_image_array(void *mlx)
{
	void	**imgs;
	char	*relative_path;
	int		img_w;
	int		img_h;

	imgs = (void **)malloc(sizeof(void *) * 9);
	relative_path = "./images_xpm/Dolphin_on_water_down.xpm";
	imgs[0] = mlx_xpm_file_to_image(mlx, relative_path, &img_w, &img_h);
	relative_path = "./images_xpm/Dolphin_on_water_left.xpm";
	imgs[1] = mlx_xpm_file_to_image(mlx, relative_path, &img_w, &img_h);
	relative_path = "./images_xpm/Dolphin_on_water_right.xpm";
	imgs[2] = mlx_xpm_file_to_image(mlx, relative_path, &img_w, &img_h);
	relative_path = "./images_xpm/Dolphin_on_water_up.xpm";
	imgs[3] = mlx_xpm_file_to_image(mlx, relative_path, &img_w, &img_h);
	relative_path = "./images_xpm/Collectible_on_water.xpm";
	imgs[4] = mlx_xpm_file_to_image(mlx, relative_path, &img_w, &img_h);
	relative_path = "./images_xpm/Exit_on_water.xpm";
	imgs[5] = mlx_xpm_file_to_image(mlx, relative_path, &img_w, &img_h);
	relative_path = "./images_xpm/Wall_only.xpm";
	imgs[6] = mlx_xpm_file_to_image(mlx, relative_path, &img_w, &img_h);
	relative_path = "./images_xpm/Water_only.xpm";
	imgs[7] = mlx_xpm_file_to_image(mlx, relative_path, &img_w, &img_h);
	imgs[8] = NULL;
	return (imgs);
}
