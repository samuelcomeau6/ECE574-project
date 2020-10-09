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

module INC_TB(

    );

    reg [`MAX_WIDTH-1:0] INC_a;
    wire [`MAX_WIDTH-1:0] INC_d;

    INC #(.DATAWIDTH( `MAX_WIDTH )) inc1 (.a(INC_a),.d(INC_d));

    initial begin

        //TEST INC
        INC_a=`a;
        #10 `assert(INC_d,INC_a+1);
        //SUCCESSFUL RUN
        $finish;
    end
endmodule
