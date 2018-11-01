/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arrudenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 16:51:40 by arrudenk          #+#    #+#             */
/*   Updated: 2018/05/10 16:51:41 by arrudenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "rtv1.h"
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <dns_util.h>

void		draw_world(t_camera camera, t_list *world, int antialiasingX, SDL_Renderer *renderer);
void		random_scene(SDL_Renderer *renderer);


void		draw_scene(SDL_Renderer *renderer);

int		main(int argc, char *args[]) {
	(void) argc;
	(void) args;
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("%s%s\n", "could not initialize sdl2: %s\n", SDL_GetError());
		return 1;
	}

	window = SDL_CreateWindow(
			"hello_sdl2",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			WIDTH, HEIGHT,
			SDL_WINDOW_SHOWN
	);
	if (window == NULL) {
		fprintf(stderr, "could not create window: %s\n", SDL_GetError());
		return 1;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);

//    screenSurface = SDL_GetWindowSurface(window);
//    SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xA0, 0x06, 0xFF));
//    SDL_UpdateWindowSurface(window);

	//SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0x00, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);

	SDL_Event event;

	random_scene(renderer);
//	draw_scene(renderer);
//	system("sudo leaks RTv1 | grep \"Process\"");
	int quit = 0;

	while (!quit) {

		/* Poll for events */
		while (SDL_PollEvent(&event)) {

			switch (event.type) {
				/* Keyboard event */
				/* Pass the event data onto PrintKeyInfo() */
				case SDL_KEYDOWN:
				case SDL_KEYUP:
					printf("KEYUP: %i\n", event.type);
					break;

					/* SDL_QUIT event (window close) */
				case SDL_QUIT:
					quit = 1;
					break;

				default:
					break;
			}

		}

	}

	SDL_Delay(0);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}

t_vec3	color_by_material(const t_ray r, t_list *list, int depth)
{
	double			t;
	t_vec3			unit_direction;
	t_hit_record	rec;
	t_vec3			attenuation;
	t_ray			scattered;

	if (list_hit(r, 0.001, DBL_MAX, &rec, list))
	{
		if (depth < 50 && rec.mat_ptr->scatter(r, &rec, &attenuation, &scattered))
		{
			/*|(attenuation * color(scattered, list, depth+1))|*/
			return vec_mult(attenuation, color_by_material(scattered, list, depth + 1));
		}
		else
		{
			return (vec(0, 0, 0));
		}
	} else {
		unit_direction = unit_vector(r.B);
		t = .5 * (unit_direction.y + 1.0);
		return vec_plus(vec_mult_scalar(vec(1.0, 1.0, 1.0), (1.0 - t)), vec_mult_scalar(vec(0.5, 0.7, 1.0), t));
	}
}

t_list	*add_sphere_to_world(t_sphere **spheres, t_list *world)
{
	while(*spheres)
	{
		if (!world)
			world = ft_lstnew(*spheres, sizeof(t_vec3) + sizeof(double) + sizeof(t_material) + 10);
		else
			ft_lstadd_end(&world, ft_lstnew(*spheres, sizeof(t_vec3) + sizeof(double) + sizeof(t_material) + 10));
		spheres++;
	}

	return (world);
}


//TODO: Read file with all objects and place their to similar array
t_sphere	**all_spheres()
{
	size_t		col;
	t_sphere	**spheres;

	col = 7;
	spheres = malloc(sizeof(t_sphere *) * col);
	spheres[col] = NULL;
	spheres[0] = new_sphere(vec(0, 0, -1), 0.5, new_material(0, vec(0.1, 0.2, 0.5), "lambertian"));
	spheres[1] = new_sphere(vec(0, -100.5, -1), 100, new_material(0, vec(0.8, 0.8, 0.8), "lambertian"));
	spheres[2] = new_sphere(vec(0, 0, -4), 1, new_material(0, vec(0.6, 0.6, 1.0), "metal"));
	spheres[3] = new_sphere(vec(1, 0, -1), 0.5, new_material(0, vec(1, 0.4, 0.6), "metal"));
	spheres[4] = new_sphere(vec(2, 0, -1), 0.5, new_material(0, vec(0.85, 0.26, 1), "lambertian"));
	spheres[5] = new_sphere(vec(-1, 0, -1), 0.5, new_material(1.5, vec(1, 0.5, 0.9), "dielectric"));
	spheres[6] = new_sphere(vec(-1, 0, -1), -0.45, new_material(1.5, vec(1, 0.5, 0.9), "dielectric"));

	return (spheres);
}


void	delSphere(void *sphere, size_t y)
{
	ft_memdel(&sphere);
}

