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

module error3(

	 input clk,
	 input rst,
	 input signed [7:0] a,
	 input signed [7:0] b,

	 output signed [7:0] z,
	 output signed [15:0] x
);

	 wire signed [7:0] d;
	 wire signed [7:0] e;
	 wire signed [15:0] f;
	 wire signed [15:0] g;
	 wire signed [15:0] xwire;
	 SADD #(8) u_ADD9 (a,b,d);
