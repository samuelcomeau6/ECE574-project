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


module DIV_TB(

  );

  reg [`MAX_WIDTH-1:0] DIV_a,DIV_b;
  wire [`MAX_WIDTH-1:0] DIV_quot;

  DIV #(.DATAWIDTH(`MAX_WIDTH)) div1 (.a(DIV_a),.b(DIV_b),.quot(DIV_quot));

  initial begin
    //TEST DIV
    DIV_a=`a;
    DIV_b=`b;
    #10 `assert(DIV_quot,DIV_a/DIV_b);
  end
endmodule
