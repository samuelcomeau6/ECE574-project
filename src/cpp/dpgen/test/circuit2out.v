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
	 SADD #(32) u_ADD14 (a,b,d);
	 SADD #(32) u_ADD15 (a,c,e);
	 SSUB #(32) u_SUB16 (a,b,f);
	 SCOMP #(32) u_COMP17 (d,e,.eq(dEQe));
	 SCOMP #(32) u_COMP18 (d,e,.lt(dLTe));
	 SMUX2x1 #(32) u_MUX2x119 (d,e,dLTe,g);
	 SMUX2x1 #(32) u_MUX2x120 (g,f,dEQe,h);
	 SSHL #(32) u_SHL21 (g,{{31{1'b0}}, dLTe},xwire);
	 SSHR #(32) u_SHR22 (h,{{31{1'b0}}, dEQe},zwire);
	 SREG #(32) u_REG23 (xwire,clk,rst,x);
	 SREG #(32) u_REG24 (zwire,clk,rst,z);


endmodule

// *********************************************************************************
// *                            END OF GENERATED FILE                              *
// *********************************************************************************
