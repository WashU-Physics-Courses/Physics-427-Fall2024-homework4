#pragma once

#include <vector>

class implicit_euler_method {
 public:
  template <typename F, typename dF>
  double integrate(const F& f, const dF& dfdy, double h,
                   double x0, double x_end, double y0) {
    // clear the arrays so that we start fresh every time we call this function
    xs.clear();
    result.clear();

    double x = x0;
    double y = y0;
    while(x <= x_end) {
      // append x and y to the result array
      xs.push_back(x);
      result.push_back(y);

      // compute the next step in y
      y = step(f, dfdy, h, x, y);
      x += h;
    }
    return y;
  }

  template <typename F, typename dF>
  double step(const F& f, const dF& dfdy, double h,
              double x, double y) {
    // Compute the next step in y, given x and y of the current step
    double y_next = y;

    // TODO: Finish this implementation, using Newton's method to solve the implicit equation
    
    return y_next;
  }

  std::vector<double> xs;
  std::vector<double> result;
};

