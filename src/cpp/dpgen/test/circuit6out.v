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
	 DEC #(64) u_DEC10 (a,e);
	 INC #(64) u_INC11 (c,f);
	 MOD #(64) u_MOD12 (a,c,g);
	 COMP #(64) u_COMP13 (g,zero,.eq(gEQz));
	 REG #(64) u_REG14 (zwire,clk,rst,z);


endmodule

// *********************************************************************************
// *                            END OF GENERATED FILE                              *
// *********************************************************************************
