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

	 output signed [31:0] z,
	 output signed [31:0] x
);

	 wire signed [31:0] d;
	 wire signed [31:0] e;
	 wire signed [31:0] f;
	 wire signed [31:0] g;
	 wire signed [31:0] h;
	 wire dLTe;
	 wire dEQe;
	 wire signed [31:0] zwire;
	 wire signed [31:0] xwire;
	 SADD #(32) s_ADD14 (a,b,d);
	 SADD #(32) s_ADD15 (a,c,e);
	 SSUB #(32) s_SUB16 (a,b,f);
	 SCOMP #(32) s_COMP17 (d,e,.eq(dEQe));
	 SCOMP #(32) s_COMP18 (d,e,.lt(dLTe));
	 SSHL #(32) s_SHL21 (g,dLTe,xwire);
	 SSHR #(32) s_SHR22 (h,dEQe,zwire);
	 SREG #(32) s_REG23 (xwire,clk,rst,x);
	 SREG #(32) s_REG24 (zwire,clk,rst,z);


endmodule

// *********************************************************************************
// *                            END OF GENERATED FILE                              *
// *********************************************************************************
