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

module circuit2(

	 input clk,
	 input rst,
	 input signed [31:0] a,
	 input signed [31:0] b,
	 input signed [31:0] c,

	 output signed [31:0] z;
	 output signed [31:0] x
);

	 wire signed [31:0] d;
	 wire signed [31:0] e;
	 wire signed [31:0] f;
	 wire signed [31:0] g;
	 wire signed [31:0] h;
	 wire [0:0] dLTe;
	 wire [0:0] dEQe;
	 wire signed [31:0] zwire;
	 wire signed [31:0] xwire;
	 ADD #(32) s_ADD14 (a,b,d);
	 ADD #(32) s_ADD15 (a,c,e);
	 SUB #(32) s_SUB16 (a,b,f);
	 COMP #(32) s_COMP17 (d,e,.eq(dEQe));
	 COMP #(32) s_COMP18 (d,e,.lt(dLTe));
	 SHL #(32) s_SHL21 (g,dLTe,xwire);
	 SHR #(32) s_SHR22 (h,dEQe,zwire);
	 REG #(32) s_REG (xwire,clk,rst,x);
	 REG #(32) s_REG (zwire,clk,rst,x);

endmodule

// *********************************************************************************
// *                            END OF GENERATED FILE                              *
// *********************************************************************************
