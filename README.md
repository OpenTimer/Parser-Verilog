# Parser-Verilog 

A Fast C++ Header-only Parser for Verilog.

# Get Started with Parser-Verilog 

A [Verilog] is a programming language that is used to describe a 
digital circuit. Below is a circuit written in Verilog.

```Verilog 
module simple (
input1,
input2, 
input3,
out
);

// Primary inputs
input input1;
input input2;
input input3;

wire input1;
wire input2;
wire input3;

// Primary output
output out; 

wire out;

// Wires
wire w1;
wire w2;
wire w3;
wire w4;

// Gates
AND2_X1 g1 (.a(input1), .b(input2), .o(w1));
OR2_X1 g2  (.a(input3), .b(w1), .o(w2));
INV_X2 g3  (.a(w2), .o(w3));
NOR2_X1 g4 (.a(w1), .b(w3), .o(out));

endmodule
```

The following example demonstrates how to use Parser-Verilog to parse a Verilog file.


```cpp
#include <iostream>

#include "verilog_driver.hpp"   // The only include you need

// Define your own parser by inheriting the ParserVerilogInterface
struct MyVerilogParser : public verilog::ParserVerilogInterface {

  virtual ~MyVerilogParser(){}

  // Function that will be called when encountering the top module name.
  void add_module(std::string&& name){
    std::cout << "Module: " << name << '\n';
  }

  // Function that will be called when encountering a port.
  void add_port(verilog::Port&& port) {
    std::cout << "Port: " << port << '\n';
  }  

  // Function that will be called when encountering a net.
  void add_net(verilog::Net&& net) {
    std::cout << "Net: " << net << '\n';
  }  

  // Function that will be called when encountering a assignment statement.
  void add_assignment(verilog::Assignment&& ast) {
    std::cout << "Assignment: " << ast << '\n';
  }  

  // Function that will be called when encountering a gate.
  void add_instance(verilog::Instance&& inst) {
    std::cout << "Instance: " << inst << '\n';
  }
};

int main(){
  MyVerilogParser parser;
  parser.read("verilog_file.v");
  return EXIT_SUCCESS;
}
```

You need a C++ compiler with C++17 support, [GNU Bison] and [Flex] to compile Parser-Verilog.
```bash
~$ flex -o./verilog_lexer.yy.cc parser-verilog/verilog_lexer.l 
~$ bison -d -o verilog_parser.tab.cc parser-verilog/verilog_parser.yy
~$ g++ -std=c++17 -I parser-verilog/ verilog_parser.tab.cc verilog_lexer.yy.cc example/simple_parser.cpp -o simple_parser -lstdc++fs
```

***
[Verilog]:             https://en.wikipedia.org/wiki/Verilog 
[GNU Bison]:           https://www.gnu.org/software/bison/
[Flex]:                https://github.com/westes/flex 

