// *******************************************************
// *                VERILOG DATAPATH FILE                *
// *******************************************************
module HLSM (
	input Clk, Rst, Start,
	output reg Done,
	input [63:0] a,
	input [63:0] b,
	input [63:0] c,
	input [63:0] d,
	input [63:0] zero,
	output reg [63:0] z
);
	reg [63:0] e;
	reg [63:0] f;
	reg [63:0] g;
	reg gEQz;
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
				g <= a % b;
				state <= T2i2;
			end
			T2i2: begin
				f <= c / d;
				state <= T3i3;
			end
			T3i3: begin
				state <= T4i4;
			end
			T4i4: begin
				gEQz <= g == zero;
				state <= T5i5;
			end
			T5i5: begin
				e <= a / b;
				state <= T6i6;
			end
			T6i6: begin
				state <= T7i7;
			end
			T7i7: begin
				state <= T8i8;
			end
			T8i8: begin
				z <= gEQz ? e : f;
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
