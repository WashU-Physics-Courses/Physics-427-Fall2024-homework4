# Physics 427 Homework 4

__Due 11:59pm Wednesday 9/25/2024__

## 0. Setting up a Python environment

We are going to use Python to plot the results of our computation. If you already have a Python environment, then feel free to skip this section. Here are the ways you can set up Python on Mac, WSL, and Linux. I strongly suggest Python 3, since Python 2 is already deprecated. 

__On Mac__, you can install Python through `homebrew`:

``` sh
brew install python
```

Alternatively, you can also just download `Anaconda` from its official website. It sets up a Python environment for you.

__On WSL__, you are effectively in a Ubuntu system. Install the Python package using:

``` sh
sudo apt-get install python3 python3-pip
```
Remember to install these in WSL if you are using it. If you use WSL but install for example `Anaconda` in your Windows system, it won't be able to access your files in WSL.

__On Liunx__, use the package manager of your distribution. 

__Once you have installed Python__, install the required Python packages using `pip` (or `pip3` for ubuntu):

``` sh
pip install numpy matplotlib jupyter
```

These packages should get you started. You may want to also install the Jupyter plugin for VS Code, so that you can run notebooks directly in VS Code. Install other packages as we go if need be.

## 1. Implementing RK4 (10 points)

In the repository, I have included an example implementation of the Euler's
method, `euler.h`. Take a look at the code, and try to understand it as much as
possible. The `euler_method` class has a method called `integrate`, which is what you call to solve the given ODE initial value problem. You need to pass in a function `f`, which describes the right hand side of the ODE $d\mathbf{y}/dx = f(x, \mathbf{y})$. Then, you need to pass in the step size `h`, the initial $x$ value `x0`, the final $x$ value `x_end`, and finally the initial $y$ value `y0`. The function stores a vector of `x`s and a vector of `y`s, and returns the final $y$ value at $x = x_\mathrm{end}$.

I have included a skeleton file for a 4th-order Runge-Kutta solver,
`rk4.h`. You task is to fill out the function bodies with a TODO comment and finish the implementation.

To help you debug your code, I also included a simple test file `test1.cpp` to
run the solver through the simplest equation, $dy/dx = \cos x$. Its output,
`output1.csv`, can be used to check against your expected solution (what is the
expected solution?) to see whether your RK4 is implemented correctly. You may need to load it into Python and plot it in order to see how the solution goes.

Note that RK4 requires some intermediate values during evaluation, and we can store them in the class. It is convenient to define `k1`, `k2`, `k3`, `k4`, and a temporary vector `y_tmp` to store the estimated `y` values, e.g. $y_n + hk_1/2$. These should be initialized to the number of equations you are solving, so we resize them to the right length in the _constructor_ of the class. The constructor of a class is a function with the same name as the class name, and no return value. Its job is usually to initialize the various data members of the class:

``` c++
class runge_kutta_4 {
public:
  runge_kutta_4(int num_equations) {
    n_eq = num_equations;
    y_tmp.resize(n_eq);
    k1.resize(n_eq);
    k2.resize(n_eq);
    ...
  }
};
```

Commit your changes to the `rk4.h` file to the repository. Do not commit the output `csv` files to the repository. You should consider adding `*.csv` to the `.gitignore` file under your homework folder, so that `git` automatically ignores these output files.

## 2. Convergence Test (10 points)

Now that we have at least 2 ODE solvers implemented in C++, we can check and compare their accuracy. We will again use the simple equation $dy/dx = \cos x$ with an initial condition $y(0) = 0$. Write a program `problem2.cpp` to solve this equation over the interval $x\in [0, 10]$ using the two classes `euler_method` and `runge_kutta_4` defined in the respective header files. Use a series of step sizes $h \in [1.0, 0.1, 0.01, 0.001]$ for each method. Write the last $y$ value returned by the `integrate` method to a `csv` file and read them in Python. Plot the deviation of the final $y$ from the expected value, $y = \sin(10)$ for the two methods. You should be able to get a plot similar to what is shown in Lecture 7 (except for the Midpoint method line). Save the plot as `problem2.png` and push it to the repository, together with the Python file you used to generate the plot as either `problem2.py` or `problem2.ipynb`. Do not push the `csv` output files.

