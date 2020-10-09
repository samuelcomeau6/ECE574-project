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

module COMP_TB(

    );

    reg [`MAX_WIDTH-1:0] COMP_a,COMP_b;
    wire COMP_gt,COMP_lt,COMP_eq;

    COMP #(.DATAWIDTH(`MAX_WIDTH))
        comp1 (.a(COMP_a),.b(COMP_b),.gt(COMP_gt),.lt(COMP_lt),.eq(COMP_eq));

    initial begin
      //TEST COMP
      COMP_a=`a;
      COMP_b=`b;
      #10;
      if(`a>`b) begin
          `assert(COMP_gt,1);
          `assert(COMP_eq,0);
          `assert(COMP_lt,0);
      end
      if(`a==`b) begin
          `assert(COMP_gt,0);
          `assert(COMP_eq,1);
          `assert(COMP_lt,0);
      end
      if(`a<`b) begin
          `assert(COMP_gt,0);
          `assert(COMP_eq,0);
          `assert(COMP_lt,1);
      end
    end
endmodule
