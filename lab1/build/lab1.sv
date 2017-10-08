`define NUM 13
`define WIDTH 13

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
module adder #(parameter start = 0, stop = 16, WIDTH = 16)(
  input [WIDTH-1:0] in [start:stop],
  output [WIDTH-1:0] out
);
localparam dst = stop - start;
generate
if (dst == 1) begin
  assign out = in[start] + in[stop];
end
else if (dst == 2) begin
  assign out = in[start] + in[stop] + in[start+1];
end else begin
	wire [WIDTH-1:0] out1;
	wire [WIDTH-1:0] out2;
	localparam middle = dst >> 1;
	adder #(.start(start), .stop(start+middle), .WIDTH(WIDTH)) x (.in(in[start:start+middle]), .out(out1));
   adder #(.start(start+middle+1), .stop(stop), .WIDTH(WIDTH)) y (.in(in[start+middle+1:stop]), .out(out2));
	assign out = out1 + out2;
end
endgenerate
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
module neuron #(parameter WIDTH = `WIDTH, NUM = `NUM)
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
  for (i=0; i<NUM; i=i+1) begin : mulgen
    multiplier m(.i(inputs[i]), .w(weights[i]), .res(mres[i]));
  end
endgenerate

// S = S + I*W
//
//
//

adder #(.start(0), .stop(NUM-1), .WIDTH(WIDTH)) a(.in(mres), .out(ares));


func f(.a(ares), .res(out));


endmodule


module lab1(output a);

reg [`WIDTH-1:0] inputs   [0:`NUM-1];
reg [`WIDTH-1:0] weights  [0:`NUM-1];

wire [`WIDTH-1:0] out;


neuron #(.WIDTH(`WIDTH), .NUM(`NUM)) n (.inputs(inputs), 
                                        .weights(weights), 
                                        .out(out));

assign a = out[0];
endmodule



