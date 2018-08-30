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

#ifndef FD_F_MATH_H
# define FD_F_MATH_H

# include <math.h>

# define ALPHA 5.2
# define RAD (ALPHA / (180 / 3.14))

typedef struct	s_vec3
{
	double	x;
	double	y;
	double	z;

	struct	s_vec3 (*division)(struct s_vec3, struct s_vec3);
	struct	s_vec3 (*minus)(struct s_vec3, struct s_vec3);
	struct	s_vec3 (*plus)(struct s_vec3, struct s_vec3);
	struct	s_vec3 (*mult)(struct s_vec3, struct s_vec3);
	struct	s_vec3 (*mult_scalar)(struct s_vec3, int scalar);
	struct	s_vec3 (*division_scalar)(struct s_vec3, int scalar);
	struct	s_vec3 (*cross)(struct s_vec3, struct s_vec3);
	struct	s_vec3 (*subtract)(struct s_vec3, struct s_vec3);
	struct	s_vec3 (*normalize)(struct s_vec3);
	double	(*dot)(struct s_vec3, struct s_vec3);
	int		(*length)(struct s_vec3);
}				t_vec3;

typedef struct	s_vec4
{
	double	x;
	double	y;
	double	z;
	double	w;
}				t_vec4;

typedef struct	s_point
{
	t_vec4		pos;
	t_vec3		rgb;
}				t_point;

typedef struct	s_mat3
{
	t_vec3 x_axis;
	t_vec3 y_axis;
	t_vec3 z_axis;
}				t_mat3;

typedef struct	s_mat4
{
	t_vec4 x_axis;
	t_vec4 y_axis;
	t_vec4 z_axis;
	t_vec4 w_axis;
}				t_mat4;

t_vec3			new_vec(double x, double y, double z);
t_vec4			vec4(double x, double y, double z, double w);
double			dot_vec4(t_vec4 v1, t_vec4 v2);
t_vec3			cross_vec3(t_vec3 v1, t_vec3 v2);
t_vec3			subtract_vec3(t_vec3 v1, t_vec3 v2);
t_mat4			new_mat4();
t_vec3			normalize_vec3(t_vec3 v);
t_mat4			mat4_mat4_multiply(t_mat4 m1, t_mat4 m2);
t_vec4			vec4_mat4_multiply(t_vec4 v, t_mat4 m);

t_mat4			create_translation(t_vec3 pos);
t_mat4			create_x_rotation(double angle);
t_mat4			create_y_rotation(double angle);
t_mat4			create_z_rotation(double angle);

t_vec3      	vec_division(t_vec3 vec1, t_vec3 vec2);
t_vec3      	vec_mult(t_vec3 vec1, t_vec3 vec2);
t_vec3      	vec_minus(t_vec3 vec1, t_vec3 vec2);
t_vec3      	vec_plus(t_vec3 vec1, t_vec3 vec2);
t_vec3      	vec_mult_scalar(t_vec3 vec, int scalar);
t_vec3      	vec_division_scalar(t_vec3 vec, int scalar);
double 			dot_vec(t_vec3 v1, t_vec3 v2);
int				vec_length(t_vec3 vec);






#endif