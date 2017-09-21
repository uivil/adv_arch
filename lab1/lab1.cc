#include <iostream>
#include <sstream>
#include <stack>

void gen_adder(std::pair<int, int> a, std::pair<int, int> b, 
    std::pair<int, int> res, std::ostringstream& os)
{
  os << "adder #(.WIDTH(WIDTH), .NUM(NUM)) x" << a.first << "_" 
    << a.second << "\n(\n.a(t" << a.first << "_" << a.second << "),\n.b(t" 
    << b.first << "_" << b.second << "),\n.res(t" << res.first 
    << "_" << res.second << ")\n);\n";
}

void gen_wire(std::pair<int, int> a, std::ostringstream& os)
{
    os << "wire [WIDTH-1:0] t" << a.first << "_" << a.second <<";\n"; 
}



void gen(int n, int level, int carry, std::stack<std::pair<int, int>>& st, 
    std::ostringstream& os)
{
  auto nodes = n + carry;

  if (nodes == 1) {
    os << "assign ares = t" << n << "_" << level << ";\n"; 
    return;
  }

  auto len = (!!(n & 1) && n > 1) ? n - 1 : n;
  
  if ((n & 1) && !carry) st.push({n, level});
  
  for (auto i = 0; i < len && len > 1; i += 2) {
    if (level == 1) {
      gen_wire({i+1, level}, os);
      gen_wire({i+2, level}, os);
    }
    // wires & modules for next layer
    gen_wire({i/2+1, level+1}, os);
    gen_adder({i+1, level}, {i+2, level}, {i/2+1, level+1}, os);
  }

  if ((n & 1) && carry && !st.empty()) {
    auto tmp = st.top();
    gen_wire({n/2+1, level+1}, os);
    gen_adder({n, level}, tmp, {n/2+1, level+1}, os);
    st.pop();
  }

  if (nodes & 1)
    gen(nodes/2, level + 1, 1, st, os);
  else 
    gen(nodes/2, level + 1, 0, st, os);

}


std::string gen(int n, int level, int carry)
{
  std::stack<std::pair<int, int>> st;
  std::ostringstream os;
  gen(n, 1, 0, st, os);
  
  return os.str();
}

int main(int argv, char **argc)
{
  std::string head = R"(`define NUM 10
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
  for (i=0; i<NUM; i=i+1)
    multiplier m(.i(inputs[i]), .w(weights[i]), .res(mres[i]));
endgenerate

// S = S + I*W)";
  
  std::string tail("func f(.a(ares), .res(out)); \nendmodule");

  const int n = 20;
  const int carry = 0;
  const int level = 1;

  std::cout << head << "\n";
  std::cout << gen(n, level, carry);
  std::cout << tail;

  return 0;
}
