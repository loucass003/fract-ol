/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llelievr <llelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 14:22:29 by llelievr          #+#    #+#             */
/*   Updated: 2019/01/08 19:03:13 by llelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int		colorize(size_t n, t_inst *inst)
{
	double	t;

	if (!inst->pretty)
		return (n * 0xFFFFFF / inst->iter);
	t = (double)n / inst->iter;
	return (ft_color_i(ft_color((u_int8_t)(9 * (1 - t) * t * t * t * 255),
		(u_int8_t)(15 * (1 - t) * (1 - t) * t * t * 255),
		(u_int8_t)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255))));
}

static int		draw_hud(t_inst *i)
{
	t_int_str	s;
	int			height;

	height = i->mlx.size.height;
	mlx_string_put(i->mlx.mlx_ptr, i->mlx.win_ptr, 5, height, MCOL,
	"Iterations:");
	s = ft_uint_to_str(i->iter);
	mlx_string_put(i->mlx.mlx_ptr, i->mlx.win_ptr, 120, height, MCOL, s.str);
	mlx_string_put(i->mlx.mlx_ptr, i->mlx.win_ptr, 5, height + 20, MCOL, "X:");
	s = ft_int_to_str(i->x / 100);
	mlx_string_put(i->mlx.mlx_ptr, i->mlx.win_ptr, 30, height + 20, MCOL,
	s.str);
	mlx_string_put(i->mlx.mlx_ptr, i->mlx.win_ptr, 200, height + 20, MCOL,
	"Y:");
	s = ft_int_to_str(i->y / 100);
	mlx_string_put(i->mlx.mlx_ptr, i->mlx.win_ptr, 225, height + 20, MCOL,
	s.str);
	mlx_string_put(i->mlx.mlx_ptr, i->mlx.win_ptr, 380, height, MCOL, HELP1);
	mlx_string_put(i->mlx.mlx_ptr, i->mlx.win_ptr, 380, height + 20, MCOL,
	HELP2);
	return (0);
}

static void		*render_div(t_thread *t)
{
	size_t		i;
	size_t		x;
	size_t		y;

	i = 0;
	y = t->min;
	while (y < t->max)
	{
		x = 0;
		while (x < t->inst->mlx.size.width)
		{
			t->inst->cx = (x - t->inst->x) / t->scalex;
			t->inst->cy = (y - t->inst->y) / t->scaley;
			i = t->inst->selected->fn(t->inst->cy * I + t->inst->cx,
			t->inst->iter,
			t->inst->c);
			if (i < t->inst->iter)
				put_pixel(t->inst->img, (t_pixel){ x, y,
					colorize(i, t->inst)});
			x++;
		}
		y++;
	}
	return (NULL);
}

int				render(t_inst *inst)
{
	size_t			t;
	pthread_t		threads[THREAD_MAX];
	t_thread		div_threads[THREAD_MAX];
	const double	scale[2] = { inst->scale * inst->mlx.size.width,
	inst->scale * inst->mlx.size.height};
	const int		div = floor(inst->mlx.size.height / THREAD_MAX);

	clear_img(inst->img);
	mlx_clear_window(inst->mlx.mlx_ptr, inst->mlx.win_ptr);
	t = 0;
	while (t < THREAD_MAX)
	{
		div_threads[t] = (t_thread){ t * div, (t + 1) * div, scale[0],
		scale[1], inst };
		pthread_create(threads + t, NULL, (void *)render_div, div_threads + t);
		t++;
	}
	while (t--)
		pthread_join(threads[t], NULL);
	mlx_put_image_to_window(inst->mlx.mlx_ptr, inst->mlx.win_ptr,
	inst->img->img_ptr, 0, 0);
	draw_hud(inst);
	return (0);
}
