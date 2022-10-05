/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aionescu <aionescu@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 19:18:15 by aionescu          #+#    #+#             */
/*   Updated: 2022/01/12 21:53:02 by aionescu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include "./mlx/mlx.h"
# include "./libft/libft.h"

typedef struct s_vars {
	void	*mlx;
	void	*win;
	char	**map;
	void	**imgs;
	int		moves;
}	t_vars;
typedef struct s_resolution {
	int	x;
	int	y;
}	t_resolution;
int		main(int argc, char **argv);
char	**generate_game_map(int fd);
char	**error_check_map(char *map_file_path);
int		set_resolution(t_resolution *resolution, t_vars vars);
void	**create_image_array(void *mlx);
void	display_map(t_vars vars, void **imgs, char **map, char dolphin_facing);
int		update_map(char **map, char movement);
int		count_collectibles(char **map);

#endif
