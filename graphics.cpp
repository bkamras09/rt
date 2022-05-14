#include <stdio.h>

int main() {
	int nx = 200;
	int ny = 100;

	FILE *fp;
	fp = fopen("img.ppm", "w");

	fprintf(fp, "%s", "P3\n");
	fprintf(fp, "%d", nx);
	fprintf(fp, "%s", " ");
	fprintf(fp, "%d", ny);
	fprintf(fp, "%s", "\n255\n");

	for (int j = ny-1; j >= 0; j--) {
		for (int i = 0; i < nx; i++) {
			float r = float(i) / float(nx);
			float g = float(j) / float(ny);
			float b = 0.2;

			int ir = int(255.99 * r);
			int ig = int(255.99 * g);
			int ib = int(255.99 * b);

			fprintf(fp, "%d", ir);
			fprintf(fp, "%s", " ");
			fprintf(fp, "%d", ig);
			fprintf(fp, "%s", " ");
			fprintf(fp, "%d", ib);
			fprintf(fp, "%s", "\n");
		}
	}

	fclose(fp);
	return 0;
}
