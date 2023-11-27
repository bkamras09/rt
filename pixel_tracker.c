#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "io.h"
#include "pixel_tracker.h"

// Schlemeil remembers to take his bucket with him
uint64_t str_cat_next_pos(char dest[], char src[], uint64_t pos) {
	for(uint64_t i = 0; src[i] != '\0'; i++ ) { dest[pos++] = src[i]; }

	return pos;
}