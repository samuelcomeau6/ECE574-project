// *******************************************************
// *                VERILOG DATAPATH FILE                *
// *******************************************************
module HLSM (
	input Clk, Rst, Start,
	output reg Done,
	input signed [7:0] a,
	input signed [7:0] b,
	input signed [7:0] c,
	input signed [7:0] d,
	input signed [7:0] e,
	input signed [7:0] f,
	input signed [7:0] g,
	input signed [7:0] h,
	input signed [7:0] num,
	output reg signed [7:0] avg
);
	reg signed[31:0] t1;
	reg signed[31:0] t2;
	reg signed[31:0] t3;
	reg signed[31:0] t4;
	reg signed[31:0] t5;
	reg signed[31:0] t6;
	reg signed[31:0] t7;
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
	localparam FINAL = 4'd11;
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
				avg <= t7 / num;
				state <= T9i9;
			end
			T9i9: begin
				state <= T10i10;
			end
			T10i10: begin
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
