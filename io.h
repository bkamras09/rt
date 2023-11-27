#ifndef IOH
#define IOH
#include <stdio.h>
#include <stdint.h>

void write_image(const char *filepath, const char *data);
uint64_t make_file_header(char *output);
uint64_t str_cat_next_pos(char *output, char *s, uint64_t p);
uint64_t write_pixels_to_file(char *output, float r, float g, float b, uint64_t p);

#endif
