CC=gcc
	rt: main.c
	$CC -lm main.c io.c ray.c vec3.c pixel_tracker.c paint.c material.c material.h object.c -o rt -Wall
