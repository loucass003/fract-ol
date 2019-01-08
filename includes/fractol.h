/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llelievr <llelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 15:50:58 by llelievr          #+#    #+#             */
/*   Updated: 2019/01/08 19:14:13 by llelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "libft.h"
# include <mlx.h>
# include <stdlib.h>
# include <complex.h>
# include <math.h>
# include <pthread.h>
# include <unistd.h>

# ifndef __linux__
#  define KEY_ESC (53)
#  define KEY_W (13)
#  define KEY_A (0)
#  define KEY_S (1)
#  define KEY_D (2)
#  define KEY_J (38)
#  define KEY_M (46)
#  define KEY_F (3)
#  define KEY_H (4)
#  define KEY_B (11)
#  define KEY_C (8)
#  define KEY_PAGE_U (116)
#  define KEY_PAGE_D (121)
# else
#  define KEY_ESC (65307)
#  define KEY_W (119)
#  define KEY_A (97)
#  define KEY_S (115)
#  define KEY_D (100)
#  define KEY_PAGE_U (65365)
#  define KEY_PAGE_D (65366)
# endif

# define THREAD_MAX 32
# define HELP1 "m: Madelbrot    j: Julia b: Burning Ship"
# define HELP2 "c: switch color h: leaf  f: Feigen"
# define MCOL 0xFFFFFF
# define USAGE "Usage: fractol [mandelbrot|feigen|julia|leaf|burning_ship]\n"

typedef _Complex double	t_complex;

typedef enum				e_bool
{
	TRUE = 1,
	FALSE = 0
}							t_bool;

typedef struct				s_img
{
	int		s_line;
	int		s_pixel;
	int		endian;
	t_size	size;
	void	*img_ptr;
	char	*img_buf;
}							t_img;

typedef struct				s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_size	size;
}							t_mlx;

typedef	struct				s_fractal
{
	int				key;
	char			*name;
	size_t			(*fn)();
}							t_fractal;

typedef struct				s_inst
{
	t_mlx			mlx;
	t_img			*img;
	t_complex		c;
	double			scale;
	size_t			iter;
	double			x;
	double			y;
	double			cx;
	double			cy;
	t_fractal		*selected;
	t_bool			move;
	t_bool			pretty;
}							t_inst;

typedef struct				s_thread
{
	size_t			min;
	size_t			max;
	double			scalex;
	double			scaley;
	t_inst			*inst;
}							t_thread;

t_img						*new_img(t_mlx *mlx, t_size size);
t_img						*clear_img(t_img *img);
void						destroy_img(t_mlx *inst, t_img *img);
t_bool						put_pixel(t_img *img, t_pixel p);

void						init_key_events(t_inst *inst);
void						init_mouse_events(t_inst *inst);
int							render(t_inst *inst);

extern t_fractal			g_fractals[];

#endif
