#include <iostream>

#include "verilog_driver.hpp"

// A custom parser struct 
struct SampleParser : public verilog::ParserVerilogInterface {
  virtual ~SampleParser(){}

  void add_module(std::string&& name){
    std::cout << "Module name = " << name << '\n';
  }

  void add_port(verilog::Port&& port) {
    std::cout << "Port: " << port << '\n';
    ports.push_back(std::move(port));
  }  

  void add_net(verilog::Net&& net) {
    std::cout << "Net: " << net << '\n';
    nets.push_back(std::move(net));
  }  

  void add_assignment(verilog::Assignment&& ast) {
    std::cout << "Assignment: " << ast << '\n';
    assignments.push_back(std::move(ast));
  }  

  void add_instance(verilog::Instance&& inst) {
    std::cout << "Instance: " << inst << '\n';
    insts.push_back(std::move(inst));
  }
  
  std::vector<verilog::Port> ports;
  std::vector<verilog::Net> nets;
  std::vector<verilog::Assignment> assignments;
  std::vector<verilog::Instance> insts;
};


int main(const int argc, const char **argv){
  if(argc < 2) {
    std::cerr << "Usage: ./sample_parser verilog_file\n";
    return EXIT_FAILURE;
  }
  
  if(std::filesystem::exists(argv[1])) { 
    SampleParser parser;
    parser.read(argv[1]);
  }
  return EXIT_SUCCESS;
}
