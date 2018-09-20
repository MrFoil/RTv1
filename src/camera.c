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

#include "vector_math.h"

//t_mat4		look_at(t_vec3 eye, t_vec3 target, t_vec3 up)
//{
//	t_mat4	t;
//	t_mat4	r;
//	t_vec3	f;
//	t_vec3	s;
//	t_vec3	u;
//
//	f = normalize_vec3(subtract_vec3(target, eye));
//	s = normalize_vec3(cross_vec3(f, up));
//	u = cross_vec3(s, f);
//	r.x_axis = vec4(s.x, u.x, f.x, 0);
//	r.y_axis = vec4(s.y, u.y, f.y, 0);
//	r.z_axis = vec4(s.z, u.z, f.z, 0);
//	r.w_axis = vec4(0, 0, 0, 1);
//	t = create_translation(new_vec(-eye.x, -eye.y, -eye.z));
//	return (mat4_mat4_multiply(r, t));
//}
//
//t_mat4		camera(t_vec3 eye, t_vec3 tar, t_vec3 up)
//{
//	t_mat4	cam;
//
//	cam = look_at(eye, tar, up);
//	return (cam);
//}

t_ray get_ray(t_camera c, double u, double v) {
	t_vec3 a;
	t_vec3 b;

	a = c.origin;
	b = vec_minus(vec_plus(vec_plus(c.lower_left_corner, vec_mult_scalar(c.horizontal, u)),
						vec_mult_scalar(c.vertical, v)), c.origin);
/*	t_vec3 t1 = vec_mult_scalar(c.horizontal, u);
	t_vec3 t2 = vec_mult_scalar(c.vertical, v);
	t_vec3 t3 = vec_plus(c.lower_left_corner, t1);
	t_vec3 t4 = vec_plus(t3, t2);
	t_vec3 t5 = vec_minus(t4, c.origin);*/
	/*lover_left_corner + u*horizontal + v*vertical - origin*/
	return (new_ray(a, b));
}
