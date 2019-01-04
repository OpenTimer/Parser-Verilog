#include <iostream>

#include "verilog_driver.hpp" 

// Struct: Gate
struct Gate {
  std::string name;
  std::string cell;
  std::unordered_map<std::string, std::string> cellpin2net;
  std::unordered_map<std::string, std::string> net2cellpin;
};

// Struct: Module
struct Module {
  std::string name;
  std::vector<std::string> ports;
  std::vector<std::string> wires;
  std::vector<std::string> inputs;
  std::vector<std::string> outputs;
  std::vector<Gate> gates;
};


// A verilog parser compatible with OpenTimer
struct OpenTimerParser : public verilog::ParserVerilogInterface {
  OpenTimerParser() = default;
  virtual ~OpenTimerParser(){}

  void add_module(std::string&& name){ module.name = std::move(name); }

  void add_port(verilog::Port&& port) {
    if(port.dir == verilog::PortDirection::INPUT) {
      module.inputs.insert(module.inputs.end(), port.names.begin(), port.names.end());
    }
    else if(port.dir == verilog::PortDirection::OUTPUT) {
      module.outputs.insert(module.outputs.end(), port.names.begin(), port.names.end());
    }
    else{
      module.inputs.insert(module.inputs.end(), port.names.begin(), port.names.end());
      module.outputs.insert(module.outputs.end(), port.names.begin(), port.names.end());
    }
    std::move(port.names.begin(), port.names.end(), std::back_inserter(module.ports));
  }

  void add_net(verilog::Net&& net) {
    if(net.type == verilog::NetType::WIRE){
      std::move(net.names.begin(), net.names.end(), std::back_inserter(module.wires));
    }
  }

  void add_assignment(verilog::Assignment&& ast) { 
    // Skip assignment
  }

  void add_instance(verilog::Instance&& inst) {
    auto &g = module.gates.emplace_back();
    g.name = inst.module_name;
    g.cell = inst.inst_name;

    std::string pin; 
    std::string net;
    for(size_t i=0; i<inst.net_names.size(); i++) {
      auto &net_name = inst.net_names[i][0];

      if(i < inst.net_names.size()) {
        auto &pin_name = inst.pin_names[i];
        switch(pin_name.index()) {
          case 0: pin = std::get<0>(pin_name); break;
          case 1: pin = std::get<1>(pin_name).name; break;
          case 2: pin = std::get<2>(pin_name).name; break;
        }

        switch(net_name.index()) {
          case 0: net = std::get<0>(net_name); break;
          case 1: net = std::get<1>(net_name).name; break;
          case 2: net = std::get<2>(net_name).name; break;
          case 3: net = std::get<3>(net_name).value; break;
        }

        g.cellpin2net.insert({pin, net});
        g.net2cellpin.insert({std::move(net), std::move(pin)});
      }
    }
  }

  Module module;
};



int main(const int argc, const char **argv){
  if(argc < 2) {
    std::cerr << "Usage: ./sample_parser verilog_file\n";
    return EXIT_FAILURE;
  }
  
  if(std::experimental::filesystem::exists(argv[1])) { 
    OpenTimerParser parser;
    parser.read(argv[1]);
  }
  return EXIT_SUCCESS;
}