Notice that you $x$ axis in the plot should be the step size $h$. However, the axis is increasing to the right by default. You can make it decreasing using:

``` python
ax = plt.gca()
ax.invert_xaxis()
```
Finally, remember to label your $x$ and $y$ axes and remember to include a legend indicating which line is which.

## 3. Implicit Euler and Stiff Problems (15 points)

In this problem, we explore stiff problems. Consider the following ODE:

$$
\frac{dy}{dx} = -100y + 3\sin x = f(x, y),\quad y(0) = 1
$$

The relatively large ratio between the coefficients should already tip you off that the ODE is probably "stiff". Our goal in this problem is to solve this equation correctly. First, in the header file `implicit_euler.h`, implement the implicit Euler integration method covered in Lecture 8. I have already included a skeleton file in this repository, and similar to Problem 1, you need to fill in the part marked as "TODO". Since the implicit Euler method requires root finding at each step, it is assumed that we use Newton's method to solve the equation, therefore in the `integrate` function we also need to pass in the derivative $\partial f/\partial y$. You can reuse your Newton-Raphson implementation in Homework 2.

Write a program `problem3.cpp` to test your implicit Euler solver and compare it with RK4. In this program, solve the above ODE using both methods on the interval $x\in [0, 1]$. For RK4, use two step sizes such that one leads to a reasonable solution and the other leads to instability. For implicit Euler, use a step size that is larger than the unstable RK4 step size that you chose earlier. Plot the 3 results on the same graph using Python, together with the exact solution:

$$
y(x) = \frac{10004 e^{-100 x} - 3\cos x + 300\sin x}{10001}
$$

In order for the plot to make sense, you may need to use logarithmic scale on the $y$ axis:

``` python
ax = plt.gca()
ax.set_yscale('log')
```

Remember to include a legend in the plot, so that we know which curve corresponds to what. Also remember to label your $x$ and $y$ axes. Save the plot as `problem3.png` and commit it to the repository, along with your `implicit_euler.h` and `problem3.cpp`. Also commit the python file you used to make the plot as `problem3.py` or `problem3.ipynb` to the repository, since we want to be able to reproduce your plot. Again, do not commit any output `csv` files.

## 4. The Nonlinear Pendulum Revisited (15 points)

For our physics application, let's solve the complete equation of motion of the nonlinear pendulum we looked at in Homework 3. The equation of motion can be written as:

$$
\frac{d^2\theta}{dt^2} + \frac{g}{L}\sin\theta = 0
$$

If we define $x = t/\sqrt{L/g}$, then $x$ is dimensionless (see Lecture 4). The equation becomes:

$$
\frac{d^2\theta}{dx^2} = -\sin\theta
$$

This is a 2nd order ODE. To convert it to a system of 1st order ODEs, we will introduce a new unknown function $\omega = d\theta/dx$. Then, the two-equation system can be written as:

$$
\frac{d\theta}{dx} = \omega,\quad \frac{d\omega}{dx} = -\sin\theta
$$

Your task is to use both Euler's method and RK4 to solve the equations above, and compare the results. Choose your initial condition such that $x_0 = 0$ and $\theta_0 = \theta_\mathrm{max}$ (what is the initial $\omega$ then?). For maximum deviation from the regular pendulum, set $\theta_\mathrm{max} = 179^\circ$ (remember to convert it to radians in the code). Use a step size where these two methods give you visibly different results. Run for 2 periods. Remember you can use your program from Homework 3 to calculate the period. This is a place where $N=10$ Gauss quadrature might give you a not-so-accurate answer. Try adaptive Simpson and target a high precision like $10^{-10}$.

Finally, plot both curves of $\theta$ vs $x$ in Python and include the plot in the repo as `problem4.png`. Remember to add an $x$ label and $y$ label to the axes of the plot, and add a legend so that we know which curve corresponds to which method. Write the period that you calculated as the title of the plot, together with the step size you chose:

``` python
ax = plt.gca()
ax.set_title(f"T = {period:.4e}, h = {h:.2e}")
```

Add your source file to the repo as `problem4.cpp`, and your python file as `problem4.py` or `problem4.ipynb`. We would like someone with the code to be able to reproduce your plot. Again, do not commit the `csv` files to the repository.
