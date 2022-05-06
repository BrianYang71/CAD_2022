module tb_carry_ripple_adder ();
reg [2:0] t_a , t_b;
reg t_op;
wire [3:0] t_out;
integer seed;
integer i;
carry_ripple_adder DUT(.a(t_a),.b(t_b), .out(t_out));
initial begin
t_a = 0;
t_b = 0 ;
t_op = 0 ;
seed = 10;
for(i =0; i <20; i =i+1) begin
t_a = $random(seed) % 8;
t_b = $random(seed) % 8;
t_op = $random(seed) % 2;
# 10;
end

t_a = 3'd7;
t_b =  3'd7;
#10;
$finish;
end

initial
$monitor("a=%d, b=%d, out=%d, time=%d",t_a ,t_b ,t_out ,$time);
endmodule