#ifndef CONFIG
#define CONFIG
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define DIM_STRING_LENGTH 4

static const uint COLOR_DEPTH = 255;
static const uint IMAGE_WIDTH = 1000;
static const int IMAGE_HEIGHT = 500;
static const uint NUMBER_OF_SAMPLES = 1000;
static const uint FILE_WIDTH = 8; //255 255\n
static const uint FILE_HEADER_LENGTH = 16; // P3\n1920 1080\n255
static const uint WORLD_OBJECT_LIMIT = 256;
static const float GAMMA = 0.5;

static char WIDTH_STRING[DIM_STRING_LENGTH];
static char HEIGHT_STRING[DIM_STRING_LENGTH];

static const char *OUTPUT_FILE_NAME = "output.ppm";
static const uint64_t MAX_FILE_SIZE = FILE_WIDTH + IMAGE_HEIGHT * IMAGE_WIDTH * FILE_HEADER_LENGTH + 1;  // for '\0'

uint64_t make_header(char *output, uint64_t pos);

#endif
