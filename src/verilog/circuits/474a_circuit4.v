`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 10/01/2020 04:36:12 AM
// Design Name: 
// Module Name: 474a_circuit4
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module circuit4(
    input clk,
    input rst,
    input [63:0] a,
    input [63:0] b,
    input [63:0] c,
    output reg [31:0] z,
    output reg [31:0] x
    );

    //wire Int64 d, e, f, g, h
    wire [63:0] d, e, f, g, h; 
    //wire Int1 dLTe, dEQe 
    wire dLTe, dEQe;
    //wire Int64 xrin, zrin
    wire [63:0] xrin, zrin, xrout, zrout;
    wire [63:0] greg, hreg;
    
    //register Int64 greg, hreg
    //greg = g
    REG #(.DATAWIDTH(64)) greg1 (.d(g),.q(greg),.Clk(clk),.Rst(rst));
    //hreg = h
    REG #(.DATAWIDTH(64)) hreg2 (.d(h),.q(hreg),.Clk(clk),.Rst(rst));
    //x = xrin
    REG #(.DATAWIDTH(64)) xr (.d(xrin),.q(xrout),.Clk(clk),.Rst(rst));
    //z = zrin
    REG #(.DATAWIDTH(64)) zr (.d(zrin),.q(zrout),.Clk(clk),.Rst(rst));
    //d = a + b
    ADD #(.DATAWIDTH(64)) (.a(a),.b(b),.sum(d));
    //e = a + c
    ADD #(.DATAWIDTH(64)) (.a(a),.b(c),.sum(e));
    //f = a - b 
    SUB #(.DATAWIDTH(64)) (.a(a),.b(b),.diff(f));  
    //dEQe = d == e
    COMP #(.DATAWIDTH(64)) (.a(d),.b(e),.eq(dEQe));
    //dLTe = d < e
    COMP #(.DATAWIDTH(64)) (.a(d),.b(e),.lt(dLTe));
    //g = dLTe ? d : e 
    MUX2x1 #(.DATAWIDTH(64)) (.a(d),.b(e),.d(g),.sel(dLTe));
    //h = dEQe ? g : f 
    MUX2x1 #(.DATAWIDTH(64)) (.a(g),.b(f),.d(h),.sel(dEQe));
    //xrin = hreg << dLTe
    SHL #(.DATAWIDTH(64)) (.a(hreg),.d(xrin),.sh_amt(dLTe));
    //zrin = greg >> dEQe
    SHR #(.DATAWIDTH(64)) (.a(greg),.d(zrin),.sh_amt(dEQe));
    always @(*) begin
        z<=zrout;
        x<=xrout;
    end
 
endmodule
