//
// Created by artem.rudencko on 8/30/2018.
//

#include "rtv1.h"

t_vec3 point_at_parameter(t_ray r, double t) {
	return (vec_plus(r.A, vec_mult_scalar(r.B, t)));
}

bool		list_hit(const t_ray ray, double d_min, double d_max, t_hit_record **rec, t_list *list) {
	t_hit_record	*temp_rec;
	bool			hit_anything;
	double			closest_so_far;
	t_list			*tmp;

	hit_anything = false;
	closest_so_far = d_max;
	tmp = list;
	temp_rec = malloc(sizeof(t_vec3) + sizeof(t_vec3) + sizeof(double) + sizeof(t_material *));

	while (tmp) {
		t_sphere *tempSphere = tmp->content;
		if (sphere_hit(ray, d_min, closest_so_far, temp_rec, tempSphere)) {
			hit_anything = true;
			closest_so_far = temp_rec->t;
			*rec = temp_rec;
		}
		tmp = tmp->next;
	}
	return (hit_anything);
}