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

module mcircuit2(

	 input clk,
	 input rst,
	 input signed [7:0] a,
	 input [15:0] b,

	 output signed [31:0] c
);

	 wire signed [31:0] cwire;
	 SADD #(32) s_ADD4 (a,b,cwire);
	 SREG #(32) s_REG5 (cwire,clk,rst,c);


endmodule

// *********************************************************************************
// *                            END OF GENERATED FILE                              *
// *********************************************************************************
