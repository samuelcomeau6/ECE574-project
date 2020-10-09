module ADD #(
    parameter DATAWIDTH=2
)(
    input [DATAWIDTH-1:0] a,
    input [DATAWIDTH-1:0] b,
    output reg [DATAWIDTH-1:0] sum
);
    always @(*) begin
        sum <= a + b;
    end
endmodule