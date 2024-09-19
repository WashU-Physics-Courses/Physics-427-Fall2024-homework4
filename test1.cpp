#include "rk4.h"
#include <cmath>
#include <fstream>

int main() {
  // Define our right hand side
  auto dydx = [](double x, const std::vector<double> &y) {
    return std::vector<double>{std::cos(x)};
  };

  // Integrate the equation until the stop condition
  runge_kutta_4 rk4(1);

  double h = 0.01;
  double x0 = 0.0;
  double x_end = 10.0;
  std::vector<double> y0 = {0.0};
  rk4.integrate(dydx, h, x0, x_end, y0);

  // Write the results into a csv file
  std::ofstream output_file("output1.csv");
  for (int i = 0; i < rk4.xs.size(); i++) {
    output_file << rk4.xs[i] << "," << rk4.result[i][0] << std::endl;
  }
  output_file.close();

  return 0;
}
