/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llelievr <llelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/22 18:55:16 by llelievr          #+#    #+#             */
/*   Updated: 2018/12/22 20:57:04 by llelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

size_t		mandelbrot(t_complex c, size_t iter)
{
	t_complex		z;
	size_t			i;
	double			mod;

	i = 0;
	z = 0;
	while (i < iter && mod < 4)
	{
		z = z * z + c;
		mod = creal(z) * creal(z) + cimag(z) * cimag(z);
		i++;
	}
	return (i);
}
