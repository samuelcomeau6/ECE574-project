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

module SHL_TB(

    );

    reg [`MAX_WIDTH-1:0] SHL_a;
    reg [`MAX_WIDTH-1:0] SHL_sh_amt;
    
    wire [`MAX_WIDTH-1:0] SHL_d;

    SHL #(.DATAWIDTH(`MAX_WIDTH)) shl1 (.a(SHL_a),.sh_amt(SHL_sh_amt),.d(SHL_d));

    initial begin
      //TEST SHl
      SHL_a=`a;
      for(SHL_sh_amt=0;SHL_sh_amt<`MAX_WIDTH;SHL_sh_amt=SHL_sh_amt+1) begin
          #10 `assert(SHL_d,SHL_a<<<SHL_sh_amt);
      end
    end
endmodule
