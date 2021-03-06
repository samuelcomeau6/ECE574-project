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

module circuit5(

	 input clk,
	 input rst,
	 input signed [63:0] a,
	 input signed [63:0] b,
	 input signed [63:0] c,
	 input signed [63:0] d,
	 input signed [63:0] zero,

	 output signed [63:0] z
);

	 wire signed [63:0] e;
	 wire signed [63:0] f;
	 wire signed [63:0] g;
	 wire signed [63:0] zwire;
	 wire gEQz;
	 SDIV #(64) u_DIV11 (a,b,e);
	 SDIV #(64) u_DIV12 (c,d,f);
	 SMOD #(64) u_MOD13 (a,b,g);
	 SCOMP #(64) u_COMP14 (g,zero,.eq(gEQz));
	 SMUX2x1 #(64) u_MUX2x115 (e,f,gEQz,zwire);
	 SREG #(64) u_REG16 (zwire,clk,rst,z);


endmodule

// *********************************************************************************
// *                            END OF GENERATED FILE                              *
// *********************************************************************************
