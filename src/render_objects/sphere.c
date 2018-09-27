//
// Created by artem.rudencko on 9/25/2018.
//

#include "rtv1.h"

t_sphere *new_sphere(t_vec3 pos, double radius, t_material material) {
	t_sphere *s;

	s = malloc(sizeof(t_vec3) + sizeof(double) + sizeof(t_sphere *));
	s->radius = radius;
	s->center = pos;
	s->material = material;

	return (s);
}

bool sphere_hit(const t_ray ray, double t_min, double t_max, t_hit_record *rec, t_sphere *s) {
	t_vec3 oc = vec_minus(ray.A, s->center);
	 /*TODO: dot(B,B) + dot(B, A-C) + dot(A-C, A-C) - R*R = 0;*/
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
			rec->mat_ptr = &s->material;
			return (true);
		}
		temp = (-b + sqrt(discriminant)) / (2 * a);
		if (temp < t_max && temp > t_min){
			rec->t = temp;
			rec->point = point_at_parameter(ray, rec->t);
			rec->normal = (vec_division_scalar(vec_minus(rec->point, s->center), s->radius));
			rec->mat_ptr = &s->material;
			return (true);
		}
	}
	return false;
}

t_vec3		random_point_in_unit_sphere(){
	double random_max;
	double random_min;

	random_max = 1;
	random_min = 0;
	t_vec3 p;
	do {
		p = vec(randfrom(random_min, random_max), randfrom(random_min, random_max), randfrom(random_min, random_max));
		p = vec_mult_scalar(p, 2.0);
		p = vec_minus(p, vec(1, 1, 1));
//		p = vec_minus(vec_mult_scalar(new_vec(randfrom(random_min, random_max), randfrom(random_min, random_max), randfrom(random_min, random_max)),2.0),new_vec(1, 1, 1));
	}while(dot_vec(p, p) >= random_max);
	return p;
}