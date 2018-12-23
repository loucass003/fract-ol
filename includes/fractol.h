/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llelievr <llelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 15:50:58 by llelievr          #+#    #+#             */
/*   Updated: 2018/12/22 20:55:33 by llelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "libft.h"
# include <mlx.h>
# include <stdlib.h>
# include <complex.h>
# include <math.h>

# ifndef __linux__
#  define KEY_ESC (53)
#  define KEY_W (13)
#  define KEY_A (0)
#  define KEY_S (1)
#  define KEY_D (2)
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

typedef double _Complex t_complex;

typedef enum	e_bool
{
	TRUE = 1,
	FALSE = 0
}				t_bool;

typedef struct	s_img
{
	int		s_line;
	int		s_pixel;
	int		endian;
	t_size	size;
	void	*img_ptr;
	char	*img_buf;
}				t_img;

typedef struct	s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_size	size;
}				t_mlx;

typedef struct	s_inst
{
	t_mlx		mlx;
	t_img		*img;
	long double	scale;
	size_t		iter;
	t_vec2		pos;
}				t_inst;

size_t			mandelbrot(t_complex c, size_t iter);

t_img			*new_img(t_mlx *mlx, t_size size);
t_img			*refresh_img(t_img *img);
void			clear_img(t_mlx *inst, t_img *img);
t_bool			put_pixel(t_img *img, t_pixel p);

int				key_event(int k, t_inst *inst);
int				render(t_inst *inst);

#endif
