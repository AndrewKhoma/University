from copy import copy
from itertools import product

from boltons.setutils import IndexedSet
from sympy import expand, lcm, LT, reduced, latex
from sympy.parsing.sympy_parser import parse_expr


def spoly(p, q):
    return expand(lcm(LT(p), LT(q)) * (1 / LT(p) * p - 1 / LT(q) * q))


def GroebnerBasis(F):
    G = copy(F)
    C = IndexedSet(product(G, G))

    step = 1
    while C:
        f, g = C.pop(0)
        spoly_f_g = spoly(f, g)
        _, h = reduced(spoly_f_g, G)

        if h != 0:
            C.update(product(G, [h]))
            G.append(h)

            print("Step " + str(step))
            print("S-polynomial: {}.\nLaTeX format: {}".format(spoly_f_g, latex(spoly_f_g)))
            print("Polynomial system: {}.\nLaTeX format: {}".format(G, latex(G)))

            step += 1

    non_reduced = copy(G)

    # Reduced Groebner basis
    for i, g in enumerate(G):
        _, G[i] = reduced(g, G[:i] + G[i + 1:])
        if G[i] == 0:
            G.remove(G[i])

    return non_reduced, G


if __name__ == '__main__':
    F = []
    with open("input.txt") as f:
        for line in f.readlines():
            F.append(parse_expr(line, evaluate=False))
    print("initial system", latex(F))

    groebner_basis, reduced_groebner_basis = GroebnerBasis(F)
    print("Groebner basis(", groebner_basis, ")")
    print("Reduced groebner basis(", reduced_groebner_basis, ")")

    print("LaTeX output")
    print(latex(groebner_basis))
    print(latex(reduced_groebner_basis))
