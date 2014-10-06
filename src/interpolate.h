typedef struct {
	double x,y;
} point_xy;

void quadratic_polynomial_from_points(const point_xy points[restrict 3], double out[restrict 3]);
double root_in_range(double poly[static 3], double min, double max, double fallback);
