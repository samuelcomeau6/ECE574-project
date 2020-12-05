// *******************************************************
// *                VERILOG DATAPATH FILE                *
// *******************************************************
module HLSM (
	input Clk, Rst, Start,
	output reg Done,
	input signed [31:0] x0,
	input signed [31:0] x1,
	input signed [31:0] x2,
	input signed [31:0] x3,
	input signed [31:0] y0,
	input signed [31:0] c0,
	input signed [31:0] five,
	input signed [31:0] ten,
	output reg signed [31:0] d1,
	output reg signed [31:0] d2,
	output reg signed [31:0] e,
	output reg signed [31:0] f,
	output reg signed [31:0] g,
	output reg signed [31:0] h
);
	reg signed[31:0] t1;
	reg signed[31:0] t2;
	reg signed[31:0] t3;
	reg signed[31:0] vd1;
	reg signed[31:0] ve;
	reg signed[31:0] vf;
	reg signed[31:0] vg;
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
				t2 <= x1 + x2;
				t3 <= x3 + c0;
				state <= T2i2;
			end
			T2i2: begin
				ve <= t2 * t3;
				vg <= x0 - ten;
				state <= T3i3;
			end
			T3i3: begin
				e <= t2 * t3;
				g <= x0 - ten;
				state <= T4i4;
			end
			T4i4: begin
				t1 <= x0 + x1;
				vf <= ve * y0;
				state <= T5i5;
			end
			T5i5: begin
				d1 <= t1 * c0;
				vd1 <= t1 * c0;
				state <= T6i6;
			end
			T6i6: begin
				state <= T7i7;
			end
			T7i7: begin
				d2 <= vd1 * five;
				f <= ve * y0;
				state <= T8i8;
			end
			T8i8: begin
				h <= vf + vg;
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
