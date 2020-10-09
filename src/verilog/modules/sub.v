module SUB #(
    parameter DATAWIDTH=2
)(
    input [DATAWIDTH-1:0] a,
    input [DATAWIDTH-1:0] b,
    output reg [DATAWIDTH-1:0] diff
);
    always @(*) begin
        diff <= a - b;
    end
endmodule