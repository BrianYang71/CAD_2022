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

	// Function that will be called when encountering a module instance.
	void add_instance(verilog::Instance&& inst) {
		std::cout << "Instance: " << inst << '\n';
	}
};

int main(){
	MyVerilogParser parser;
	parser.read("verilog_file.v");
	return EXIT_SUCCESS;
}
