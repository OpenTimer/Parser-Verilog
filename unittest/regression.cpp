#include <iostream>
#include <iomanip>
#include <chrono>

#include "verilog_driver.hpp"


// A custom parser struct 
struct VerilogParser : public verilog::ParserVerilogInterface {
  virtual ~VerilogParser(){}

  void add_module(std::string&& name){}
  void add_port(verilog::Port&& port) {}  
  void add_net(verilog::Net&& net) {}  
  void add_assignment(verilog::Assignment&& ast) {}  
  void add_instance(verilog::Instance&& inst) { } 
};


int main(const int argc, const char **argv){
  std::cout << std::setw(10) << ' '
            << std::setw(20) << "[Benchmark]"
            << std::setw(13) << "[Runtime]" << '\n';
  std::cout << std::string(45, '-') << '\n';

  for(const auto&p : std::filesystem::directory_iterator("../benchmark/")){

    std::cout << std::setw(10) << "Parsing " 
              << std::setw(20) << p.path().filename().string() ;

    VerilogParser parser;
    auto t1 = std::chrono::high_resolution_clock::now();
    parser.read(p);
    auto t2 = std::chrono::high_resolution_clock::now();

    std::cout << std::setw(13) 
              << std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count()/1000.0f << "ms\n";
  }

  return( EXIT_SUCCESS );
}
