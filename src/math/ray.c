//
// Created by artem.rudencko on 8/30/2018.
//

#include "vector_math.h"

t_vec3 point_at_parameter(t_ray r, double t) {
	return (vec_plus(r.A, vec_mult_scalar(r.B, t)));
}

bool sphere_hit(const t_ray ray, double t_min, double t_max, t_hit_record *rec, t_sphere *s) {
	t_vec3 oc = vec_minus(ray.A, s->center);
	// dot(B,B) + dot(B, A-C) + dot(A-C, A-C) - R*R = 0;
	double a = dot_vec(ray.B, ray.B);
	double b =  2.0 * dot_vec(oc, ray.B);
	double c = dot_vec(oc, oc) - s->radius * s->radius;
	double discriminant = b * b - 4 * a * c;
	double temp;
	if (discriminant > 0){
		temp = (-b - sqrt(discriminant)) / (2 * a);
		if (temp < t_max && temp > t_min){
			rec->t = temp;
			rec->point = point_at_parameter(ray, rec->t);
			rec->normal = (vec_division_scalar(vec_minus(rec->point, s->center), s->radius));
			return (true);
		}
		temp = (-b + sqrt(discriminant)) / (2 * a);
		if (temp < t_max && temp > t_min){
			rec->t = temp;
			rec->point = point_at_parameter(ray, rec->t);
			rec->normal = (vec_division_scalar(vec_minus(rec->point, s->center), s->radius));
			return (true);
		}
	}
	return false;
}

bool list_hit(const t_ray ray, double d_min, double d_max, t_hit_record **rec, t_list *list) {
	t_hit_record *temp_rec;
	bool hit_anything;
	double closest_so_far;
	t_list *tmp;

	hit_anything = false;
	closest_so_far = d_max;
	tmp = list;
	temp_rec = malloc(sizeof(t_vec3) + sizeof(t_vec3) + sizeof(double));

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