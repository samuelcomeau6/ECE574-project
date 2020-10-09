module DIV #(
    parameter DATAWIDTH=2
)(
    input [DATAWIDTH-1:0] a,
    input [DATAWIDTH-1:0] b,
    
    output reg [DATAWIDTH-1:0] quot
);
    always @(*) 
    begin
        quot <= a / b;
    end
endmodule
