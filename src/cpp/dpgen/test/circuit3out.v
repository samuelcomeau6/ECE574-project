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

module circuit3(

	 input clk,
	 input rst,
	 input signed [15:0] a,
	 input signed [15:0] b,
	 input signed [15:0] c,
	 input signed [15:0] d,
	 input signed [15:0] e,
	 input signed [15:0] f,
	 input signed [15:0] g,
	 input signed [15:0] h,
	 input signed [7:0] sa,

	 output signed [15:0] avg
);

	 wire signed [31:0] l00;
	 wire signed [31:0] l01;
	 wire signed [31:0] l02;
	 wire signed [31:0] l03;
	 wire signed [31:0] l10;
	 wire signed [31:0] l11;
	 wire signed [31:0] l2;
	 wire signed [31:0] l2div2;
	 wire signed [31:0] l2div4;
	 wire signed [31:0] l2div8;
	 ADD #(32) s_ADD20 (a,b,l00);
	 ADD #(32) s_ADD21 (c,d,l01);
	 ADD #(32) s_ADD22 (e,f,l02);
	 ADD #(32) s_ADD23 (g,h,l03);
	 ADD #(32) s_ADD24 (l00,l01,l10);
	 ADD #(32) s_ADD25 (l02,l03,l11);
	 ADD #(32) s_ADD26 (l10,l11,l2);
	 SHR #(32) s_SHR27 (l2,sa,l2div2);
	 SHR #(32) s_SHR28 (l2div2,sa,l2div4);
	 SHR #(32) s_SHR29 (l2div4,sa,l2div8);
	 REG #(16) s_REG30 (l2div8,clk,rst,avg);


endmodule

// *********************************************************************************
// *                            END OF GENERATED FILE                              *
// *********************************************************************************
