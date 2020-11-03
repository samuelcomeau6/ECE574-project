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

module circuit1(

	 input clk,
	 input rst,
	 input signed [7:0] a,
	 input signed [7:0] b,
	 input signed [7:0] c,

	 output signed [7:0] z,
	 output signed [15:0] x
);

	 wire signed [7:0] d;
	 wire signed [7:0] e;
	 wire signed [15:0] f;
	 wire signed [15:0] g;
	 wire signed [15:0] xwire;
	 ADD #(8) s_ADD10 (a,b,d);
	 ADD #(8) s_ADD11 (a,c,e);
	 COMP #(16) s_COMP12 (d,e,.gt(g));
	 MUX2x1 #(8) s_MUX13 (d,e,g,z);
	 MUL #(16) s_MUL14 (a,c,f);
	 SUB #(16) s_SUB15 (f,d,xwire);
	 REG #(16) s_REG16 (zwire,clk,rst,z);
	 REG #(16) s_REG17 (xwire,clk,rst,x);


endmodule

// *********************************************************************************
// *                            END OF GENERATED FILE                              *
// *********************************************************************************
