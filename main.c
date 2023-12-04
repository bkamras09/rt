#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <pthread.h>
#include "thread.h"
#include "vec3.h"
#include "ray.h"
#include "paint.h"
#include "io.h"
#include "config.h"
#include "object.h"
#include "camera.h"

// use -lpthread in mkfile to use pthreads

/*
int main() {
	char *output_data = malloc(sizeof(char) * (MAX_FILE_SIZE));

	uint64_t p = make_file_header(output_data);
	
	Camera cam = make_Camera(
		make_Vec3(18, 6, 4),
		make_Vec3(0, 0, -1),
		make_Vec3(0, 1, 0),
		30,
		0.1);

	World world;
	world.object_limit = 7; // WORLD_OBJECT_LIMIT in config.h;

	world.objects[0] = new_lambertian(make_Vec3(-4, 1, 0), make_Vec3(0.1, 0.2, 0.3), 2);
	world.objects[1] = new_lambertian(make_Vec3(0, -1001, -1), make_Vec3(0.5, 0.5, 0.5), 1000);
	world.objects[2] = new_metal(make_Vec3(4, 1, 0), make_Vec3(0.7, 0.6, 0.5), 2, 0);
	world.objects[3] = new_dielectric(make_Vec3(0, 1, 0), 2, 1.5);
	world.objects[4] = new_metal(make_Vec3(3, 1, 3), make_Vec3(0, 0.4, 0.8), 0.2, 0);
	world.objects[5] = new_metal(make_Vec3(2, 0, 2), make_Vec3(0, 0.4, 0.8), 0.2, 0);
	world.objects[6] = new_lambertian(make_Vec3(3, 1, 4), make_Vec3(0.9, 0, 0.3), 0.2);

    int num_threads = 8; // Or any number based on your CPU cores
    pthread_t threads[num_threads];
    ThreadData thread_data[num_threads];
    Vec3 *output_buffer = malloc(sizeof(Vec3) * IMAGE_WIDTH * IMAGE_HEIGHT);

    int section_height = IMAGE_HEIGHT / num_threads;

    for (int i = 0; i < num_threads; i++) {
        thread_data[i].start_row = i * section_height;
        thread_data[i].end_row = (i + 1) * section_height;
        thread_data[i].cam = cam; // Assuming cam and world are already initialized
        thread_data[i].world = world;
        thread_data[i].output_buffer = output_buffer;

        if (pthread_create(&threads[i], NULL, render_section, &thread_data[i])) {
            fprintf(stderr, "Error creating thread\n");
            return 1;
        }
    }

    // Wait for threads to finish
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    // Write output to file
    for (int j = 0; j < IMAGE_HEIGHT; j++) {
        for (unsigned int i = 0; i < IMAGE_WIDTH; i++) {
            Vec3 col = output_buffer[j * IMAGE_WIDTH + i];
            // ... [write col to file] ...
        }
    }

    free(output_buffer);
}
*/


int main()
{
	//create_world();
	//render();
	//save_image();
	//free_world();
	char *output_data = malloc(sizeof(char) * (MAX_FILE_SIZE));

	uint64_t p = make_file_header(output_data);
	
	Camera cam = make_Camera(make_Vec3(18, 6, 4), make_Vec3(0, 0, -1), make_Vec3(0, 1, 0), 30, 0.2);

	World world = create_empty_world();

	add_to_World(&world, new_lambertian(make_Vec3(-4, 1, 0), make_Vec3(0.1, 0.2, 0.3), 2));
	add_to_World(&world, new_lambertian(make_Vec3(0, -1001, -1), make_Vec3(0.5, 0.5, 0.5), 1000));
	add_to_World(&world, new_metal(make_Vec3(4, 1, 0), make_Vec3(0.7, 0.6, 0.5), 2, 0));
	add_to_World(&world, new_dielectric(make_Vec3(0, 1, 0), 2, 1.5));
	add_to_World(&world, new_metal(make_Vec3(3, 1, 3), make_Vec3(0, 0.4, 0.8), 0.2, 0));
	add_to_World(&world, new_metal(make_Vec3(2, 0, 2), make_Vec3(0, 0.4, 0.8), 0.2, 0));
	add_to_World(&world, new_lambertian(make_Vec3(3, 1, 4), make_Vec3(0.9, 0, 0.3), 0.2));

	for (int j = IMAGE_HEIGHT - 1; j >= 0; j--) {
		for (unsigned int i = 0; i < IMAGE_WIDTH; i++) {
			Vec3 col = make_Vec3(0, 0, 0);
			for (unsigned int s = 0; s < NUMBER_OF_SAMPLES; s++) {
				float u = (float)(i + drand48()) / (float)IMAGE_WIDTH;
				float v = (float)(j + drand48()) / (float)IMAGE_HEIGHT;
				ray r = get_ray(u, v, cam);

				// Vec3 pt = pt_at_param(r, 2.0);
				col = add_inc_Vec3(col, color(r, &world, 0));
			}

			col = div_dec_Vec3(col, (float)NUMBER_OF_SAMPLES);
			col = make_Vec3((float)sqrt(col.e[0]), (float)sqrt(col.e[1]), (float)sqrt(col.e[2]));

			p = write_pixels_to_file(output_data, col.e[0], col.e[1], col.e[2], p);
		}
	}

	output_data[p] = '\0';

	write_image(OUTPUT_FILE_NAME, output_data);

	// free_world(w, c);
	free(output_data);

	return 0;
}