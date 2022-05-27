module shifter_right_arith(
    input  [31:0] in,
    input  [ 4:0] sa,   //shift amount
    output [31:0] out
);

wire [63:0] sr64_res;

assign sr64_res = {{32{in[31]}}, in[31:0]} >> sa;

assign out = sr64_res[31:0];

endmodule

