# pico-sha-test
Test program to create and verify numerous SHA-1 hashes on a Raspberry Pi Pico

## Cloning the project.

Checkout the project using the following command:

    git clone --recurse-submodules https://github.com/darranl/pico-sha-test.git

## Building the project.

This assmumes you have already set up a working environment based on the [Getting Started with Pico](https://datasheets.raspberrypi.com/pico/getting-started-with-pico.pdf) documentation at [raspberrypi.com](https://www.raspberrypi.com).

    cd pico-sha-test
    mkdir build
    cd build
    cmake ..
    make -j4

After this there will be two binaries which can be installed depending on your installation mechanism `pico-sha-test.elf` or `pico-sha-test.uf2`.

Once installed the test program runs immidiately and outputs the results to `stdio`.

e.g.

    Begin SHA-1 Testing                               
                                                               
    +-------+--------+-------------+-----------------+
    | Test  | Length | Pass / Fail | Syst Tick Count |
    +-------+--------+-------------+-----------------+
    |     0 |      0 |        Pass |           16644 |
    |     1 |      8 |        Pass |           10690 |
    |     2 |     16 |        Pass |           10037 |
    |     3 |     24 |        Pass |           10040 |

