verilog_lexer.yy.cc: parser-verilog/verilog_lexer.l
	flex -o./verilog_lexer.yy.cc parser-verilog/verilog_lexer.l 
verilog_parser.tab.cc: 
	bison -d -o verilog_parser.tab.cc parser-verilog/verilog_parser.yy
sample_parser: parser-verilog/ verilog_parser.tab.cc verilog_lexer.yy.cc example/sample_parser.cpp
	g++ -std=c++17 -I parser-verilog/ verilog_parser.tab.cc verilog_lexer.yy.cc example/sample_parser.cpp -o sample_parser -lstdc++fs
