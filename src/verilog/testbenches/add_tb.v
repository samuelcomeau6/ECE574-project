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

module ADD_TB(

    );
    reg [`MAX_WIDTH-1:0] ADD_a,ADD_b;
    wire [`MAX_WIDTH-1:0] ADD_sum;

    ADD #(.DATAWIDTH(`MAX_WIDTH)) add1 (.a(ADD_a),.b(ADD_b),.sum(ADD_sum));

    initial begin
      //TEST ADD
      ADD_a=`a;
      ADD_b=`b;
      #10 `assert(ADD_sum,ADD_a+ADD_b);
    end
endmodule
