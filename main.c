#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include "vec3.h"
#include "ray.h"
#include "paint.h"
#include "io.h"
#include "config.h"
#include "object.h"
#include "camera.h"

int main() {
	char *output_data = malloc(sizeof(char) * ( MAX_FILE_SIZE ) ); 
	uint64_t p = make_file_header(output_data);
	Camera cam = make_Camera();

	World world;
	world.object_limit = 3; //WORLD_OBJECT_LIMIT in config.h;
	float q;
	
	world.objects[0] = make_Object(q, 0.5, make_Vec3(0, 0, 0), make_Vec3(0, 0, 0), make_Vec3(0, 0, -1));
	world.objects[1] = make_Object(q, 0.8, make_Vec3(0, -0.3, 0), make_Vec3(0, 0, 0), make_Vec3(0.4, 1, -2));
	world.objects[2] = make_Object(q, 100, make_Vec3(0, 0, 0), make_Vec3(0, 0, 0), make_Vec3(0, -100.5, -1));
	for (int j = IMAGE_HEIGHT - 1; j >= 0; j--) {
		for (unsigned int i = 0; i < IMAGE_WIDTH; i++) {
			Vec3 col = make_Vec3(0, 0, 0);
			for (unsigned int s = 0; s < NUMBER_OF_SAMPLES; s++) {
				float u = (float)( i + drand48()) / (float)IMAGE_WIDTH;
				float v = (float)( j + drand48()) / (float)IMAGE_HEIGHT;
				ray r = get_ray(u, v, cam);
				Vec3 pt = pt_at_param(r, 2.0);
				col = add_inc_Vec3(col, color(r, &world));
			}

			col = div_dec_Vec3(col, (float)NUMBER_OF_SAMPLES);
			col = make_Vec3((float)sqrt(col.e[0]), (float)sqrt(col.e[1]), (float)sqrt(col.e[2]));
			
			p = write_pixels_to_file(output_data, col.e[0], col.e[1], col.e[2], p);
			
		}
	}
	output_data[p] = '\0';

	write_image(OUTPUT_FILE_NAME, output_data);

	return 0;
}
