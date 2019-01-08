/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llelievr <llelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/22 18:55:16 by llelievr          #+#    #+#             */
/*   Updated: 2019/01/08 19:07:17 by llelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static size_t		mandelbrot(t_complex c, size_t iter)
{
	t_complex		z;
	size_t			i;

	i = 0;
	z = 0;
	while (i < iter && cabs(z) <= 2)
	{
		z = z * z + c;
		i++;
	}
	return (i);
}

static size_t		julia(t_complex z, size_t iter, t_complex c)
{
	size_t	i;

	i = 0;
	while (cabs(z) <= 2 && i < iter)
	{
		z = z * z + c;
		i++;
	}
	return (i);
}

static size_t		burning_ship(t_complex c, size_t max_iter)
{
	t_complex	z;
	size_t		i;

	i = 0;
	z = 0;
	while (cabs(z) <= 2 && i < max_iter)
	{
		z = z * z + c;
		z = fabs(creal(z)) + I * fabs(cimag(z));
		i++;
	}
	return (i);
}

static size_t		leaf(t_complex c, size_t max_iter)
{
	size_t		i;
	t_complex	z;

	i = 0;
	z = 0;
	while (cabs(z) <= 2 && i < max_iter)
	{
		z = ccos(z / c);
		i++;
	}
	return (i);
}

static size_t		feigen(t_complex c, size_t max_iter)
{
	size_t		i;
	t_complex	z;
	t_complex	c3;

	i = 0;
	z = 0;
	c3 = c * c * c;
	while (cabs(z) <= 2 && i < max_iter)
	{
		z = z * z + c3 - 1.401155;
		i++;
	}
	return (i);
}

t_fractal	g_fractals[] = {
	{ KEY_J, "mandelbrot", mandelbrot },
	{ KEY_M, "julia", julia },
	{ KEY_B, "burning_ship", burning_ship },
	{ KEY_H, "leaf", leaf },
	{ KEY_F, "feigen", feigen }
};
