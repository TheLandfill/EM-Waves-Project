#include "integration.h"
#include "eta_integration.h"
#include "value_list.h"
#include "real.h"
#include <iostream>
#include <limits>

typedef std::numeric_limits<double> dbl;

int main() {
	const unsigned int NUM_INTERVALS = 1 << 6;
	const size_t num_threads = 2;
	const size_t num_chunks = 1 << 19;
	std::cout << "Using " << (NUM_INTERVALS * num_threads * num_chunks) << " intervals for the integrals.\n";
	#ifdef BINOMIAL_TEST
		for (unsigned int i = 0; i <= 20; i++) {
			for (unsigned int j = 0; j <= i; j++) {
				std::cout << "(" << i << ", " << j << "):\t" << (double)binomial(i, j) << "\n";
			}
		}
		return 0;
	#endif
	const unsigned int max_n = 20;
	const unsigned int max_power = max_n * 2 + 1;
	const real beta = 0.4;
	Multiple_Eta_Integrand default_beta_eta_integral(beta, max_power);
	Value_List vl(max_power);
	real a = 0.0;
	real b = 1.0;
	const real chunk_step = (b - a) / (((real)num_threads) * ((real)num_chunks));
	const real thread_step = (b - a) / 4.0;
	#pragma omp parallel for
	for (size_t i = 0; i < num_threads; i++) {
		const real thread_start = thread_step * i + a;
		Value_List vl_local(max_power);
		for (size_t j = 0; j < num_chunks; j++) {
			Simpson_Points sp(thread_start + chunk_step * j, thread_start + chunk_step * (j + 1), NUM_INTERVALS);
			Simpson_Sums<Value_List> ss{max_power, max_power, max_power};
			vl_local += simpson_rule<Value_List>(default_beta_eta_integral, sp, ss);
		}
		#pragma omp critical
		vl += vl_local;
	}
	std::cout << "Values of eta(beta, k)\n";
	std::cout << std::fixed;
	std::cout.precision(dbl::digits10);
	for (size_t i = 0; i < vl.get_size(); i++) {
		std::cout << i << ":\t" << (double)vl[i] << "\n";
	}
	std::cout << "\nValues of zeta(N, beta)\n";
	Value_List zl(max_n + 1);
	for (size_t i = 0; i <= max_n; i++) {
		real zeta = 0.0;
		for (size_t j = 0; j <= 2 * i; j++) {
			zeta += binomial(2 * i, j) * vl[j];
		}
		zeta *= beta * beta / 2.0;
		zl[i] = zeta;
		std::cout << i << ":\t" << (double)zeta << "\n";
	}
	std::cout << "\nzeta(N, beta) - zeta(N + 1, beta)\n";
	for (size_t i = 0; i < max_n; i++) {
		std::cout << i << "&    " << (double)(zl[i] - zl[i + 1]) << "\n";
	}
	return 0;
}
