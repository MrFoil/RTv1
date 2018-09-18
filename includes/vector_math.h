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

# include "libft.h"
# include <math.h>
# include <stdbool.h>
# include "rtv1.h"
# define ALPHA 5.2
# define RAD (ALPHA / (180 / 3.14))

typedef struct	s_vec3
{
	double	x;
	double	y;
	double	z;
}				t_vec3;

typedef struct s_sphere {
	t_vec3 center;
	double radius;
} t_sphere;

typedef struct s_camera {
	struct s_vec3 lower_left_corner;
	struct s_vec3 horizontal;
	struct s_vec3 vertical;
	struct s_vec3 origin;
} t_camera;

typedef struct	s_hit_record
{
	double			t;
	t_vec3 point;
	t_vec3 normal;
}				t_hit_record;

typedef struct	s_ray
{
	struct s_vec3	A;
	struct s_vec3	B;
}				t_ray;

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

typedef struct s_object {
	int type; // 1 == Sphere, 2 == Rectangle
	struct s_vec3 pos;
	double width;
	double height;
	double radius;
	struct s_vec3 color;
	bool visible;
} t_object;


//typedef struct	s_mat3
//{
//	t_vec3 x_axis;
//	t_vec3 y_axis;
//	t_vec3 z_axis;
//}				t_mat3;
//
//typedef struct	s_mat4
//{
//	t_vec4 x_axis;
//	t_vec4 y_axis;
//	t_vec4 z_axis;
//	t_vec4 w_axis;
//}				t_mat4;

t_vec3			new_vec(double x, double y, double z);
t_vec4			vec4(double x, double y, double z, double w);
double			dot_vec4(t_vec4 v1, t_vec4 v2);
t_vec3			cross_vec3(t_vec3 v1, t_vec3 v2);
t_vec3			subtract_vec3(t_vec3 v1, t_vec3 v2);

t_vec3      	vec_division(t_vec3 vec1, t_vec3 vec2);
t_vec3      	vec_mult(t_vec3 vec1, t_vec3 vec2);
t_vec3      	vec_minus(t_vec3 vec1, t_vec3 vec2);
t_vec3      	vec_plus(t_vec3 vec1, t_vec3 vec2);
t_vec3      	vec_mult_scalar(t_vec3 vec, double scalar);
t_vec3      	vec_division_scalar(t_vec3 vec, double scalar);
double 			dot_vec(t_vec3 v1, t_vec3 v2);
float				vec_length(t_vec3 vec);
t_vec3			unit_vector(t_vec3 v);

double sdSphere(t_vec3 vec, float s);


t_ray		new_ray(t_vec3 v1, t_vec3 v2);

t_vec3 point_at_parameter(t_ray r, double t);

t_camera new_camera(t_vec3 lower_left_corner, t_vec3 horizontal, t_vec3 vertical, t_vec3 origin);

t_ray get_ray(t_camera c, double u, double v);

bool list_hit(t_ray ray, double d_min, double d_max, t_hit_record **rec, t_list *list);

t_sphere *new_sphere(t_vec3 pos, double radius);










#endif