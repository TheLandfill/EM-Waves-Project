#ifndef ETA_INTEGRATION_H
#define ETA_INTEGRATION_H
#include "value_list.h"
#include "real.h"

class Multiple_Eta_Integrand {
private:
	real beta;
	unsigned int k;
public:
	Multiple_Eta_Integrand(real beta, unsigned int k);
	void operator()(Value_List& holder, real v);
};

real binomial(unsigned int n, unsigned int k);

#endif
