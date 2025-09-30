#include <stdio.h>
#include <malloc.h>

typedef struct shape {
	int width;
	int height;
	double tri_area;
	int squ_area;
	int radius;
	double pi;
	double cir_area;
} shape;

void shape_tri_area(shape* pmy);
void shape_squ_area(shape* pmy);
void shape_cir_area(shape* pmy);
void shape_menu_area(shape* pmy);
shape* shape_init_area(void);