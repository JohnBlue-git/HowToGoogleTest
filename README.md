# How to GoogleTest

A small, progressive C and C++ project for learning GoogleTest (and GoogleMock)
with CMake. Each example is a real library with a test target, so you can change
the implementation and see the tests catch regressions.

## Requirements

- CMake 3.20 or newer
- A C11 and C++17 compiler
- Git and an internet connection the first time you configure (CMake downloads
  GoogleTest 1.15.2 with `FetchContent`)

GoogleTest is a C++ framework. The C example keeps its implementation in C and
uses a small C++ test runner to call its C API.

## Build and run

From the project root:

```sh
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

Run a single test executable directly for GoogleTest's filtering and output:

```sh
./build/c_demo/c_demo_tests
./build/cpp_demo/cpp_demo_tests --gtest_filter=TemperatureMonitorTest.*
```

For example, `--gtest_filter=CppBasicsTest.*` runs only the basic C++ examples.
To start over with a clean build, remove the generated `build/` directory.

## How the tests exercise the source

```mermaid
flowchart TD
    CMake["CMake configure<br/>FetchContent downloads GoogleTest / GoogleMock"]
    Build["cmake --build build"]
    CTest["ctest"]

    subgraph CExample["C example"]
        CSource["calculator.c<br/>(C implementation)"] --> CLib["c_calculator library"]
        CTests["calculator_test.cpp<br/>(C++ GoogleTest cases)"] --> CRunner["c_demo_tests"]
        CLib --> CRunner
    end

    subgraph CppExample["C++ example"]
        CppSource["temperature_monitor.cpp<br/>(C++ implementation)"] --> CppLib["temperature_monitor library"]
        CppTests["basics_test.cpp<br/>private_member_test.cpp<br/>temperature_monitor_test.cpp"] --> CppRunner["cpp_demo_tests"]
        CppLib --> CppRunner
        Mock["MockTemperatureObserver<br/>(GoogleMock)"] --> CppTests
    end

    GTest["GoogleTest / GoogleMock libraries"]
    CMake --> Build
    Build --> CLib
    Build --> CRunner
    Build --> CppLib
    Build --> CppRunner
    GTest --> CRunner
    GTest --> CppRunner
    CRunner --> CTest
    CppRunner --> CTest
    CTest --> Results["Test results<br/>(pass / fail)"]
```

The C source is compiled as C and linked into a C++ GoogleTest runner. The C++
tests link the C++ library directly; GoogleMock supplies a test double for the
monitor's observer interface. CTest runs the discovered GoogleTest cases from
both executables and reports the results.

## Learning path

### 1. C API: assertions and error cases

`c_demo/src/calculator.c` contains ordinary C functions. Its C++ test runner
checks successful calculations, division by zero, and invalid arguments in
`c_demo/tests/calculator_test.cpp`. The `extern "C"` guards in the header make
the API usable from both C and C++.

```mermaid
flowchart LR
    Add["calculator_add(2, 3)"] --> AddCheck["EXPECT_EQ: 5"]
    Divide["calculator_divide(12, 3, &result)"] --> DivideCheck["status: OK<br/>result: 4"]
    Zero["calculator_divide(12, 0, &result)"] --> ZeroCheck["status: DIVIDE_BY_ZERO<br/>result unchanged"]
    Null["calculator_divide(12, 3, nullptr)"] --> NullCheck["status: INVALID_ARGUMENT"]
```

### 2. C++: test cases and fixtures

`CppBasicsTest` demonstrates `TEST`. `TemperatureConversionTest` is a
parameterized test fixture that checks known Celsius/Fahrenheit pairs. The
tests exercise observable behavior rather than implementation details.

```mermaid
flowchart LR
    Basic["CppBasicsTest<br/>2 + 3 = 5<br/>5 > 0"] --> BasicCheck["EXPECT_EQ / EXPECT_TRUE"]
    Inputs["Parameterized Celsius values<br/>-40, 0, 20, 100"] --> Convert["celsiusToFahrenheit"]
    Convert --> Expected["Expected values<br/>-40, 32, 68, 212"]
    Expected --> ParamCheck["EXPECT_EQ for each pair"]
```

### 3. Private members

`PrivateMemberTest.NormalizeClampsNegativeValues` uses GoogleTest's
`FRIEND_TEST` to access one private helper. This technique couples the test to
the class implementation; prefer testing through the public interface unless
direct access is necessary for a specific reason.

```mermaid
flowchart LR
    Test["PrivateMemberTest<br/>(FRIEND_TEST access)"] --> Private["normalizeForDisplay"]
    Private --> Negative["Input: -5"]
    Private --> Positive["Input: 5"]
    Negative --> NegativeCheck["EXPECT_EQ: 0"]
    Positive --> PositiveCheck["EXPECT_EQ: 5"]
```

### 4. GoogleMock

`TemperatureMonitor` depends on its `Observer` interface.
`MockTemperatureObserver` and `EXPECT_CALL` show how to isolate the monitor
from that dependency, verify interactions, and check that no notification is
sent when the threshold is not reached.

```mermaid
flowchart LR
    Fixture["TemperatureMonitorTest fixture<br/>threshold: 30"] --> Monitor["monitor.record(temperature)"]
    Mock["StrictMock observer"] --> Expect["EXPECT_CALL"]
    Monitor --> At["Input: 30"]
    Monitor --> Below["Input: 29"]
    At --> Notify["Observer notified once"]
    Below --> NoNotify["No notification"]
    Expect --> NotifyCheck["Verify notification"]
    Expect --> NoNotifyCheck["Verify zero calls"]
```

## Project layout

```text
CMakeLists.txt
c_demo/
  include/calculator.h
  src/calculator.c
  tests/calculator_test.cpp
cpp_demo/
  include/temperature_monitor.h
  src/temperature_monitor.cpp
  tests/
    basics_test.cpp
    private_member_test.cpp
    temperature_monitor_test.cpp
```

The root `CMakeLists.txt` fetches GoogleTest and adds both examples. Each
subdirectory defines a library and a test executable, then registers the
individual GoogleTest cases with CTest.
