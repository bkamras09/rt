/*#include "camera.h"
#include "object.h"
#include "paint.h"
#include "material.h"
#include "vec3.h"
#include "vec3.h"

typedef struct {
    int start_row;
    int end_row;
    Camera cam;
    World world;
    Vec3 *output_buffer; // Array to store the output color for each pixel
} ThreadData;

void* render_section(void *arg) {
    ThreadData *data = (ThreadData *)arg;

    for (int j = data->start_row; j < data->end_row; j++) {
        for (unsigned int i = 0; i < IMAGE_WIDTH; i++) {
            Vec3 col = make_Vec3(0, 0, 0);
            for (unsigned int s = 0; s < NUMBER_OF_SAMPLES; s++) {
                float u = (float)(i + drand48()) / (float)IMAGE_WIDTH;
                float v = (float)(j + drand48()) / (float)IMAGE_HEIGHT;
                ray r = get_ray(u, v, data->cam);
                col = add_inc_Vec3(col, color(r, &data->world, 0));
            }
            col = div_dec_Vec3(col, (float)NUMBER_OF_SAMPLES);
            col = make_Vec3(sqrt(col.e[0]), sqrt(col.e[1]), sqrt(col.e[2]));
            data->output_buffer[j * IMAGE_WIDTH + i] = col;
        }
    }

    return NULL;
}*/