module shifter_left_logic(
    input  [31:0] in,
    input  [ 4:0] sa,   //shift amount
    output [31:0] out
);

assign out = in << sa;

endmodule

