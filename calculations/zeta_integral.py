#!/usr/bin/env python3
import numpy as np
from pprint import pprint

n = 10000000
midpoint_vals = np.linspace(0 + 0.5 / n, 1 - 0.5 / n, num = n)
left_vals = np.linspace(0, 1 - 1 / n, num = n)
right_vals = np.linspace(0 + 1 / n, 1, num = n)
print(midpoint_vals[0:4])
eta_integrand = lambda beta, v: - 2 * beta * (1 - beta ** 2 * v) ** 0.5 / ( (1 - v) ** 0.5 + beta * (1 - beta ** 2 * v ) ** 0.5)

def integrate_eta(beta, k_min, k_max):
    global eta_integrand
    beta_eta_integrand = lambda x: eta_integrand(beta, x)
    eta_integrand_midpoint_vals = list(map(beta_eta_integrand, midpoint_vals))
    eta_integrand_left_vals = list(map(beta_eta_integrand, left_vals))
    eta_integrand_right_vals = list(map(beta_eta_integrand, right_vals))
    integral_values = []
    for k in range(k_min, k_max + 1):
        k_pow = lambda x: x ** k
        midpoint_rule = sum(map(k_pow, eta_integrand_midpoint_vals)) / n
        left_rule = sum(map(k_pow, eta_integrand_left_vals)) / n
        right_rule = sum(map(k_pow, eta_integrand_right_vals)) / n
        trapezoid_rule = (left_rule + right_rule) / 2
        simpson_rule = (2 * midpoint_rule + trapezoid_rule) / 3
        integral_values.append((beta, k, simpson_rule))
    return integral_values

pprint(integrate_eta(0.4, 0, 20))
