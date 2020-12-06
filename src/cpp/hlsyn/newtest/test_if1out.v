// *******************************************************
// *                VERILOG DATAPATH FILE                *
// *******************************************************
module HLSM (
	input Clk, Rst, Start,
	output reg Done,
	input signed [31:0] a,
	input signed [31:0] b,
	input signed [31:0] c,
	output reg signed [31:0] z,
	output reg signed [31:0] x
);
	reg signed[31:0] d;
	reg signed[31:0] f;
	reg signed[31:0] g;
	reg signed[31:0] zrin;
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
				d <= a + b;
				g <= a < b;
				zrin <= a + c;
				f <= a * c;
				state <= T2i2;
			end
			T2i2: begin
				if(g) zrin <= a + b;
				state <= T3i3;
			end
			T3i3: begin
				z <= zrin + f;
				state <= T4i4;
			end
			T4i4: begin
				x <= f - d;
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
