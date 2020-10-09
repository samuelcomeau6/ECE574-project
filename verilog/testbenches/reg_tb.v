`timescale 1ns/1ns
`define assert(signal, value) \
	if(signal != value) begin \
		$display(" ",$realtime,":ASSERTION FAILED in %m: signal != value");\
		$display("          %m:signal = ",signal);\
		$display("          %m:value = ",value);\
		$stop;\
	end \
	if(^signal === 1'bX ) begin \
		$display(" ",$realtime,":SIGNAL UNASSIGNED AT ASSERTION in %m: signal != value");\
		$display("          %m:signal = ",signal);\
		$display("          %m:value = ",value);\
		$stop;\
	end
`define MAX_WIDTH 8
`define a 10
`define b 5

module REG_TB(
    );

    reg [`MAX_WIDTH-1:0] REG_d;
    wire [`MAX_WIDTH-1:0] REG_q;
    reg REG_Clk,REG_Rst;
    REG #(.DATAWIDTH(`MAX_WIDTH)) reg1 (.d(REG_d),.q(REG_q),.Clk(REG_Clk),.Rst(REG_Rst));
    initial begin
        //Test REG
        REG_d=`a;
        REG_Rst=0;
        #10 REG_Clk=1;
        #10 `assert(reg1.Clk,1);
        #10 REG_Clk=0;
        #10 `assert(REG_q,REG_d);
        REG_d=`b;
        #10 `assert(REG_q,`a);
        #10 REG_Rst=1;
        #10 REG_Clk=1;
        #10 `assert(REG_q,0);
        #10 REG_Rst=0;
        #10 `assert(REG_q,0);
        #10 REG_Clk=0;
        #10 `assert(REG_q,0);
        #10 REG_Clk=1;
        #10 `assert(REG_q,REG_d);
    end
endmodule
