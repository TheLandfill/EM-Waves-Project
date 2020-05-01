#include "eta_integration.h"
#include "real.h"
#include <cmath>

real binomial(unsigned int n, unsigned int k) {
	real result = 1.0;
	for (unsigned int i = k; i > 0; i--) {
		result *= ((real)(n - k + i)) / ((real)(i));
	}
	return result;
}

real eta_integrand(real beta, real v) {
	real beta_sqrt_term = beta * sqrt(1.0 - beta * beta * v);
	real sqrt_term = sqrt(1.0 - v);
	return - 2.0 * beta_sqrt_term / ( sqrt_term + beta_sqrt_term );
}

real exponentiation_by_squaring(real val, unsigned int n) {
	real result = 1.0;
	real cur_square = val;
	while (n != 0) {
		result *= cur_square * (n & 1);
		n >>= 1;
		cur_square *= cur_square;
	}
	return result;
}

Multiple_Eta_Integrand::Multiple_Eta_Integrand(real beta, unsigned int k) : beta(beta), k(k) {}

void Multiple_Eta_Integrand::operator()(Value_List& holder, real v) {
	real eta_base = eta_integrand(beta, v);
	holder[0] = 1.0;
	for (size_t i = 1; i < k; i++) {
		holder[i] = holder[i - 1] * eta_base;
	}
}
