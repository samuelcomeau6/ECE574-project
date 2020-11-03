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

	 input clk,
	 input rst,
	 input [63:0] a,
	 input [63:0] b,
	 input [63:0] c,

	 output [31:0] z;
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
	 ADD #(64) u_ADD16 (a,b,d);
	 ADD #(64) u_ADD17 (a,c,e);
	 SUB #(64) u_SUB18 (a,b,f);
	 COMP #(64) u_COMP19 (d,e,.eq(dEQe));
	 COMP #(64) u_COMP20 (d,e,.lt(dLTe));
	 REG #(64) u_REG21 (g,clk,rst,greg);
	 REG #(64) u_REG22 (h,clk,rst,hreg);
	 SHL #(0) u_SHL25 (hreg,dLTe,xrin);
	 SHR #(0) u_SHR26 (greg,dEQe,zrin);
	 REG #(32) u_REG27 (xrin,clk,rst,x);
	 REG #(32) u_REG28 (zrin,clk,rst,z);


endmodule

// *********************************************************************************
// *                            END OF GENERATED FILE                              *
// *********************************************************************************
