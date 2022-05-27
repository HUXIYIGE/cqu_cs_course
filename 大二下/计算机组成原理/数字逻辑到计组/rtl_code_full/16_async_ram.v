module async_ram(
    input         clk,
    input         en,   //access enable, HIGH valid
    input  [ 3:0] wen,  //write enable by byte, HIGH valid
    input  [ 9:0] addr,
    input  [31:0] wdata,
    output [31:0] rdata
);

reg  [31:0] bit_array [1023:0];
wire [31:0] rd_out;

// bit array write
always @(posedge clk) begin
    if (en) begin
        if (wen[0]) bit_array[addr][ 7: 0] <= wdata[ 7: 0];
        if (wen[1]) bit_array[addr][15: 8] <= wdata[15: 8];
        if (wen[2]) bit_array[addr][23:16] <= wdata[23:16];
        if (wen[3]) bit_array[addr][31:24] <= wdata[31:24];
    end
end

// bit array read
assign rd_out = bit_array[addr];

// final output
assign rdata = rd_out;

endmodule
