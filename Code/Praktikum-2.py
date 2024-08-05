import numpy as np

def romberg_integration(f, a, b, eps=1e-6):
    R = [[0.5 * (b - a) * (f(a) + f(b))]]  # R[0][0]
    n = 1

    while True:
        h = float(b - a) / 2**n
        sum_f = sum(f(a + (2*k - 1) * h) for k in range(1, 2**(n-1) + 1))
        row = [0.5 * R[n-1][0] + sum_f * h]  # R[n][0]
        row.extend(
            row[m - 1] + (row[m - 1] - R[n - 1][m - 1]) / (4**m - 1)
            for m in range(1, n + 1)
        )
        if abs(row[-1] - R[n-1][-1]) < eps:
            return row[-1]
        R.append(row)
        n += 1

# Function to integrate
def f(x):
    return np.exp(x)

# Define the interval
a = 0
b = 4

# Perform Romberg Integration
romberg_result = romberg_integration(f, a, b)
print(f'Hasil integrasi dengan metode Romberg: {romberg_result}')
