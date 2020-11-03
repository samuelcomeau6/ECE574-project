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

module (

	 input a,
	 input b,

	 output z;
	 output x
);

	 wire [7:0] d;
	 wire [7:0] e;
	 wire [15:0] f;
	 wire [15:0] g;
	 wire [15:0] xwire;
	 ADD #(0) u_ADD9 (a,b,d);
	 ADD #(0) u_ADD10 (a,c,e);
	 COMP> #(0) u_COMP>11 (d,e,g);
	 MUL #(0) u_MUL13 (a,c,f);
	 SUB #(0) u_SUB14 (f,d,xwire);
	 assign x = xwire;


endmodule

// *********************************************************************************
// *                            END OF GENERATED FILE                              *
// *********************************************************************************
