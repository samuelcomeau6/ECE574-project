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

module circuit4(

	 input [63:0] a,
	 input [63:0] b,
	 input [63:0] c,

	 output [31:0] z,
	 output [31:0] x
);

	 wire [63:0] d;
	 wire [63:0] e;
	 wire [63:0] f;
	 wire [63:0] g;
	 wire [63:0] h;
	 wire [0:0] dLTe;
	 wire [0:0] dEQe;
	 wire [63:0] xrin;
	 wire [63:0] zrin;
	 ADD #(0) u_ADD16 (a,b,d);
	 ADD #(0) u_ADD17 (a,c,e);
	 SUB #(0) u_SUB18 (a,b,f);
	 COMP== #(0) u_COMP==19 (d,e,dEQe);
	 COMP< #(0) u_COMP<20 (d,e,dLTe);
	 assign greg = g;
	 assign hreg = h;
	 SHL #(0) u_SHL25 (hreg,dLTe,xrin);
	 SHR #(0) u_SHR26 (greg,dEQe,zrin);
	 assign x = xrin;
	 assign z = zrin;


endmodule

// *********************************************************************************
// *                            END OF GENERATED FILE                              *
// *********************************************************************************
