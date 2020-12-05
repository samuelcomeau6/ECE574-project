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
	input [31:0] sa,
	output reg [31:0] avg
);
	reg [31:0] t1;
	reg [31:0] t2;
	reg [31:0] t3;
	reg [31:0] t4;
	reg [31:0] t5;
	reg [31:0] t6;
	reg [31:0] t7;
	reg [31:0] t7div2;
	reg [31:0] t7div4;
	reg [3:0] state;
	localparam WAIT = 4'd0;
	localparam T1i1 = 4'd1;
	localparam T2i2 = 4'd2;
	localparam T3i3 = 4'd3;
	localparam T4i4 = 4'd4;
	localparam T5i5 = 4'd5;
	localparam T6i6 = 4'd6;
	localparam T7i7 = 4'd7;
	localparam T8i8 = 4'd8;
	localparam T9i9 = 4'd9;
	localparam T10i10 = 4'd10;
	localparam T11i11 = 4'd11;
	localparam FINAL = 4'd12;
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
				state <= T3i3;
			end
			T3i3: begin
				t2 <= t1 + c;
				state <= T4i4;
			end
			T4i4: begin
				t3 <= t2 + d;
				state <= T5i5;
			end
			T5i5: begin
				t4 <= t3 + e;
				state <= T6i6;
			end
			T6i6: begin
				t5 <= t4 + f;
				state <= T7i7;
			end
			T7i7: begin
				t6 <= t5 + g;
				state <= T8i8;
			end
			T8i8: begin
				t7 <= t6 + h;
				state <= T9i9;
			end
			T9i9: begin
				t7div2 <= t7 >> sa;
				state <= T10i10;
			end
			T10i10: begin
				t7div4 <= t7div2 >> sa;
				state <= T11i11;
			end
			T11i11: begin
				avg <= t7div4 >> sa;
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
