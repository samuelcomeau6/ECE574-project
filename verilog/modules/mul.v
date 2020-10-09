
module MUL #(parameter DATAWIDTH = 64)(input [DATAWIDTH-1:0]a,input [DATAWIDTH-1:0]b,output reg [DATAWIDTH-1:0]prod);//Multiplier Module

    always@(*) begin
    prod <= a*b;
    end
endmodule

