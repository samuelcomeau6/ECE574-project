module DEC #(
    parameter DATAWIDTH=2
)(
    input [DATAWIDTH-1:0] a,
    output reg [DATAWIDTH-1:0] d
);
    always @(*) begin
        d <= a - 1;
    end
endmodule