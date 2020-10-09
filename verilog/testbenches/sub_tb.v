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

module SUB_TB(

    );

    reg [`MAX_WIDTH-1:0] SUB_a,SUB_b;
    wire [`MAX_WIDTH-1:0] SUB_diff;

    SUB #(.DATAWIDTH(`MAX_WIDTH)) sub1 (.a(SUB_a),.b(SUB_b),.diff(SUB_diff));

    initial begin
      //TEST SUB
      SUB_a=`a;
      SUB_b=`b;
      #10 `assert(SUB_diff,SUB_a-SUB_b);
    end

endmodule
