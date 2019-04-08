syms T(x) a b

    s = input('Ingrese la ecuación: ') k = sym(s);

eq = diff(k * diff(T, x), x) == 0;

dsolve(eq, 'x')