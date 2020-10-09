
module MUX2x1 #(parameter DATAWIDTH = 64)(input[DATAWIDTH-1:0]a,input[DATAWIDTH-1:0]b,input sel,output reg [DATAWIDTH-1:0]d);//Mux Module

    always@(*) begin
        if (sel == 0) begin
        d <= a;
        end
        else begin
        d <= b;
        end    
    end
endmodule
