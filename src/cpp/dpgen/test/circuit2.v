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

	 input [31:0] a,
	 input [31:0] b,
	 input [31:0] c,

	 output [31:0] z,
	 output [31:0] x
);

	 wire [31:0] d;
	 wire [31:0] e;
	 wire [31:0] f;
	 wire [31:0] g;
	 wire [31:0] h;
	 wire [0:0] dLTe;
	 wire [0:0] dEQe;
	 wire [31:0] zwire;
	 wire [31:0] xwire;
	 ADD #(0) u_ADD14 (a,b,d);
	 ADD #(0) u_ADD15 (a,c,e);
	 SUB #(0) u_SUB16 (a,b,f);
	 COMP== #(0) u_COMP==17 (d,e,dEQe);
	 COMP< #(0) u_COMP<18 (d,e,dLTe);
	 SHL #(0) u_SHL21 (g,dLTe,xwire);
	 SHR #(0) u_SHR22 (h,dEQe,zwire);
	 assign x = xwire;
	 assign z = zwire;


endmodule

// *********************************************************************************
// *                            END OF GENERATED FILE                              *
// *********************************************************************************