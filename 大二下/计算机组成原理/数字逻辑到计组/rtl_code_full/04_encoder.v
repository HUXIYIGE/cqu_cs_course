module encoder_8_3(
    input  [7:0] in,
    output [2:0] out
);

assign out = in[0] ? 3’d0 :
             in[1] ? 3’d1 :
             in[2] ? 3’d2 :
             in[3] ? 3’d3 :
             in[4] ? 3’d4 :
             in[5] ? 3’d5 :
             in[6] ? 3’d6 :
                     3’d7 ;

endmodule



module encoder_8_3(
    input  [7:0] in,
    output [2:0] out
);

assign out = ({3{in[0]}} & 3’d0)
           | ({3{in[1]}} & 3’d1)
           | ({3{in[2]}} & 3’d2)
           | ({3{in[3]}} & 3’d3)
           | ({3{in[4]}} & 3’d4)
           | ({3{in[5]}} & 3’d5)
           | ({3{in[6]}} & 3’d6)
           | ({3{in[7]}} & 3’d7);

endmodule

