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

module MOD_TB(

    );

    reg [`MAX_WIDTH-1:0] MOD_a,MOD_b;
    wire [`MAX_WIDTH-1:0] MOD_rem;

    MOD #(.DATAWIDTH(`MAX_WIDTH)) mod1 (.a(MOD_a),.b(MOD_b),.rem(MOD_rem));
    initial begin


        //TEST MOD
        MOD_a=`a;
        MOD_b=`b;
        #10 `assert(MOD_rem,MOD_a%MOD_b);
        //SUCCESSFUL RUN
        $finish;
    end
endmodule
