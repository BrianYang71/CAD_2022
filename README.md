# This is README file for EDA final project (CAD Contest Problem A)

Author: \
B09901175 Yang, Bo Yu \
B09901192 Lin, Pei Han\
B09901040 Ko, Chun Yi 

Date: 2022/6/24

---
## SYNOPSIS

This program supports rewriting the circuit written in verilog from a **gate-level form** to a simplified arithmetic **dataflow form**.\
We provide two ways to implement:

### Method 1

    ./demo <input_file_name> <output_file_name>

**It meets the form of the contest**. \
However, because of some trivial technical problems, we can't access to our commands added in `abc/src/ext-cad` when executing our demo. \
At this time, we merely output the verilog file `write_out.v` with one input file `release/test01/top_primitive.v`

========
### Method 2
Run our algorithm in the environment of `abc`.

---
## Directory
|  dir   |  description  |
| :------:  | :------: |
|  abc   |  abc package  |
|  release   |  input files  |
|  tool  |  executable binary |

---
## HOW TO COMPILE

To compile ABC as a binary,

* `cd abc/`
* `make`

---
## HOW TO RUN

### Method 1 
    ./demo ./release/test01/top_primitive.v write_out.v

 Output file `write_out.v` will be the simplified verilog rewriting from `release/test01/top_primitive.v`.

 Notice that file `out_.v` is a transition file generated during the process. **It can be ignored**. 

========
### Method 2
The process is separated into 3 steps.

Step 1. \
Convert the input file (gate-level verilog) to **abc readable input file** (dataflow verilog)

    ./tool/convert <input_file_name> \
For example,

    ./tool/convert ./release/test01/top_primitive.v
It will generate a file named `out_.v`

Step 2. \
Run our algorithm in the environment of abc

    [...] ~/> cd abc/
 After compiling ABC as a binary.

    [...] ~/abc> ./abc
    UC Berkeley, ABC 1.01 (compiled Jun 23 2022 00:32:58)
    abc 01> r ../out_.v; alg2
 It will print the final result in the terminal. \
 For example, 

    out1=in1+in2+in3
Back to the base directory

    abc 04> q
    [...] ~/abc> cd ..
 
 Step 3.\
 Write the `write_out.v` verilog \
 copy the result printed in the terminal and paste it in the **fourth argument** of the terminal

    ./tool/write out_.v write_out.v <formula printed in the terminal>
For exmaple,

    ./tool/write out_.v write_out.v "out1=in1+in2+in3"
Then, `write_out.v` is the final output verilog.

---

## OTHER NOTICE
Currently, we can only rewrite test case 1 and 2. \
Please access to only these two input files
