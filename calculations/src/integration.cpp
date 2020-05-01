#include "integration.h"
#include "real.h"

Simpson_Points::Simpson_Points(real a, real b, size_t n) :
start(a),
dx((b - a)/((real)n)),
n(n) {}
