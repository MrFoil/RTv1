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

t_mat4		look_at(t_vec3 eye, t_vec3 target, t_vec3 up)
{
	t_mat4	t;
	t_mat4	r;
	t_vec3	f;
	t_vec3	s;
	t_vec3	u;

	f = normalize_vec3(subtract_vec3(target, eye));
	s = normalize_vec3(cross_vec3(f, up));
	u = cross_vec3(s, f);
	r.x_axis = vec4(s.x, u.x, f.x, 0);
	r.y_axis = vec4(s.y, u.y, f.y, 0);
	r.z_axis = vec4(s.z, u.z, f.z, 0);
	r.w_axis = vec4(0, 0, 0, 1);
	t = create_translation(vec3(-eye.x, -eye.y, -eye.z));
	return (mat4_mat4_multiply(r, t));
}

t_mat4		camera(t_vec3 eye, t_vec3 tar, t_vec3 up)
{
	t_mat4	cam;

	cam = look_at(eye, tar, up);
	return (cam);
}
