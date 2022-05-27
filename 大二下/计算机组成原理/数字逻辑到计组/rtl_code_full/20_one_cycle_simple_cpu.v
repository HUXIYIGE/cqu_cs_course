module one_cycle_simple_cpu(
    input       clk,
    input       resetn
);
reg         reset;
always @(posedge clk) reset <= ~resetn;

wire        inst_sram_en;
wire [ 3:0] inst_sram_wen;
wire [31:0] inst_sram_addr;
wire [31:0] inst_sram_wdata;
wire [31:0] inst_sram_rdata;
wire        data_sram_en;
wire [ 3:0] data_sram_wen;
wire [31:0] data_sram_addr;
wire [31:0] data_sram_wdata;
wire [31:0] data_sram_rdata;

wire [31:0] seq_pc;
wire [31:0] nextpc;
reg  [31:0] pc;
wire [31:0] inst;
wire [ 5:0] op;
wire [ 4:0] rs;
wire [ 4:0] rt;
wire [ 4:0] rd;
wire [ 4:0] sa;
wire [ 5:0] func;
wire [15:0] imm;
wire [25:0] jidx;
wire [63:0] op_d;
wire [31:0] rs_d;
wire [31:0] rt_d;
wire [31:0] rd_d;
wire [31:0] sa_d;
wire [63:0] func_d;
wire        inst_addu;
wire        inst_subu;
wire        inst_slt;
wire        inst_sltu;
wire        inst_and;
wire        inst_or;
wire        inst_xor;
wire        inst_nor;
wire        inst_sll;
wire        inst_srl;
wire        inst_sra;
wire        inst_addiu;
wire        inst_lui;
wire        inst_lw;
wire        inst_sw;
wire        inst_beq;
wire        inst_bne;
wire        inst_jal;
wire        inst_jr;
wire [11:0] alu_op;
wire        src1_is_sa;  
wire        src1_is_pc;
wire        src2_is_imm; 
wire        src2_is_8;
wire        res_from_mem;
wire        dst_is_r31;  
wire        dst_is_rt;   
wire        gr_we;       
wire        mem_we;      
wire [ 4:0] dest;
wire [ 4:0] rf_raddr1;
wire [31:0] rf_rdata1;
wire [ 4:0] rf_raddr2;
wire [31:0] rf_rdata2;
wire [31:0] rs_value;
wire [31:0] rt_value;
wire        rs_eq_rt;
wire        br_taken;
wire [31:0] bd_pc;
wire [31:0] br_target;
reg         bd_taken;
reg  [31:0] bd_target;
wire [31:0] alu_src1;
wire [31:0] alu_src2;
wire [31:0] alu_result;
wire [31:0] mem_result;
wire [31:0] final_result;
wire        rf_we;
wire [ 4:0] rf_waddr;
wire [31:0] rf_wdata;


assign seq_pc = pc + 3'h4;
assign nextpc = bd_taken ? bd_target : seq_pc; 

always @(posedge clk) begin
    if (reset) pc <= 32'hbfc00000;
    else       pc <= nextpc;
end

assign inst_sram_en     = 1'b1;
assign inst_sram_wen    = 4'h0;
assign inst_sram_addr   = pc;
assign inst_sram_wdata  = 32'b0;
async_ram inst_sram(
    .clk    (clk                 ), //I
    .en     (inst_sram_en        ), //I
    .wen    (inst_sram_wen       ), //I
    .addr   (inst_sram_addr[11:2]), //I
    .wdata  (inst_sram_wdata     ), //I
    .rdata  (inst_sram_rdata     )  //O
    );
assign inst = inst_sram_rdata;
    
assign op   = inst[31:26];
assign rs   = inst[25:21];
assign rt   = inst[20:16];
assign rd   = inst[15:11];
assign sa   = inst[10: 6];
assign func = inst[ 5: 0];
assign imm  = inst[15: 0];
assign jidx = inst[25: 0];

decoder_6_64 u_dec0(.in(op  ), .out(op_d  ));
decoder_6_64 u_dec1(.in(func), .out(func_d));
decoder_5_32 u_dec2(.in(rs  ), .out(rs_d  ));
decoder_5_32 u_dec3(.in(rt  ), .out(rt_d  ));
decoder_5_32 u_dec4(.in(rd  ), .out(rd_d  ));
decoder_5_32 u_dec5(.in(sa  ), .out(sa_d  ));

