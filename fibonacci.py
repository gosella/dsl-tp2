from copy import copy

def power(x, n, op, z):
    if n == 0:
        return copy(z)

    while (n & 1) == 0:
        n >>= 1
        x = op(x, x)

    result = copy(x)
    n >>= 1
    while n != 0:
        x = op(x, x)
        if (n & 1) != 0:
            result = op(result, x)
        n >>= 1

    return result


def multiply_2x2(x, y):
    return [ x[0] * y[0] + x[1] * y[2], x[0] * y[1] + x[1] * y[3],
             x[2] * y[0] + x[3] * y[2], x[2] * y[1] + x[3] * y[3] ]


def fibonacci(n):
    if n == 0:
        return 0

    return power([1, 1, 1, 0], n-1, multiply_2x2, [1, 0, 0, 1])[0]


def slow_fibonacci(n):
    current = 0
    next = 1

    while n > 0:
        current, next = next, current + next
        n -= 1

    return current


def worst_fibonacci_ever(n):
    if n == 0:
        return 0
    if n <= 2:
        return 1
    return worst_fibonacci_ever(n-1) + worst_fibonacci_ever(n-2)
