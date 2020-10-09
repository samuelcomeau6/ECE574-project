
module REG #(parameter DATAWIDTH = 64)(input[DATAWIDTH-1:0]d,input Clk,input Rst,output reg [DATAWIDTH-1:0]q);//Register Module

    always@(posedge Clk)begin
        if (Rst == 1) begin
            q <= 0;
        end
        else begin 
            q <= d;
        end
    end
endmodule