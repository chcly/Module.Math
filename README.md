# Math

Utility math library.

## Testing

The Test directory is setup to work with [googletest](https://github.com/google/googletest).

## Building

![A1](https://github.com/chcly/Module.Math/actions/workflows/build-linux.yml/badge.svg)
![A2](https://github.com/chcly/Module.Math/actions/workflows/build-windows.yml/badge.svg)

```sh
mkdir build
cd build
cmake .. -DMath_BUILD_TEST=ON -DMath_AUTO_RUN_TEST=ON
make
```

### Optional defines

| Option                  | Description                                          | Default |
| :---------------------- | :--------------------------------------------------- | :-----: |
| Math_BUILD_TEST         | Build the unit test program.                         |   ON    |
| Math_AUTO_RUN_TEST      | Automatically run the test program.                  |   OFF   |
| Math_USE_STATIC_RUNTIME | Build with the MultiThreaded(Debug) runtime library. |   ON    |

