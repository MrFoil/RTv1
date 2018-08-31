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
# include <stdbool.h>

# define ALPHA 5.2
# define RAD (ALPHA / (180 / 3.14))

typedef struct	s_vec3
{
	double	x;
	double	y;
	double	z;
}				t_vec3;

typedef struct	s_hit_record
{
	double			t;
	struct s_vec3	point;
	struct s_vec3	normal;
}				t_hit_record;

typedef struct	s_ray
{
	struct s_vec3	A;
	struct s_vec3	B;
}				t_ray;

typedef struct	s_sphere
{
	struct s_vec3	center;
	double			radius;
}				t_sphere;

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
t_vec3      	vec_mult_scalar(t_vec3 vec, double scalar);
t_vec3      	vec_division_scalar(t_vec3 vec, double scalar);
double 			dot_vec(t_vec3 v1, t_vec3 v2);
int				vec_length(t_vec3 vec);
t_vec3			unit_vector(t_vec3 v);


t_ray		new_ray(t_vec3 v1, t_vec3 v2);
t_vec3		point_at_parameter(t_vec3 A, t_vec3 B, double t);







#endif