/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aionescu <aionescu@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 19:17:08 by aionescu          #+#    #+#             */
/*   Updated: 2022/01/13 00:13:29 by aionescu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	exit_game(t_vars *vars)
{
	free(vars->map);
	mlx_destroy_window(vars->mlx, vars->win);
	exit(0);
}

char	determine_facing(int keycode)
{
	if (keycode == 97)
		return ('L');
	else if (keycode == 119)
		return ('U');
	else if (keycode == 100)
		return ('R');
	else
		return ('D');
}

int	key_hook(int keycode, t_vars *vars)
{
	char	facing;
	int		moved;

	facing = 'U';
	moved = 0;
	if (keycode == 97 || keycode == 100 || keycode == 115 || keycode == 119)
	{
		facing = determine_facing(keycode);
		moved = update_map(vars->map, facing);
		if (moved != 0)
		{
			vars->moves++;
			printf("Moves made so far: %d\n", vars->moves);
		}
		display_map(*vars, vars->imgs, vars->map, facing);
		if (moved == 2)
		{
			printf("Thanks for all the fish!\n");
			exit_game(vars);
		}
	}
	else if (keycode == 65307)
		exit_game(vars);
	return (0);
}

int	main(int argc, char **argv)
{
	t_vars			vars;
	t_resolution	resolution;

	vars.map = error_check_map(argv[1]);
	if (argc != 2 || vars.map == NULL)
	{
		printf("Error\nInvalid map provided.\n");
		return (1);
	}
	if (set_resolution(&resolution, vars) != 0)
	{
		printf("Error\nThe provided map is too big.\n");
		return (1);
	}
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, resolution.x, resolution.y, "So long!");
	vars.imgs = create_image_array(vars.mlx);
	vars.moves = 0;
	display_map(vars, vars.imgs, vars.map, 'U');
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_hook(vars.win, 17, 1L << 17, exit_game, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
