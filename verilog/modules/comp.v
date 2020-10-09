
module COMP #(parameter DATAWIDTH = 64)(input[DATAWIDTH-1:0]a,input[DATAWIDTH-1:0]b,output reg gt,output reg lt,output reg eq);//Comparator Module

    always @(*)begin
        if (a < b) begin
        gt <= 0;
        lt <= 1;
        eq <= 0;
        end
        else if (a > b) begin
        gt <= 1;
        lt <= 0;
        eq <= 0;
        end
        else begin
        gt <= 0;
        lt <= 0;
        eq <= 1;
        end
    end
endmodule

