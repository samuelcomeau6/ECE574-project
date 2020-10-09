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

module DEC_TB(

    );

    reg [`MAX_WIDTH-1:0] DEC_a;
    wire [`MAX_WIDTH-1:0]DEC_d;

    DEC #(.DATAWIDTH(`MAX_WIDTH)) dec1 (.a(DEC_a),.d(DEC_d));
    initial begin

        //TEST DEC
        DEC_a=`a;
        #10 `assert(DEC_d,DEC_a-1);
        //SUCCESSFUL RUN
        $finish;
    end
endmodule
