module Full_Adder( A, B, Cin, Sum, Cout );

    input A, B, Cin;
    output Sum, Cout;

    wire W1, W2, W3;

    xor xor1( W1, A, B );
    and and1( W2, W1, Cin );
    and and2( W3, A, B );
    xor xor2( Sum, W1, Cin );
    or  or1( Cout, W2, W3 );

endmodule
