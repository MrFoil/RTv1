//
// Created by artem.rudencko on 8/30/2018.
//

#include "vector_math.h"

t_vec3		point_at_parameter(t_vec3 A, t_vec3 B, double t){
	return (vec_plus(A, vec_mult_scalar(B, t)));
}

bool		hit(const t_ray ray, double t_min, double t_max, t_hit_record rec, t_sphere s)
{
	t_vec3 oc = vec_minus(ray.A, s.center);
	// dot(B,B) + 2 * dot(B, A-C) + dot(A-C, A-C) - R*R = 0;
	double a = dot_vec(ray.B, ray.B);
	double b = 2.0 * dot_vec(oc, ray.B);
	double c = dot_vec(oc, oc) - s.radius * s.radius;
	double discriminant = b * b - a * c;
	double temp;
	if (discriminant > 0){
		temp = (-b - sqrt(discriminant)) /a;
		if (temp < t_max && temp > t_min){
			rec.t = temp;
			rec.point = point_at_parameter(ray.A, ray.B,rec.t);
			rec.normal = (vec_division_scalar(vec_minus(rec.point, s.center), s.radius));
			return (true);
		}
		temp = (-b + sqrt(discriminant)) /a;
		if (temp < t_max && temp > t_min){
			rec.t = temp;
			rec.point = point_at_parameter(ray.A, ray.B,rec.t);
			rec.normal = (vec_division_scalar(vec_minus(rec.point, s.center), s.radius));
			return (true);
		}
	}
	return false;
}
