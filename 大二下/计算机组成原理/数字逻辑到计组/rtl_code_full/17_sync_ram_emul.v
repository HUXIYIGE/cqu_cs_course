module sync_ram_emul(
    input         clk,
    input         en,       //access enable, HIGH valid
    input  [ 3:0] wen,      //write enable by byte, HIGH valid
    input  [ 9:0] addr,
    input  [31:0] wdata,
    output [31:0] rdata
);

reg  [31:0] bit_array [1023:0];

reg         en_r;
reg  [ 3:0] wen_r;
reg  [ 9:0] addr_r;
reg  [31:0] wdata_r;
wire [31:0] rd_out;

// inputs latch
always @(posedge clk) begin
    en_r <= en;
    if (en) begin
        wen_r   <= wen;
        addr_r  <= addr;
        wdata_r <= wdata;
    end
end

// bit array write
always @(posedge clk) begin
    if (en_r) begin
        if (wen_r[0]) bit_array[addr_r][ 7: 0] <= wdata_r[ 7: 0];
        if (wen_r[1]) bit_array[addr_r][15: 8] <= wdata_r[15: 8];
        if (wen_r[2]) bit_array[addr_r][23:16] <= wdata_r[23:16];
        if (wen_r[3]) bit_array[addr_r][31:24] <= wdata_r[31:24];
    end
end

// bit array read
assign rd_out = bit_array[addr_r];

// final output
assign rdata = rd_out;

endmodule

