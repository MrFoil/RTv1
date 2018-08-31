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
#include <vector_math.h>
#include <stdio.h>
#include <stdbool.h>

#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 300


double	hit_sphere(const t_vec3 center, double radius, const t_ray ray){
	t_vec3 oc = vec_minus(ray.A, center);
	// dot(B,B) + 2 * dot(B, A-C) + dot(A-C, A-C) - R*R = 0;
	double a = dot_vec(ray.B, ray.B);
	double b = 2.0 * dot_vec(oc, ray.B);
	double c = dot_vec(oc, oc) - radius * radius;
	double discriminant = b*b - 4 * a * c;
	if(discriminant < 0){
		return (-1.0);
	} else{
		return ((-b - sqrt(discriminant)) / (2.0*a));
	}
}

t_vec3	color(const t_ray r)
{
	double  t;
    t_vec3  unit_direction;

	unit_direction = unit_vector(r.B);
	t = .5 * (unit_direction.y + 1.0);
	return vec_plus(vec_mult_scalar(new_vec(1.0, 1.0, 1.0), (1.0 - t)), vec_mult_scalar(new_vec(0.5, 0.7, 1.0), t));
}

void	draw_scene(SDL_Renderer *renderer){
	int nx = SCREEN_WIDTH;
	int ny = SCREEN_HEIGHT;


	/*Camera*/
	t_vec3 lower_left_corner = new_vec(-2, -1, -1);
	t_vec3 horizontal = new_vec(4, .0, .0);
	t_vec3 vertical = new_vec(.0, 2, .0);
	t_vec3 origin = new_vec(.0, .0, .0); /*"EYE" camera position*/
	t_vec3 col;

	for (int j = ny - 1; j >= 0 ; j--) {
		for (int i = 0; i < nx; i++) {
			double u = (double) i / (double) nx;
			double v = (double) j / (double) ny;
			t_ray ray = new_ray(origin, // A
					vec_plus(vec_plus(lower_left_corner,vec_mult_scalar(horizontal, u)), vec_mult_scalar(vertical, v))); /* B = lover_left_corner + u*horizontal + v*vertical */
			t_vec3	center = new_vec(.0, .0 , -1); // Sphere center
			double	t = hit_sphere(center, 0.5, ray);
			if (t > 0.0)
			{
				t_vec3 temp = point_at_parameter(ray.A, ray.B, t);
				t_vec3 temp1 = vec_minus(temp, center);
				t_vec3 N = unit_vector(temp1); // Нормаль для текущей точки
				col = vec_mult_scalar(new_vec(N.x + 1, N.y + 1, N.z + 1), 0.5);
			}
			else
			{
				col = color(ray);
			}

			t_vec3 draw = vec_mult_scalar(col, (int)255.99);

			SDL_SetRenderDrawColor(renderer, draw.x, draw.y, draw.z, SDL_ALPHA_OPAQUE);
			SDL_RenderDrawPoint(renderer, i, j);
		}
	}

}

int main(int argc, char *args[]) {
    SDL_Window *window = NULL;
    SDL_Surface *screenSurface = NULL;
    SDL_Renderer *renderer = NULL;


    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("%s%s\n", "could not initialize sdl2: %s\n", SDL_GetError());
        return 1;
    }

    window = SDL_CreateWindow(
            "hello_sdl2",
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH, SCREEN_HEIGHT,
            SDL_WINDOW_SHOWN
    );
    if (window == NULL) {
        fprintf(stderr, "could not create window: %s\n", SDL_GetError());
        return 1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    screenSurface = SDL_GetWindowSurface(window);
    SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xA0, 0x06, 0xFF));
    SDL_UpdateWindowSurface(window);

    //SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0x00, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    SDL_Event event;

	draw_scene(renderer);

    SDL_RenderPresent(renderer);

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