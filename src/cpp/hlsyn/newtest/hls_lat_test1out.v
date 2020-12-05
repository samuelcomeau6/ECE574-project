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
	reg [2:0] state;
	localparam WAIT = 3'd0;
	localparam T1i1 = 3'd1;
	localparam T2i2 = 3'd2;
	localparam T3i3 = 3'd3;
	localparam T4i4 = 3'd4;
	localparam FINAL = 3'd5;
	always @(posedge Clk) begin
		case (state)
			WAIT: begin
				 Done <= 0;
				if (Start) state <=T1i1;
				else state <= WAIT;
			end
			T1i1: begin
				f <= a + b;
				state <= T2i2;
			end
			T2i2: begin
				g <= f + c;
				state <= T3i3;
			end
			T3i3: begin
				h <= g + d;
				state <= T4i4;
			end
			T4i4: begin
				i <= h + e;
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
