`timescale 1ns/1ns
`define assert(signal, value) \
	if(signal != value) begin \
		$display(" ",$realtime,":ASSERTION FAILED in %m: signal != value");\
		$display("          %m:signal = ",signal);\
		$display("          %m:value = ",value);\
		$stop;\
	end \
	if(^signal === 1'bX) begin \
		$display(" ",$realtime,":SIGNAL UNASSIGNED AT ASSERTION in %m: signal != value");\
		$display("          %m:signal = ",signal);\
		$display("          %m:value = ",value);\
		$stop;\
	end
`define MAX_WIDTH 8
`define a 10
`define b 5

module MUL_TB(

    );
    reg [`MAX_WIDTH-1:0] MUL_a,MUL_b;
    wire [`MAX_WIDTH-1:0] MUL_prod;

    MUL #(.DATAWIDTH(`MAX_WIDTH)) mul1 (.a(MUL_a),.b(MUL_b),.prod(MUL_prod));
    initial begin
      //TEST MUL
      MUL_a=`a;
      MUL_b=`b;
      #10 `assert(MUL_prod,MUL_a*MUL_b);
    end

endmodule
