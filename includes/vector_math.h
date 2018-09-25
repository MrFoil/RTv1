/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math.h                                       :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: arrudenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 15:10:08 by arrudenk          #+#    #+#             */
/*   Updated: 2018/03/29 14:06:26 by arrudenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_MATH_H
# define VECTOR_MATH_H

# include "libft.h"
# include <math.h>
# include <stdbool.h>
# define ALPHA 5.2
# define RAD (ALPHA / (180 / 3.14))


typedef struct	s_vec3
{
	double	x;
	double	y;
	double	z;
}				t_vec3;

t_vec3			new_vec(double x, double y, double z);

t_vec3			cross_vec3(t_vec3 v1, t_vec3 v2);
t_vec3			subtract_vec3(t_vec3 v1, t_vec3 v2);
t_vec3			vec_division(t_vec3 vec1, t_vec3 vec2);
t_vec3			vec_mult(t_vec3 vec1, t_vec3 vec2);
t_vec3			vec_minus(t_vec3 vec1, t_vec3 vec2);
t_vec3			vec_plus(t_vec3 vec1, t_vec3 vec2);
t_vec3			vec_mult_scalar(t_vec3 vec, double scalar);
t_vec3			vec_division_scalar(t_vec3 vec, double scalar);
double 			dot_vec(t_vec3 v1, t_vec3 v2);
double			vec_length(t_vec3 vec);
t_vec3			unit_vector(t_vec3 v);
t_vec3			vec_reflect(t_vec3 v, t_vec3 n);

#endif