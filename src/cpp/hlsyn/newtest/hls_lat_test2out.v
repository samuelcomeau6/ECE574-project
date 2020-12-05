// *******************************************************
// *                VERILOG DATAPATH FILE                *
// *******************************************************
module HLSM (
	input Clk, Rst, Start,
	output reg Done,
	input signed [15:0] a,
	input signed [15:0] b,
	input signed [15:0] c,
	input signed [15:0] d,
	input signed [15:0] e,
	output reg signed [15:0] i
);
	reg signed[15:0] f;
	reg signed[15:0] g;
	reg signed[15:0] h;
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
	localparam FINAL = 4'd10;
	always @(posedge Clk) begin
		case (state)
			WAIT: begin
				 Done <= 0;
				if (Start) state <=T1i1;
				else state <= WAIT;
			end
			T1i1: begin
				f <= a * b;
				state <= T2i2;
			end
			T2i2: begin
				state <= T3i3;
			end
			T3i3: begin
				g <= f * c;
				state <= T4i4;
			end
			T4i4: begin
				state <= T5i5;
			end
			T5i5: begin
				h <= g * d;
				state <= T6i6;
			end
			T6i6: begin
				state <= T7i7;
			end
			T7i7: begin
				i <= h * e;
				state <= T8i8;
			end
			T8i8: begin
				state <= T9i9;
			end
			T9i9: begin
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
