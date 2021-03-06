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
	 SADD #(32) u_ADD4 ({{24{a[7]}}, a},{{16{1'b0}}, b},cwire);
	 SREG #(32) u_REG5 (cwire,clk,rst,c);


endmodule

// *********************************************************************************
// *                            END OF GENERATED FILE                              *
// *********************************************************************************
