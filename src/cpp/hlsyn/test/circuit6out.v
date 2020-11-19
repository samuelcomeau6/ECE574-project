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

module circuit6(

	 input clk,
	 input rst,
	 input signed [63:0] a,
	 input signed [63:0] b,
	 input signed [63:0] c,
	 input signed [63:0] zero,

	 output signed [63:0] z
);

	 wire signed [63:0] e;
	 wire signed [63:0] f;
	 wire signed [63:0] g;
	 wire signed [63:0] zwire;
	 wire gEQz;
	 SDEC #(64) u_DEC10 (a,e);
	 SINC #(64) u_INC11 (c,f);
	 SMOD #(64) u_MOD12 (a,c,g);
	 SCOMP #(64) u_COMP13 (g,zero,.eq(gEQz));
	 SMUX2x1 #(64) u_MUX2x114 (e,f,gEQz,zwire);
	 SREG #(64) u_REG15 (zwire,clk,rst,z);


endmodule

// *********************************************************************************
// *                            END OF GENERATED FILE                              *
// *********************************************************************************
