#pragma once

#include <vector>

class runge_kutta_4 {
public:
  runge_kutta_4(int num_equations) {
    // constructor, initialize the data members
    n_eq = num_equations;
    y_tmp.resize(n_eq);
    k1.resize(n_eq);
    k2.resize(n_eq);
    k3.resize(n_eq);
    k4.resize(n_eq);
  }

  template <typename F>
  std::vector<double> integrate(const F &f, double h,
                                double x0, double x_end,
                                const std::vector<double> &y0) {
    // clear the arrays so that we start fresh every time we call this function
    xs.clear();
    result.clear();

    double x = x0;
    std::vector<double> y = y0;
    while (x <= x_end) {
      // append x and y to the result array
      xs.push_back(x);
      result.push_back(y);

      // compute the next step in y
      y = step(f, h, x, y);
      x += h;
    }
    return y;
  }

  template <typename F>
  std::vector<double> step(const F& f, double h, double x, const std::vector<double> &y) {
    // Compute the next step in y, given x and y of the current step
    std::vector<double> y_next = y;

    // TODO: Finish this implementation, refer to the euler.h if you are
    // unsure where to start.

    return y_next;
  }

  int n_eq;
  std::vector<double> k1, k2, k3, k4, y_tmp;
  std::vector<double> xs;
  std::vector<std::vector<double>> result;
};
