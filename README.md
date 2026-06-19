# linalg

A small linear algebra library in C. It has two halves:

- **General numeric core** — a dynamic, heap-allocated `Mat` type (NxM, `double`)
  with arithmetic, transpose, multiply, and decompositions (LU, determinant,
  solve, inverse, QR).
- **Graphics core** — fixed-size `Vec2/3/4`, `Mat4`, and quaternions with the
  transforms used for rendering (translate/scale/rotate, perspective, look-at).

It builds as a **shared library** so it can be linked by the C visualizer
([linalg-viz]) and loaded from Python via ctypes ([linalg-py]).

## Layout

```
include/linalg/   public headers (matrix, vector, decomp, gfx + umbrella)
src/              implementations
tests/            dependency-free unit tests (the spec / build target)
```

## Build & test

Requires CMake and a C compiler (GCC/MinGW or MSVC).

```sh
cmake -S . -B build -G "MinGW Makefiles"   # omit -G to use the default
cmake --build build
ctest --test-dir build --output-on-failure
```

The compiled library lands in `build/bin/`.

## Status

The function bodies start as stubs (search for `TODO`); the tests define the
expected behavior. Implement until `ctest` is green.

[linalg-viz]: https://github.com/kizdude/linalg-viz
[linalg-py]: https://github.com/kizdude/linalg-py
