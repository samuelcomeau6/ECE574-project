// *******************************************************
// *                VERILOG DATAPATH FILE                *
// *******************************************************
module HLSM (
	input Clk, Rst, Start,
	output reg Done,
	input [31:0] a,
	input [31:0] b,
	input [31:0] c,
	input [31:0] d,
	input [31:0] e,
	input [31:0] f,
	input [31:0] g,
	input [31:0] h,
	input [31:0] i,
	input [31:0] j,
	input [31:0] l,
	input [31:0] m,
	input [31:0] n,
	input [31:0] o,
	input [31:0] p,
	input [31:0] q,
	input [31:0] r,
	input [31:0] s,
	input [31:0] t,
	input [31:0] u,
	input [31:0] v,
	input [31:0] w,
	input [31:0] x,
	input [31:0] y,
	input [31:0] z,
	input [31:0] aa,
	input [31:0] bb,
	input [31:0] cc,
	input [31:0] dd,
	input [31:0] ee,
	input [31:0] ff,
	input [31:0] gg,
	input [31:0] hh,
	input [31:0] ii,
	output reg [31:0] final
);
	reg [31:0] t1;
	reg [31:0] t2;
	reg [31:0] t3;
	reg [31:0] t4;
	reg [31:0] t5;
	reg [31:0] t6;
	reg [31:0] t7;
	reg [31:0] t8;
	reg [31:0] t9;
	reg [31:0] t10;
	reg [31:0] t11;
	reg [31:0] t12;
	reg [31:0] t13;
	reg [31:0] t14;
	reg [31:0] t15;
	reg [31:0] t16;
	reg [31:0] t17;
	reg [31:0] t18;
	reg [31:0] t19;
	reg [31:0] t20;
	reg [31:0] t21;
	reg [31:0] t22;
	reg [31:0] t23;
	reg [31:0] t24;
	reg [31:0] t25;
	reg [31:0] t26;
	reg [31:0] t27;
	reg [31:0] t28;
	reg [31:0] t29;
	reg [31:0] t30;
	reg [31:0] t31;
	reg [31:0] t32;
	reg [31:0] t33;
	reg [5:0] state;
	localparam WAIT = 6'd0;
	localparam T1i1 = 6'd1;
	localparam T2i2 = 6'd2;
	localparam T3i3 = 6'd3;
	localparam T4i4 = 6'd4;
	localparam T5i5 = 6'd5;
	localparam T6i6 = 6'd6;
	localparam T7i7 = 6'd7;
	localparam T8i8 = 6'd8;
	localparam T9i9 = 6'd9;
	localparam T10i10 = 6'd10;
	localparam T11i11 = 6'd11;
	localparam T12i12 = 6'd12;
	localparam T13i13 = 6'd13;
	localparam T14i14 = 6'd14;
	localparam T15i15 = 6'd15;
	localparam T16i16 = 6'd16;
	localparam T17i17 = 6'd17;
	localparam T18i18 = 6'd18;
	localparam T19i19 = 6'd19;
	localparam T20i20 = 6'd20;
	localparam T21i21 = 6'd21;
	localparam T22i22 = 6'd22;
	localparam T23i23 = 6'd23;
	localparam T24i24 = 6'd24;
	localparam T25i25 = 6'd25;
	localparam T26i26 = 6'd26;
	localparam T27i27 = 6'd27;
	localparam T28i28 = 6'd28;
	localparam T29i29 = 6'd29;
	localparam T30i30 = 6'd30;
	localparam T31i31 = 6'd31;
	localparam T32i32 = 6'd32;
	localparam T33i33 = 6'd33;
	localparam T34i34 = 6'd34;
	localparam FINAL = 6'd35;
	always @(posedge Clk) begin
		case (state)
			WAIT: begin
				 Done <= 0;
				if (Start) state <=T1i1;
				else state <= WAIT;
			end
			T1i1: begin
				t1 <= a + b;
				state <= T2i2;
			end
			T2i2: begin
				t2 <= t1 + c;
				state <= T3i3;
			end
			T3i3: begin
				t3 <= t2 + d;
				state <= T4i4;
			end
			T4i4: begin
				t4 <= t3 + e;
				state <= T5i5;
			end
			T5i5: begin
				t5 <= t4 + f;
				state <= T6i6;
			end
			T6i6: begin
				t6 <= t5 + g;
				state <= T7i7;
			end
			T7i7: begin
				t7 <= t6 + h;
				state <= T8i8;
			end
			T8i8: begin
				t8 <= t7 + i;
				state <= T9i9;
			end
			T9i9: begin
				t9 <= t8 + j;
				state <= T10i10;
			end
			T10i10: begin
				t10 <= t9 + l;
				state <= T11i11;
			end
			T11i11: begin
				t11 <= t10 + m;
				state <= T12i12;
			end
			T12i12: begin
				t12 <= t11 + n;
				state <= T13i13;
			end
			T13i13: begin
				t13 <= t12 + o;
				state <= T14i14;
			end
			T14i14: begin
				t14 <= t13 + p;
				state <= T15i15;
			end
			T15i15: begin
				t15 <= t14 + q;
				state <= T16i16;
			end
			T16i16: begin
				t16 <= t15 + r;
				state <= T17i17;
			end
			T17i17: begin
				t17 <= t16 + s;
				state <= T18i18;
			end
			T18i18: begin
				t18 <= t17 + t;
				state <= T19i19;
			end
			T19i19: begin
				t19 <= t18 + u;
				state <= T20i20;
			end
			T20i20: begin
				t20 <= t19 + v;
				state <= T21i21;
			end
			T21i21: begin
				t21 <= t20 + w;
				state <= T22i22;
			end
			T22i22: begin
				t22 <= t21 + x;
				state <= T23i23;
			end
			T23i23: begin
				t23 <= t22 + y;
				state <= T24i24;
			end
			T24i24: begin
				t24 <= t23 + z;
				state <= T25i25;
			end
			T25i25: begin
				t25 <= t24 + aa;
				state <= T26i26;
			end
			T26i26: begin
				t26 <= t25 + bb;
				state <= T27i27;
			end
			T27i27: begin
				t27 <= t26 + cc;
				state <= T28i28;
			end
			T28i28: begin
				t28 <= t27 + dd;
				state <= T29i29;
			end
			T29i29: begin
				t29 <= t28 + ee;
				state <= T30i30;
			end
			T30i30: begin
				t30 <= t29 + ff;
				state <= T31i31;
			end
			T31i31: begin
				t31 <= t30 + gg;
				state <= T32i32;
			end
			T32i32: begin
				t32 <= t31 + hh;
				state <= T33i33;
			end
			T33i33: begin
				t33 <= t32 + ii;
				state <= T34i34;
			end
			T34i34: begin
				final <= t33 + t1;
				state <= FINAL;
			end
			FINAL: begin
				Done <= 1'd1;
				state <= WAIT;
			end
		endcase
	end

endmodule

// *******************************************************
// *                END OF GENERATED FILE                *
// *******************************************************
