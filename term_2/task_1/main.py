import math


def bisections(func, a, b, epsilon):
    cnt = 0

    while b - a > epsilon:
        cnt += 1
        # print(cnt)

        c = (a + b) / 2

        if func(c) * func(a) < 0:
            b = c
        elif func(c) * func(b) < 0:
            a = c
        elif func(c) == 0:
            return c

    return f"\nSolution: {(a + b) / 2}\nIterations: {cnt}"


def derivative(func, x, epsilon):
    return (func(x + epsilon) - func(x)) / epsilon


def fixed_point_iteration(func, a, epsilon, newton=False, sor=False):
    sgn = 1 if derivative(func, a, 10**(-9)) > 0 else -1
    cnt = 0
    cnt_max = 10**9

    # g(x) = x - sgn * func(x); x_{i+1} = g(x_{i})
    try:
        if newton:
            g = lambda x: x - (1 / derivative(func, x, 10**(-9))) * func(x)
        elif sor:
            g = lambda x: x - (1 / derivative(func, a, 10 ** (-9))) * func(x) * 2
        else:
            g = lambda x: x - (1 / derivative(func, a, 10 ** (-9))) * func(x)
    except OverflowError:
        return "Method doesn't converge (overflow error)"

    x_curr = g(a)

    try:
        while abs(x_curr - g(x_curr)) > epsilon and cnt < cnt_max:
            x_curr = g(x_curr)
            cnt += 1
            # print(x_curr)
    except OverflowError:
        return "Method doesn't converge (overflow error)"

    if cnt >= cnt_max:
        return "Method doesn't converge"

    return f"\nSolution: {x_curr}\nIterations: {cnt}"


# bisections
# print(bisections(lambda x: x**3 - 8, -10, 53, epsilon=10 ** (-9)))

# fixed point iteration
print(fixed_point_iteration(lambda x: x**3 - 8 + math.sin(x), 50, epsilon=10**(-9)))

# newton method
print(fixed_point_iteration(lambda x: x**3 - 8 + math.sin(x), 50, epsilon=10**(-9), newton=True))

# sor
print(fixed_point_iteration(lambda x: x**3 - 8 + math.sin(x), 50, epsilon=10**(-9), sor=True))
