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
	input signed [15:0] g,
	input signed [15:0] h,
	output reg signed [15:0] i,
	output reg signed [15:0] j,
	output reg signed [15:0] k,
	output reg signed [15:0] l
);
	reg [2:0] state;
	localparam WAIT = 3'd0;
	localparam T1i1 = 3'd1;
	localparam T2i2 = 3'd2;
	localparam FINAL = 3'd3;
	always @(posedge Clk) begin
		case (state)
			WAIT: begin
				 Done <= 0;
				if (Start) state <=T1i1;
				else state <= WAIT;
			end
			T1i1: begin
				i <= a * b;
				j <= c * d;
				k <= e * f;
				l <= g * h;
				state <= T2i2;
			end
			T2i2: begin
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
