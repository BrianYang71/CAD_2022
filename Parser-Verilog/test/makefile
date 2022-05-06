VERILOG = iverilog
TARGET = test.vcd

$(TARGET) : test.vvp
	vvp test.vvp

simple.vvp: test_tb.v test.v
	$(VERILOG) -o test.vvp test_tb.v test.v

clean:
	rm $(TARGET)