/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_math.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arrudenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 00:36:49 by arrudenk          #+#    #+#             */
/*   Updated: 2018/03/30 00:36:51 by arrudenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector_math.h>

t_vec4		quick_math(t_vec4 axis, t_mat4 m1, t_vec4 v)
{
	t_vec4 m1x;
	t_vec4 m1y;
	t_vec4 m1z;
	t_vec4 m1w;

	m1x = vec4(m1.x_axis.x, m1.y_axis.x, m1.z_axis.x, m1.w_axis.x);
	m1y = vec4(m1.x_axis.y, m1.y_axis.y, m1.z_axis.y, m1.w_axis.y);
	m1z = vec4(m1.x_axis.z, m1.y_axis.z, m1.z_axis.z, m1.w_axis.z);
	m1w = vec4(m1.x_axis.w, m1.y_axis.w, m1.z_axis.w, m1.w_axis.w);
	axis.x = dot_vec4(m1x, v);
	axis.y = dot_vec4(m1y, v);
	axis.z = dot_vec4(m1z, v);
	axis.w = dot_vec4(m1w, v);
	return (axis);
}

t_mat4		mat4_mat4_multiply(t_mat4 m1, t_mat4 m2)
{
	t_mat4 r;

	r.x_axis = quick_math(r.x_axis, m1, m2.x_axis);
	r.y_axis = quick_math(r.y_axis, m1, m2.y_axis);
	r.z_axis = quick_math(r.z_axis, m1, m2.z_axis);
	r.w_axis = quick_math(r.w_axis, m1, m2.w_axis);
	return (r);
}

t_vec4		vec4_mat4_multiply(t_vec4 v, t_mat4 m)
{
    t_vec4 r;
    t_vec4 m1x;
    t_vec4 m1y;
    t_vec4 m1z;
    t_vec4 m1w;

    m1x = vec4(m.x_axis.x, m.y_axis.x, m.z_axis.x, m.w_axis.x);
    m1y = vec4(m.x_axis.y, m.y_axis.y, m.z_axis.y, m.w_axis.y);
    m1z = vec4(m.x_axis.z, m.y_axis.z, m.z_axis.z, m.w_axis.z);
    m1w = vec4(m.x_axis.w, m.y_axis.w, m.z_axis.w, m.w_axis.w);
    r.x = dot_vec4(v, m1x);
    r.y = dot_vec4(v, m1y);
    r.z = dot_vec4(v, m1z);
    r.w = dot_vec4(v, m1w);
    return (r);
}
