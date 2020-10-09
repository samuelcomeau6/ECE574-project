//`timescale 1ns / 1ns
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: Nicholas Paco
// 
// Create Date: 10/02/2020 10:54:00 AM
// Design Name: 
// Module Name: circuit1
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


module circuit1(input clk,input rst,input [7:0]a,input[7:0]b,input[7:0]c,output reg [7:0]z,output reg [15:0]x);

wire [7:0]d;
wire [7:0]e;
wire [7:0]f;
wire  g;
wire [15:0] xwire;
wire [15:0] xwire2;
wire ltwire;
wire eqwire;
wire [7:0] zwire;

//d = a + b
//module ADD #module ADD #(parameter DATAWIDTH=2)(input [DATAWIDTH-1:0] a,input [DATAWIDTH-1:0] b,output reg [DATAWIDTH-1:0] sum)
ADD #(8) u_add1 (a,b,d);

//e = a + c
//module ADD #module ADD #(parameter DATAWIDTH=2)(input [DATAWIDTH-1:0] a,input [DATAWIDTH-1:0] b,output reg [DATAWIDTH-1:0] sum)
ADD #(8) u_add2 (a,c,e);

//g = d > e
//module COMP #(parameter DATAWIDTH = 64)(input[DATAWIDTH-1:0]a,input[DATAWIDTH-1:0]b,output reg gt,output reg lt,output reg eq);//Comparator Module
COMP #(8) u_comp1 (d,e,g,ltwire,eqwire);

//z = g ? d : e
//module MUX2x1 #(parameter DATAWIDTH = 64)(input[DATAWIDTH-1:0]a,input[DATAWIDTH-1:0]b,input sel,output reg [DATAWIDTH-1:0]d);//Mux Module
MUX2x1 #(8) u_mux1 (d,e,g,zwire);

always@(*)begin
z <= zwire;
end

//f = a * c
//module MUL #(parameter DATAWIDTH = 64)(input [DATAWIDTH-1:0]a,input [DATAWIDTH-1:0]b,output reg [DATAWIDTH-1:0]prod);//Multiplier Module
MUL #(8) u_mul1 (a,c,f);

//xwire = f - d
//module SUB #(parameter DATAWIDTH=2)(input [DATAWIDTH-1:0] a,input [DATAWIDTH-1:0] b,output reg [DATAWIDTH-1:0] diff);
SUB #(16) u_sub1 ({8'b0,f},{8'b0,d},xwire);

//x = xwire
//module REG #(parameter DATAWIDTH = 64)(input[DATAWIDTH-1:0]d,input Clk,input Rst,output reg [DATAWIDTH-1:0]q);//Register Module
REG #(16) u_reg1 (xwire,clk,rst,xwire2);

always@(*)begin
x <= xwire2;
end

    
endmodule


