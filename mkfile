CC=gcc
	rt: main.c
	$CC -lm main.c io.c ray.c vec3.c pixel_tracker.c paint.c object.c camera.c -o rt -lpthread -Wall -O3
