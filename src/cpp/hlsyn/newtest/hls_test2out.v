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
	reg signed[31:0] e;
	reg signed[31:0] f;
	reg signed[31:0] g;
	reg signed[31:0] h;
	reg dLTe;
	reg dEQe;
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
				d <= a + b;
				e <= a + c;
				state <= T2i2;
			end
			T2i2: begin
				f <= a - b;
				dLTe <= d < e;
				state <= T3i3;
			end
			T3i3: begin
				g <= dLTe ? d : e;
				state <= T4i4;
			end
			T4i4: begin
				dEQe <= d == e;
				x <= g << dLTe;
				state <= T5i5;
			end
			T5i5: begin
				h <= dEQe ? g : f;
				state <= T6i6;
			end
			T6i6: begin
				z <= h >> dEQe;
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
