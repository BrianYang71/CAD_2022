module carry_ripple_adder (a, b,out);
input [2:0] a, b;
output [3:0] out;
wire c1, c2;
FA f1(.a(a[0]),.b(b[0]), .c_in (1'b0),.sum(out[0]), .c_out(c1));
FA f2(.a(a[1]),.b(b[1]), .c_in (c1),.sum(out[1]), .c_out(c2));
FA f3(.a(a[2]),.b(b[2]), .c_in (c2),.sum(out[2]), .c_out(out[3]));
endmodule

module HA(a, b,sum,c_out);

input wire a, b;
output wire sum, c_out;
xor (sum ,a, b);
and(c_out ,a, b);

endmodule

module FA(a, b,c_in , sum, c_out);
input a, b, c_in;
output sum, c_out;
wire w1, w2, w3;
HA M1(.a(a), .b(b), .sum(w1), .c_out(w2));
HA M2(.a(w1), .b(c_in), .sum(sum), .c_out(w3));
or (c_out , w2,w3);
endmodule
