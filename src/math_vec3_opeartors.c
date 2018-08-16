/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_math.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arrudenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 16:16:46 by arrudenk          #+#    #+#             */
/*   Updated: 2018/05/23 16:16:47 by arrudenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector_math.h>

t_vec3 normalize_vec3(t_vec3 v) {
    t_vec3 r;
    double l;

    l = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    r.x = v.x / l;
    r.y = v.y / l;
    r.z = v.z / l;
    return (r);
}

t_vec3 cross_vec3(t_vec3 v1, t_vec3 v2) {
    t_vec3 r;

    r.x = v1.y * v2.z - v2.y * v1.z;
    r.y = v1.x * v2.z - v2.x * v1.z;
    r.z = v1.x * v2.y - v2.x * v1.y;
    return (r);
}

t_vec3 subtract_vec3(t_vec3 v1, t_vec3 v2) {
    t_vec3 r;

    r.x = v1.x - v2.x;
    r.y = v1.y - v2.y;
    r.z = v1.z - v2.z;
    return (r);
}