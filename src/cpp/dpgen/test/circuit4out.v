// *********************************************************************************
// *********************************************************************************
// *                                                                               *
// *                             VERILOG MODULE FILE                               *
// *                                                                               *
// *   Team members:                                                               *
// *     Adam Frankowski                                                           *
// *     Samuel Comeau                                                             *
// *     Nick Paco                                                                 *
// *                                                                               *
// *                                                                               *
// *                                                                               *
// *********************************************************************************
// *********************************************************************************

module circuit4(

	 input clk,
	 input rst,
	 input signed [63:0] a,
	 input signed [63:0] b,
	 input signed [63:0] c,

	 output signed [31:0] z,
	 output signed [31:0] x
);

	 wire signed [63:0] d;
	 wire signed [63:0] e;
	 wire signed [63:0] f;
	 wire signed [63:0] g;
	 wire signed [63:0] h;
	 wire dLTe;
	 wire dEQe;
	 wire signed [63:0] xrin;
	 wire signed [63:0] zrin;
	 wire signed [63:0] greg;
	 wire signed [63:0] hreg;
	 SADD #(64) u_ADD16 (a,b,d);
	 SADD #(64) u_ADD17 (a,c,e);
	 SSUB #(64) u_SUB18 (a,b,f);
	 SCOMP #(64) u_COMP19 (d,e,.eq(dEQe));
	 SCOMP #(64) u_COMP20 (d,e,.lt(dLTe));
	 SMUX2x1 #(64) u_MUX2x121 (d,e,dLTe,g);
	 SMUX2x1 #(64) u_MUX2x122 (g,f,dEQe,h);
	 SREG #(64) u_REG23 (g,clk,rst,greg);
	 SREG #(64) u_REG24 (h,clk,rst,hreg);
	 SSHL #(64) u_SHL25 (hreg,{{63{1'b0}}, dLTe},xrin);
	 SSHR #(64) u_SHR26 (greg,{{63{1'b0}}, dEQe},zrin);
	 SREG #(32) u_REG27 (xrin[31:0],clk,rst,x);
	 SREG #(32) u_REG28 (zrin[31:0],clk,rst,z);


endmodule

// *********************************************************************************
// *                            END OF GENERATED FILE                              *
// *********************************************************************************
