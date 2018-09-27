/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arrudenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 18:21:15 by arrudenk          #+#    #+#             */
/*   Updated: 2018/03/29 18:21:16 by arrudenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*TODO: lover_left_corner + u*horizontal + v*vertical - origin*/
t_ray get_ray(t_camera c, double u, double v) {
	t_vec3 a;
	t_vec3 b;

	a = c.origin;
	b = vec_minus(vec_plus(vec_plus(c.lower_left_corner, vec_mult_scalar(c.horizontal, u)),
						vec_mult_scalar(c.vertical, v)), c.origin);

	return (new_ray(a, b));
}

/*t_vec3		quick_math(t_vec3 axis, t_camera m1, t_vec3 v)
{
	t_vec3 m1x;
	t_vec3 m1y;
	t_vec3 m1z;

	m1x = vec(m1.lower_left_corner.x, m1.horizontal.x, m1.vertical.x);
	m1y = vec(m1.lower_left_corner.y, m1.horizontal.y, m1.vertical.y);
	m1z = vec(m1.lower_left_corner.z, m1.horizontal.z, m1.vertical.z);
	axis.x = dot_vec(m1x, v);
	axis.y = dot_vec(m1y, v);
	axis.z = dot_vec(m1z, v);
	return (axis);
}*/

/*t_camera		mat4_mat4_multiply(t_camera m1, t_camera m2)
{
	t_camera r;

	r.lower_left_corner = quick_math(r.x_axis, m1, m2.x_axis);
	r.horizontal = quick_math(r.y_axis, m1, m2.y_axis);
	r.vertical = quick_math(r., m1, m2.z_axis);
	return (r);
}*/

t_camera	new_camera(t_vec3 lookfrom, t_vec3 lookat, t_vec3 vup, float vfov, float aspect)
{/*TODO: vfov - is top to bottom in degrees; vup - "view up"*/
	t_camera	camera;
	t_vec3	u;
	t_vec3	v;
	t_vec3	w;
	float		theta;
	float		half_height;
	float		half_width;

	theta = vfov * M_PI/180;
	half_height = tan(theta/2);
	half_width = aspect * half_height;
	camera.origin = lookfrom;
	w = unit_vector(subtract_vec3(lookfrom, lookat));
	u = unit_vector(cross_vec3(vup, w));
	v = cross_vec3(w, u);
	t_vec3 lower_left_corner = vec(-half_width, -half_height, -1.0);

	t_vec3 halfW_mult_u, halfH_mult_v, temp3;
	halfW_mult_u = vec_mult_scalar(u, half_width);
	halfH_mult_v = vec_mult_scalar(v, half_height);
	temp3 = vec_minus(camera.origin, halfW_mult_u);
	temp3 = vec_minus(temp3, halfH_mult_v);
	temp3 = vec_minus(temp3, w);
	camera.lower_left_corner = temp3;
	/*TODO: origin - half_width * u - half_height * v - w */
	camera.lower_left_corner = vec_minus(vec_minus(vec_minus(camera.origin, vec_mult_scalar(u, half_width)), vec_mult_scalar(v, half_height)), w);
	camera.horizontal = vec_mult_scalar(u, 2* half_width);
	camera.vertical = vec_mult_scalar(v, 2 * half_height);

	return (camera);
}