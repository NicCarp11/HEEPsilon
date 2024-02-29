<p align="left"><img src="docs/HEEPsilon_logo.png" width="500"></p>

HEEPsilon is a versatile computing platform targeting ultra low power processing of biological and environmental signals. It is built over the [X-HEEP](https://github.com/esl-epfl/x-heep) platform and extends it with [openEdgeCGRA](https://github.com/esl-epfl/OpenEdgeCGRA) a design-time resizable and run-time reprogrammable Coarse Grained Reconfigurable Array (CGRA).
For a brief insight on HEEPsilon please refer to our abstract:

📄 [An Open-Hardware Coarse-Grained Reconfigurable Array for Edge Computing](https://dl.acm.org/doi/10.1145/3587135.3591437).

As an X-HEEP spinoff, HEEPsilon keeps all X-HEEP functionalities, from RTL simulation on Verilator, VCS and Questasim to implementation on the [PYNQ-Z2 FPGA](https://www.xilinx.com/support/university/xup-boards/XUPPYNQ-Z2.html).

---

# Getting started

Due to its modular design, HEEPsilon respects the X-HEEP workflow. As such, you can follow [X-HEEP's getting started](https://x-heep.readthedocs.io/en/latest/How_to/GettingStarted.html) to set up the environment.

# Behavioural simulations

The CGRA used in HEEPsilon can be simulated with CGRA-instruction accuracy using the [ESL-CGRA simulator](https://github.com/esl-epfl/ESL-CGRA-simulator).
This allows for fast and easy-to-debug design of kernels for the CGRA. Once you are happy with your design you can compile the assembly and get the bitstream to load into the CGRA.

# Preparing set-up for kernel with weight parallelism
This section quickly describes the content of this repository, so that you may be able to test the convolutional kernel implemented with weight parallelism.

```
.
├── .github
├── docs
├── hw
├── script
├── sw
│   ├── applications
│   │   ├── kernel_test
│   │   │   ├── kernels
│   │   │   │   ├── conv
│   │   │   │   │   └── render-c.py
│   ├── external
├── tb
├── util
├── Makefile
├── README.md
├── cgra_x_heep.core
└── script.sh
```
For this kind of activity, we are going to test the initial kernel configuration: I<sub>x</sub>=I<sub>y</sub>=16, F<sub>x</sub>=F<sub>y</sub>=3, C=K=16. In this particularly case, you just need to run the `script.sh`, since it is configured to prepare both the assembly instructions and firmaware for this kind of application.

# Modifying hyper-parameter 
In case you want to change hyper-parameter, you can easily modify them, by accessing to `render-c.py`. This file is formatted in this way:
```
input_dim = 16
filter_dimension = 3
input_channel = 16
output_channel = 16

data = {
    'input_dim': input_dim,
    'output_row': input_dim-filter_dimension+1,
    'output_col': input_dim-filter_dimension+1,
    'input_channel': input_channel,
    'output_channel': output_channel,
}
```
By changing these intial lines, and run again `script.sh`, automatically you have both the assmebly instructions and firmware code updated.

# Compiling with Makefile
As previously, in order to compile and try either a simulation on Verilator or an implementation on the [PYNQ-Z2 FPGA], you can follow [X-HEEP's compiling with Makefile](https://x-heep.readthedocs.io/en/latest/How_to/CompileMakefile.html)

When generating core-v-mini-mcu package for an implementation on the PYNQ-Z2, we highly suggest this kind of configuration:

```
make mcu-gen MEMORY_BANKS=5
```
This number is the result of exploration between different memory banks, and is the one used for this project.

In order to either simulate on Verilator or implement on PYNQ we remind you to you to add the option `PROJECT=kernel_test` to their corresponding scripts.