void	draw_scene(SDL_Renderer *renderer){
	int			nx;
	int			ny;
	t_camera	camera;
	int			antialiasingX;
	t_list		*world;

	world = NULL;

	ny = HEIGHT;
	nx = WIDTH;
	antialiasingX = 8;
	camera = new_camera(vec(-2, 2, 1), vec(0, 0, -1), vec(0, -1, 0), 20, (float)nx / (float)ny);


	t_sphere **spheres = all_spheres();
	world = add_sphere_to_world(spheres, world);

	t_vec3 col;

	for (int j = ny -1; j >= 0 ; j--) {
		for (int i = 0; i < nx; i++) {
			col = vec(0, 0, 0);
			for (int k = 0; k < antialiasingX ; k++) {
				double u = ((double)i + drand48()) / (double)nx;
				double v = ((double)j + drand48()) / (double)ny;
				t_ray ray = get_ray(camera, u, v); /*ray for current coordinates*/
				col = vec_plus(col,color_by_material(ray, world, 0));
			}
			col = vec_division_scalar(col, (double)antialiasingX);
			col = vec(sqrt(col.x), sqrt(col.y), sqrt(col.z));
			t_vec3 draw = vec_mult_scalar(col, 255.99);

			SDL_SetRenderDrawColor(renderer, (Uint8)draw.x, (Uint8)draw.y, (Uint8)draw.z, SDL_ALPHA_OPAQUE);
			SDL_RenderDrawPoint(renderer, i, j);
		}
		SDL_RenderPresent(renderer);
	}

	//CLEARING ALLOCATED MEMORY
	ft_lstdel(&world, delSphere);
	int n = 0;
	while (spheres[n])
	{
		ft_memdel((void **)&spheres[n]);
		n++;
	}
	ft_memdel((void **)&spheres);
	//GRATZ LEAKS = 0
}

float	ft_drand48(){
	float range = (1 - 0);
	float div = RAND_MAX / range;
	return 0 + (rand() / div);
}

void		draw_world(t_camera camera, t_list *world, int antialiasingX, SDL_Renderer *renderer){
	int			nx;
	int			ny;

	ny = HEIGHT;
	nx = WIDTH;
	t_vec3 col;
	for (int j = ny -1; j >= 0 ; j--) {
		for (int i = 0; i < nx; i++) {
			col = vec(0, 0, 0);
			for (int k = 0; k < antialiasingX ; k++) {
				double u = ((double)i + drand48()) / (double)nx;
				double v = ((double)j + drand48()) / (double)ny;
				t_ray ray = get_ray(camera, u, v); /*ray for current coordinates*/
				col = vec_plus(col,color_by_material(ray, world, 0));
			}
			col = vec_division_scalar(col, (double)antialiasingX);
			col = vec(sqrt(col.x), sqrt(col.y), sqrt(col.z));
			t_vec3 draw = vec_mult_scalar(col, 255.99);

			SDL_SetRenderDrawColor(renderer, (Uint8)draw.x, (Uint8)draw.y, (Uint8)draw.z, SDL_ALPHA_OPAQUE);
			SDL_RenderDrawPoint(renderer, i, j);
		}
		SDL_RenderPresent(renderer);
	}

}

void		random_scene(SDL_Renderer *renderer)
{
	int			n = 500;
	t_list		*world;
	t_sphere	**spheres;
	spheres = malloc(sizeof(t_sphere *) * n);
	spheres[n] = NULL;
	spheres[0] = new_sphere(vec(0, -1000, 0), 1000, new_material(0, vec(0.5, 0.5, 0.5), "lambertian"));
	int i = 1;
	t_vec3	center;
	float	choose_mat;
	for (int a = -6; a < 6; a++)
	{
		for (int b = -6; b < 6; b++)
		{
			choose_mat = ft_drand48();
			center = vec(a + 0.9 * ft_drand48(), 0.2, b + 0.9 * ft_drand48());
			if (vec_length(vec_minus(center, vec(4, 0.2, 0))) > 0.9)
			{
				if (choose_mat < 0.8) // diffuse
				{
					spheres[i++] = new_sphere(center, 0.2,
							new_material(0, vec(drand48() * drand48(), drand48() * drand48(), drand48() * drand48()), "lambertian"));
				}
				else if (choose_mat < 0.95) // metal
				{
					spheres[i++] = new_sphere(center, 0.2,
							new_material(0, vec(0.5 * (1 + drand48()), 0.5 * (1 + drand48()), 0.5 * (1 + drand48())), "metal"));
				}
				else // glass
				{
					spheres[i++] = new_sphere(center, 0.2,
							new_material(1.5, vec(0, 0, 0), "dielectric"));
				}
			}
		}
	}

	spheres[i++] = new_sphere(vec(0, 1, 0), 1.0 , new_material(1.5, vec(0, 0, 0), "dielectric"));
	spheres[i++] = new_sphere(vec(-4, 1, 0), 1.0 , new_material(0, vec(0.4, 0.2, 0.1), "lambertian"));
	spheres[i++] = new_sphere(vec(4, 1, 0), 1.0 , new_material(0, vec(0.7, 0.6, 0.5), "metal"));
	spheres[i] = NULL;
	world = add_sphere_to_world(spheres, world);
	t_camera camera = new_camera(vec(13, 5, 3), vec(0, 0, 0), vec(0, -1, 0), 30, (float)WIDTH / (float)HEIGHT);

	draw_world(camera, world, 16, renderer);


	//CLEARING ALLOCATED MEMORY
	ft_lstdel(&world, delSphere);
	n = 0;
	while (spheres[n])
	{
		ft_memdel((void **)&spheres[n]);
		n++;
	}
	ft_memdel((void **)&spheres);
	//GRATZ LEAKS = 0
}
