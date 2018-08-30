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

// TODO: Normalize
// TODO: Subtract

double dot_vec4(t_vec4 v1, t_vec4 v2) {
    double r;

    r = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
    return (r);
}

//_____
int vec4_length(t_vec4 vec) {
    double l;

    l = sqrt(pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2) + pow(vec.w, 2));
    //--or
    l = dot_vec4(vec, vec);
    //its the same
    return ((int) l);
}
