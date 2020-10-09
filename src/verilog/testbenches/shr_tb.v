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

module SHR_TB(

    );


  reg [`MAX_WIDTH-1:0] SHR_a;
  wire [`MAX_WIDTH-1:0]SHR_d;
  reg [`MAX_WIDTH-1:0] SHR_sh_amt;

  SHR #(.DATAWIDTH(`MAX_WIDTH)) shr1 (.a(SHR_a),.sh_amt(SHR_sh_amt),.d(SHR_d));

  initial begin
    //TEST SHR
    SHR_a=`a;
    for(SHR_sh_amt=0;SHR_sh_amt<`MAX_WIDTH;SHR_sh_amt=SHR_sh_amt+1) begin
        #10 `assert(SHR_d,SHR_a>>>SHR_sh_amt);
    end
  end
endmodule
