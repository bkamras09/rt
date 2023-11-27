#ifndef IOC
#define IOC

#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include "io.h"

void write_image(const char *filepath, const char *data)
{
	if (remove(OUTPUT_FILE_NAME) == 0) {
		printf("Deleted old image successfully.\n");
	}
    else {
    	printf("Unable to delete the file.\nFile was either not present or an error occurred.\n");
    }

	FILE *fp = fopen(filepath, "ab");
	if ( fp ) {
		fputs(data, fp);
		fclose(fp);
	}
}

uint64_t make_file_header(char *output) {
	uint64_t p = 0;
	char width_as_string[8];
	char height_as_string[8];
	snprintf(width_as_string, 8, "%d", IMAGE_WIDTH);
	snprintf(height_as_string, 8, "%d", IMAGE_HEIGHT);
	p = str_cat_next_pos(output, "P3\n", p);
	p = str_cat_next_pos(output, width_as_string, p);
	p = str_cat_next_pos(output, " ", p);
	p = str_cat_next_pos(output, height_as_string, p);
	p = str_cat_next_pos(output, "\n", p);
	p = str_cat_next_pos(output, "255\n", p);

	return p;
}

uint64_t write_pixels_to_file(char *output, float r, float g, float b, uint64_t p) {
	int red = (int)255.99 * r;
	int green = (int)255.99 * g;
	int blue = (int)255.99 * b;
	
	char red_as_string[8];
	char green_as_string[8];
	char blue_as_string[8];
			
	snprintf(red_as_string, 5, "%d", red);
	snprintf(green_as_string, 5, "%d", green),
	snprintf(blue_as_string, 5, "%d", blue);

	p = str_cat_next_pos(output, red_as_string, p);
	p = str_cat_next_pos(output, " ", p);
	p = str_cat_next_pos(output, green_as_string, p);
	p = str_cat_next_pos(output, " ", p);
	p = str_cat_next_pos(output, blue_as_string, p);
	p = str_cat_next_pos(output, "\n", p);	
}

#endif
