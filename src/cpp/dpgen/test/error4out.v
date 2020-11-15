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

module error4(

	 input clk,
	 input rst,
	 input signed [7:0] a,
	 input signed [7:0] b,
	 input signed [7:0] c,

	 output signed [7:0] z
);

	 wire signed [7:0] d;
	 wire signed [7:0] e;
	 wire signed [15:0] f;
	 wire signed [15:0] g;
	 wire signed [15:0] xwire;
	 SADD #(8) u_ADD9 (a,b,d);
	 SADD #(8) u_ADD10 (a,c,e);
	 SCOMP #(8) u_COMP11 (d,e,.gt(g));
	 SMUX2x1 #(8) u_MUX2x112 (d,e,g,z);
	 SMUL #(16) u_MUL13 ({{8{a[7]}}, a},{{8{c[7]}}, c},f);
	 SSUB #(16) u_SUB14 (f,{{8{d[7]}}, d},xwire);
