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

	 input a,
	 input b,
	 input c,
	 input d,
	 input e,
	 input f,
	 input g,
	 input h,
	 input sa,

	 output avg
);

	 wire [31:0] l00;
	 wire [31:0] l01;
	 wire [31:0] l02;
	 wire [31:0] l03;
	 wire [31:0] l10;
	 wire [31:0] l11;
	 wire [31:0] l2;
	 wire [31:0] l2div2;
	 wire [31:0] l2div4;
	 wire [31:0] l2div8;
	 ADD #(0) u_ADD20 (a,b,l00);
	 ADD #(0) u_ADD21 (c,d,l01);
	 ADD #(0) u_ADD22 (e,f,l02);
	 ADD #(0) u_ADD23 (g,h,l03);
	 ADD #(0) u_ADD24 (l00,l01,l10);
	 ADD #(0) u_ADD25 (l02,l03,l11);
	 ADD #(0) u_ADD26 (l10,l11,l2);
	 SHR #(0) u_SHR27 (l2,sa,l2div2);
	 SHR #(0) u_SHR28 (l2div2,sa,l2div4);
	 SHR #(0) u_SHR29 (l2div4,sa,l2div8);
	 assign avg = l2div8;


endmodule

// *********************************************************************************
// *                            END OF GENERATED FILE                              *
// *********************************************************************************
