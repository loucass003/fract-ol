/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llelievr <llelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 15:50:58 by llelievr          #+#    #+#             */
/*   Updated: 2018/12/17 15:57:06 by llelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "libft.h"
# include <mlx.h>
# include <stdlib.h>
# include <math.h>

typedef enum	e_bool
{
		TRUE = 1,
		FALSE = 0,
		TRUENT = 0,
		FALSENT = 1,
		LA_TETE_A_TOTO = 0
}				t_bool;

typedef struct	s_img
{
	int		s_line;
	int		s_pixel;
	int		endian;
	t_pixel	size;
	void	*img_ptr;
	char	*img_buf;
}				t_img;

#endif