assign inst_addu   = op_d[6'h00] & func_d[6'h21] & sa_d[5'h00];
assign inst_subu   = op_d[6'h00] & func_d[6'h23] & sa_d[5'h00];
assign inst_slt    = op_d[6'h00] & func_d[6'h2a] & sa_d[5'h00];
assign inst_sltu   = op_d[6'h00] & func_d[6'h2b] & sa_d[5'h00];
assign inst_and    = op_d[6'h00] & func_d[6'h24] & sa_d[5'h00];
assign inst_or     = op_d[6'h00] & func_d[6'h25] & sa_d[5'h00];
assign inst_xor    = op_d[6'h00] & func_d[6'h26] & sa_d[5'h00];
assign inst_nor    = op_d[6'h00] & func_d[6'h27] & sa_d[5'h00];
assign inst_sll    = op_d[6'h00] & func_d[6'h00] & rs_d[5'h00];
assign inst_srl    = op_d[6'h00] & func_d[6'h02] & rs_d[5'h00];
assign inst_sra    = op_d[6'h00] & func_d[6'h03] & rs_d[5'h00];
assign inst_addiu  = op_d[6'h09];
assign inst_lui    = op_d[6'h0f] & rs_d[5'h00];
assign inst_lw     = op_d[6'h23];
assign inst_sw     = op_d[6'h2b];
assign inst_beq    = op_d[6'h04];
assign inst_bne    = op_d[6'h05];
assign inst_jal    = op_d[6'h03];
assign inst_jr     = op_d[6'h00] & func_d[6'h08] & rt_d[5'h00] & rd_d[5'h00] & sa_d[5'h00];

assign alu_op[ 0] = inst_addu | inst_addiu | inst_lw | inst_sw | inst_jal;
assign alu_op[ 1] = inst_subu;
assign alu_op[ 2] = inst_slt;
assign alu_op[ 3] = inst_sltu;
assign alu_op[ 4] = inst_and;
assign alu_op[ 5] = inst_nor;
assign alu_op[ 6] = inst_or;
assign alu_op[ 7] = inst_xor;
assign alu_op[ 8] = inst_sll;
assign alu_op[ 9] = inst_srl;
assign alu_op[10] = inst_sra;
assign alu_op[11] = inst_lui;

assign src1_is_sa   = inst_sll   | inst_srl | inst_sra;
assign src1_is_pc   = inst_jal;
assign src2_is_imm  = inst_addiu | inst_lui | inst_lw | inst_sw;
assign src2_is_8    = inst_jal;
assign res_from_mem = inst_lw;
assign dst_is_r31   = inst_jal;
assign dst_is_rt    = inst_addiu | inst_lui | inst_lw;
assign gr_we        = ~inst_sw & ~inst_beq & ~inst_bne & ~inst_jr;
assign mem_we       = inst_sw;

assign dest         = dst_is_r31 ? 5'd31 :
                      dst_is_rt  ? rt    : 
                                   rd;


assign rf_raddr1 = rs;
assign rf_raddr2 = rt;
regfile u_regfile(
    .clk    (clk      ),
    .raddr1 (rf_raddr1),
    .rdata1 (rf_rdata1),
    .raddr2 (rf_raddr2),
    .rdata2 (rf_rdata2),
    .we     (rf_we    ),
    .waddr  (rf_waddr ),
    .wdata  (rf_wdata )
    );
assign rs_value = rf_rdata1;
assign rt_value = rf_rdata2;


assign rs_eq_rt  = (rs_value == rt_value);
assign br_taken  = inst_beq  &&  rs_eq_rt
                || inst_bne  && !rs_eq_rt
                || inst_jal
                || inst_jr;
assign bd_pc     = pc + 3'h4;
assign br_target = (inst_beq || inst_bne) ? (bd_pc + {{14{imm[15]}}, imm[15:0], 2'b0}) :
                   (inst_jr)              ? rs_value :
                  /*inst_jal*/              {bd_pc[31:28], jidx[25:0], 2'b0};

always @(posedge clk) begin
    if (reset) bd_taken <= 1'b0;
    else       bd_taken <= br_taken;

    if (br_taken) bd_target <= br_target;
end

assign alu_src1 = src1_is_sa  ? {27'b0, sa[4:0]} : 
                  src1_is_pc  ? pc[31:0]         :
                                rs_value;
assign alu_src2 = src2_is_imm ? {{16{imm[15]}}, imm[15:0]} : 
                  src2_is_8   ? 32'd8                      :
                                rt_value;

alu u_alu(
    .alu_op     (alu_op    ),
    .alu_src1   (alu_src1  ),
    .alu_src2   (alu_src2  ),
    .alu_result (alu_result)
    );


assign data_sram_en    = 1'b1;
assign data_sram_wen   = mem_we ? 4'hf : 4'h0;
assign data_sram_addr  = alu_result;
assign data_sram_wdata = rt_value;
async_ram data_sram(
    .clk    (clk                 ), //I
    .en     (data_sram_en        ), //I
    .wen    (data_sram_wen       ), //I
    .addr   (data_sram_addr[11:2]), //I
    .wdata  (data_sram_wdata     ), //I
    .rdata  (data_sram_rdata     )  //O
    );
assign mem_result = data_sram_rdata;

assign final_result = res_from_mem ? mem_result : alu_result;

assign rf_we    = gr_we;
assign rf_waddr = dest;
assign rf_wdata = final_result;

endmodule
