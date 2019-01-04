# Parser-Verilog 

A Fast C++ Header-only Parser for Verilog.

# Get Started with Parser-Verilog 

A Verilog [Verilog] is a programming language that is used to describe a 
digital circuit.

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

// Start wires
wire w1;
wire w2;
wire w3;
wire w4;


// Start cells
AND2_X1 g1 ( .a(input1), .b(input2), .o(w1) );
OR2_X1 g2 (.a(input3), .b(w1), .o(w2));
INV_X2 u3 ( .a(w2), .o(w3) );
NOR2_X1 u4 ( .a(w1), .b(w3), .o(out) );

endmodule
```


***
[Verilog]:            https://en.wikipedia.org/wiki/Verilog
