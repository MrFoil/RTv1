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

#include <rtv1.h>


//
//t_vec4		vec4_mat4_multiply(t_vec4 v, t_mat4 m)
//{
//    t_vec4 r;
//    t_vec4 m1x;
//    t_vec4 m1y;
//    t_vec4 m1z;
//    t_vec4 m1w;
//
//    m1x = vec4(m.x_axis.x, m.y_axis.x, m.z_axis.x, m.w_axis.x);
//    m1y = vec4(m.x_axis.y, m.y_axis.y, m.z_axis.y, m.w_axis.y);
//    m1z = vec4(m.x_axis.z, m.y_axis.z, m.z_axis.z, m.w_axis.z);
//    m1w = vec4(m.x_axis.w, m.y_axis.w, m.z_axis.w, m.w_axis.w);
//    r.x = dot_vec4(v, m1x);
//    r.y = dot_vec4(v, m1y);
//    r.z = dot_vec4(v, m1z);
//    r.w = dot_vec4(v, m1w);
//    return (r);
//}
