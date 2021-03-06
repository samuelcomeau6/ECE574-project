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

module mcircuit1(

	 input clk,
	 input rst,
	 input signed [7:0] a,
	 input [7:0] b,

	 output signed [7:0] c
);

	 wire signed [7:0] cwire;
	 SADD #(8) u_ADD4 (a,b,cwire);
	 SREG #(8) u_REG5 (cwire,clk,rst,c);


endmodule

// *********************************************************************************
// *                            END OF GENERATED FILE                              *
// *********************************************************************************
