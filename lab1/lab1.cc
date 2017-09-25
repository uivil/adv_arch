#include <iostream>
#include <sstream>
#include <fstream>
#include <stack>

void gen_adder(const std::pair<int, int>& a, const std::pair<int, int>& b, 
    const std::pair<int, int>& res, std::ostringstream& os)
{
  os << "adder #(.WIDTH(WIDTH), .NUM(NUM)) x" << a.first << "_" 
    << a.second << "\n(\n.a(t" << a.first << "_" << a.second << "),\n.b(t" 
    << b.first << "_" << b.second << "),\n.res(t" << res.first 
    << "_" << res.second << ")\n);\n";
}

void gen_wire(const std::pair<int, int>& a, std::ostringstream& os)
{
  os << "wire [WIDTH-1:0] t" << a.first << "_" << a.second; 
  if (a.second == 1)
    os << " = mres[" << a.first-1 <<"]";

  os << ";\n";
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
  if (argv < 2) exit(1);
  
  const int n = std::atoi(argc[1]);
  const int level = 1;
  const int carry = 0;
  
  std::ifstream h("head.vh");
  std::stringstream head;
  head << h.rdbuf();

  std::ifstream t("tail.vh");
  std::stringstream tail;
  tail << t.rdbuf();
  
  std::cout << head.str() << std::endl;
  std::cout << gen(n, level, carry) << std::endl;
  std::cout << tail.str() << std::endl;

  return 0;
}
