#pragma once

#include <vector>

class euler_method {
 public:
  template <typename F>
  std::vector<double> integrate(const F& f, double h,
                                double x0, double x_end,
                                const std::vector<double>& y0) {
    // clear the arrays so that we start fresh every time we call this function
    xs.clear();
    result.clear();

    double x = x0;
    std::vector<double> y = y0;
    while(x <= x_end) {
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
    
    // You can't directly add two std::vector<double> together, so you need to loop
    // through the elements of y and add the corresponding elements of f(x, y).
    for (int i = 0; i < y.size(); i++) {
      y_next[i] += h * f(x, y)[i];
    }
    return y_next;
  }

  std::vector<double> xs;
  std::vector<std::vector<double>> result;
};
