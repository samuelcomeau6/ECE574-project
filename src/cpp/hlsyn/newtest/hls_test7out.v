// *******************************************************
// *                VERILOG DATAPATH FILE                *
// *******************************************************
module HLSM (
	input Clk, Rst, Start,
	output reg Done,
	input signed [31:0] u,
	input signed [31:0] x,
	input signed [31:0] y,
	input signed [31:0] dx,
	input signed [31:0] a,
	input signed [31:0] three,
	output reg signed [31:0] u1,
	output reg signed [31:0] x1,
	output reg signed [31:0] y1,
	output reg signed [31:0] c
);
	reg signed[31:0] t1;
	reg signed[31:0] t2;
	reg signed[31:0] t3;
	reg signed[31:0] t4;
	reg signed[31:0] t5;
	reg signed[31:0] t6;
	reg signed[31:0] t7;
	reg signed[31:0] vx1;
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
	localparam FINAL = 4'd9;
	always @(posedge Clk) begin
		case (state)
			WAIT: begin
				 Done <= 0;
				if (Start) state <=T1i1;
				else state <= WAIT;
			end
			T1i1: begin
				vx1 <= x + dx;
				t1 <= three * x;
				t5 <= three * y;
				state <= T2i2;
			end
			T2i2: begin
				x1 <= x + dx;
				c <= vx1 < a;
				state <= T3i3;
			end
			T3i3: begin
				t2 <= u * dx;
				state <= T4i4;
			end
			T4i4: begin
				t7 <= u * dx;
				state <= T5i5;
			end
			T5i5: begin
				t3 <= t1 * t2;
				state <= T6i6;
			end
			T6i6: begin
				t6 <= t5 * dx;
				y1 <= y + t7;
				state <= T7i7;
			end
			T7i7: begin
				t4 <= u - t3;
				state <= T8i8;
			end
			T8i8: begin
				u1 <= t4 - t6;
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
