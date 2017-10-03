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
 

wire [WIDTH-1:0] t1_1 = mres[0];
wire [WIDTH-1:0] t2_1 = mres[1];
wire [WIDTH-1:0] t1_2;
adder #(.WIDTH(WIDTH), .NUM(NUM)) x1_1
(
.a(t1_1),
.b(t2_1),
.res(t1_2)
);
wire [WIDTH-1:0] t3_1 = mres[2];
wire [WIDTH-1:0] t4_1 = mres[3];
wire [WIDTH-1:0] t2_2;
adder #(.WIDTH(WIDTH), .NUM(NUM)) x3_1
(
.a(t3_1),
.b(t4_1),
.res(t2_2)
);
wire [WIDTH-1:0] t5_1 = mres[4];
wire [WIDTH-1:0] t6_1 = mres[5];
wire [WIDTH-1:0] t3_2;
adder #(.WIDTH(WIDTH), .NUM(NUM)) x5_1
(
.a(t5_1),
.b(t6_1),
.res(t3_2)
);
wire [WIDTH-1:0] t7_1 = mres[6];
wire [WIDTH-1:0] t8_1 = mres[7];
wire [WIDTH-1:0] t4_2;
adder #(.WIDTH(WIDTH), .NUM(NUM)) x7_1
(
.a(t7_1),
.b(t8_1),
.res(t4_2)
);
wire [WIDTH-1:0] t9_1 = mres[8];
wire [WIDTH-1:0] t10_1 = mres[9];
wire [WIDTH-1:0] t5_2;
adder #(.WIDTH(WIDTH), .NUM(NUM)) x9_1
(
.a(t9_1),
.b(t10_1),
.res(t5_2)
);
wire [WIDTH-1:0] t1_3;
adder #(.WIDTH(WIDTH), .NUM(NUM)) x1_2
(
.a(t1_2),
.b(t2_2),
.res(t1_3)
);
wire [WIDTH-1:0] t2_3;
adder #(.WIDTH(WIDTH), .NUM(NUM)) x3_2
(
.a(t3_2),
.b(t4_2),
.res(t2_3)
);
wire [WIDTH-1:0] t1_4;
adder #(.WIDTH(WIDTH), .NUM(NUM)) x1_3
(
.a(t1_3),
.b(t2_3),
.res(t1_4)
);
wire [WIDTH-1:0] t1_5;
adder #(.WIDTH(WIDTH), .NUM(NUM)) x1_4
(
.a(t1_4),
.b(t5_2),
.res(t1_5)
);
assign ares = t1_5;

func f(.a(ares), .res(out)); 
endmodule

