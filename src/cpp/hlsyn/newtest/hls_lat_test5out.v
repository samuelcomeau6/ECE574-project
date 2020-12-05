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
	input signed [15:0] f,
	output reg signed [15:0] j,
	output reg signed [15:0] k
);
	reg signed[15:0] h;
	reg signed[15:0] i;
	reg [3:0] state;
	localparam WAIT = 4'd0;
	localparam T1i1 = 4'd1;
	localparam T2i2 = 4'd2;
	localparam T3i3 = 4'd3;
	localparam T4i4 = 4'd4;
	localparam T5i5 = 4'd5;
	localparam T6i6 = 4'd6;
	localparam FINAL = 4'd7;
	always @(posedge Clk) begin
		case (state)
			WAIT: begin
				 Done <= 0;
				if (Start) state <=T1i1;
				else state <= WAIT;
			end
			T1i1: begin
				h <= a * b;
				state <= T2i2;
			end
			T2i2: begin
				state <= T3i3;
			end
			T3i3: begin
				i <= h + c;
				k <= e * f;
				state <= T4i4;
			end
			T4i4: begin
				state <= T5i5;
			end
			T5i5: begin
				j <= i * d;
				state <= T6i6;
			end
			T6i6: begin
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
