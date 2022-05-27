


module Dflipflop(
    input      clk,
    input      din,
    output reg q
);

always @(posedge clk) begin
    q <= din;
end

endmodule
