/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 00:19:09 by yenyilma          #+#    #+#             */
/*   Updated: 2025/11/30 01:29:34 by yenyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		mlx_loop(void *mlx_ptr);
int		mlx_key_hook(void *win, int (*f)(), void *param);
int		init_mlx(t_minirt *rt);
void	setup_camera(t_camera *cam);
void	render_scene(t_minirt *rt);

static void	put_img(void *m, void *w, void *i)
{
	extern int	mlx_put_image_to_window(void *, void *, void *, int, int);

	mlx_put_image_to_window(m, w, i, 0, 0);
}

static int	setup_hook(void *win, t_minirt *rt)
{
	extern int	mlx_hook(void *, int, int, int (*)(), void *);

	return (mlx_hook(win, 17, 0, close_window, rt));
}

int	main(int ac, char **av)
{
	t_minirt	rt;
	t_scene		*scene;

	if (ac != 2)
		error_exit("Usage: ./miniRT <scene.rt>");
	scene = parse_scene(av[1]);
	rt.scene = *scene;
	free(scene);
	setup_camera(&rt.scene.camera);
	if (!init_mlx(&rt))
		error_exit("MLX initialization failed");
	render_scene(&rt);
	put_img(rt.mlx.mlx, rt.mlx.win, rt.mlx.img);
	setup_hook(rt.mlx.win, &rt);
	mlx_key_hook(rt.mlx.win, key_press, &rt);
	mlx_loop(rt.mlx.mlx);
	return (0);
}
