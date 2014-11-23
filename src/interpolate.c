#include <math.h>

/**
 * Computes quadratic polynomial coefficients from 3 points.
 *
 * Given 3 points with x,y finds a,b,c of (ax^2 + bx + c). This enables polynomial interpolation/extrapolation.
 *
 * License: CC0/public domain
 */

#include "interpolate.h"

static void matrix3x3_inverse(const double m[restrict static 3][3], double out[restrict static 3][3])
{
	const double det = m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1]) -
	                   m[1][0] * (m[0][1] * m[2][2] - m[2][1] * m[0][2]) +
	                   m[2][0] * (m[0][1] * m[1][2] - m[1][1] * m[0][2]);

	const double invdet = det ? 1.0 / det : 0;

	out[0][0] = (m[1][1] * m[2][2] - m[1][2] * m[2][1]) * invdet;
	out[1][0] = (m[2][0] * m[1][2] - m[1][0] * m[2][2]) * invdet;
	out[2][0] = (m[1][0] * m[2][1] - m[2][0] * m[1][1]) * invdet;
	out[0][1] = (m[2][1] * m[0][2] - m[0][1] * m[2][2]) * invdet;
	out[1][1] = (m[0][0] * m[2][2] - m[2][0] * m[0][2]) * invdet;
	out[2][1] = (m[0][1] * m[2][0] - m[0][0] * m[2][1]) * invdet;
	out[0][2] = (m[0][1] * m[1][2] - m[0][2] * m[1][1]) * invdet;
	out[1][2] = (m[0][2] * m[1][0] - m[0][0] * m[1][2]) * invdet;
	out[2][2] = (m[0][0] * m[1][1] - m[0][1] * m[1][0]) * invdet;
}

static void matrix3x3_multiply1x3(const double m[restrict static 3][3], const double b[restrict static 3], double out[restrict static 3])
{
	out[0] = m[0][0]*b[0] + m[0][1]*b[1] + m[0][2]*b[2];
	out[1] = m[1][0]*b[0] + m[1][1]*b[1] + m[1][2]*b[2];
	out[2] = m[2][0]*b[0] + m[2][1]*b[1] + m[2][2]*b[2];
}

void quadratic_polynomial_from_points(const point_xy points[restrict 3], double out[restrict 3]) {
	double x[3][3], invx[3][3];
	double y[3];

	for(int i = 0; i < 3; i++) {
		x[i][0] = points[i].x * points[i].x;
		x[i][1] = points[i].x;
		x[i][2] = 1;
		y[i] = points[i].y;
	}

	matrix3x3_inverse(x, invx);
	matrix3x3_multiply1x3(invx, y, out);
}

inline static double sign(double x) {
	return (x > 0) - (x < 0);
}

double root_in_range(double poly[static 3], double min, double max, double fallback) {
	const double delta = poly[1]*poly[1] - 4.0 * poly[0] * poly[2];

	if (delta > 0) {
		const double q = -0.5 * (poly[1] + sign(poly[1]) * sqrt(delta));

		const double x1 = q / poly[0];
		if (x1 >= min && x1 <= max) {
			return x1;
		}

		const double x2 = poly[2] / q;
		if (x2 >= min && x2 <= max) {
			return x2;
		}
	}

	return fallback;
}
