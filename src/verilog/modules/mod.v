module MOD #(
    parameter DATAWIDTH=2
)(
    input [DATAWIDTH-1:0] a,
    input [DATAWIDTH-1:0] b,
    
    output reg [DATAWIDTH-1:0] rem
);
    always @(*) 
    begin
        rem <= a % b;
    end
endmodule
