#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

// Fungsi yang akan diintegrasikan
double f(double x)
{
    return exp(x);
}

// Fungsi Integrasi Romberg
double rombergIntegration(double (*f)(double), double a, double b, double eps = 1e-6)
{
    vector<vector<double>> R(1, vector<double>(1, 0.5 * (b - a) * (f(a) + f(b))));
    int n = 1;
    while (true)
    {
        double h = (b - a) / pow(2, n);
        double sum_f = 0.0;
        for (int k = 1; k <= pow(2, n - 1); ++k)
        {
            sum_f += f(a + (2 * k - 1) * h);
        }
        vector<double> row(1, 0.5 * R[n - 1][0] + sum_f * h);
        for (int m = 1; m <= n; ++m)
        {
            row.push_back(row[m - 1] + (row[m - 1] - R[n - 1][m - 1]) / (pow(4, m) - 1));
        }
        if (abs(row.back() - R[n - 1].back()) < eps)
        {
            return row.back();
        }
        R.push_back(row);
        ++n;
    }
}

int main()
{
    double a = 0;
    double b = 4;
    double result = rombergIntegration(f, a, b);
    cout << "Hasil integrasi dengan metode Romberg: " << result << endl;
    return 0;
}
