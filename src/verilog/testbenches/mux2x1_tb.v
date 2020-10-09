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

module MUX2x1_TB(

    );

    reg [`MAX_WIDTH-1:0] MUX2x1_a,MUX2x1_b;
    wire [`MAX_WIDTH-1:0] MUX2x1_d;
    reg MUX2x1_sel;

      MUX2x1 #(.DATAWIDTH(`MAX_WIDTH))
            mux1 (.a(MUX2x1_a),.b(MUX2x1_b),.sel(MUX2x1_sel),.d(MUX2x1_d));

      initial begin
        //TEST MUX2x1
        MUX2x1_a=`a;
        MUX2x1_b=`b;
        MUX2x1_sel=0;
        #10 `assert(MUX2x1_d,MUX2x1_a);
        MUX2x1_sel=1;
        #10 `assert(MUX2x1_d,MUX2x1_b);
      end
endmodule
