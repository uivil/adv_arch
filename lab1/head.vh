`define NUM 10
`define WIDTH 10

//**********
module multiplier #(parameter WIDTH = `WIDTH, NUM = `NUM)
(
  input [WIDTH-1:0] i,
  input [WIDTH-1:0] w,
  output [WIDTH-1:0] res
);
  assign res = i * w;
endmodule

//**********
module adder #(parameter WIDTH = `WIDTH, NUM = `NUM)
(
  input [WIDTH-1:0] a,
  input [WIDTH-1:0] b,
  output [WIDTH-1:0] res
);
  assign res = a + b;
endmodule


//**********
module func #(parameter WIDTH = `WIDTH, NUM = `NUM)
(
  input [WIDTH-1:0] a,
  output [WIDTH-1:0] res
);
  assign res = {a[WIDTH-1], {WIDTH-1{1'b0}}};
endmodule

//**********
module lab1 #(parameter WIDTH = `WIDTH, NUM = `NUM)
(
  input [WIDTH-1:0] inputs [0:NUM-1],
  input [WIDTH-1:0] weights [0:NUM-1],

  output [WIDTH-1:0] out
);

wire [WIDTH-1:0] mres [0:NUM-1];
wire [WIDTH-1:0] ares;

// I*W
generate
genvar i;
  for (i=0; i<NUM; i=i+1) begin : gen_muls
    multiplier m(.i(inputs[i]), .w(weights[i]), .res(mres[i]));
  end
endgenerate

// S = S + I*W
 
