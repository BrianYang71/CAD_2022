module top(in1, in2, in3, out1);
  input [3:0] in1, in2, in3;
  output [3:0] out1;
  assign out1 = in1 + in2 + in3;
endmodule
