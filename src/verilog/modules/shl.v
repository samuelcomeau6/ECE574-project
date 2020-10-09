module SHL #(
    parameter DATAWIDTH=2
)(
    input [DATAWIDTH-1:0] a,
    input [DATAWIDTH-1:0] sh_amt,
    
    output reg [DATAWIDTH-1:0] d
);
    always @(*) 
    begin
        d <= a << sh_amt;
    end
endmodule
