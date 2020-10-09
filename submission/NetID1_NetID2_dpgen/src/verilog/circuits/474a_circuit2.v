//`timescale 1ns / 1ns
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: Nicholas Paco
// 
// Create Date: 10/02/2020 10:54:00 AM
// Design Name: 
// Module Name: circuit2
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


module circuit2(input clk,input Rst,input [31:0]a,input[31:0]b,input[31:0]c,output reg [31:0]z,output reg [31:0]x);

wire [31:0]d,e,f,g,h;
wire dLTe,dEQe;
wire [31:0] xwire,zwire;
wire ltwire,gtwire,eqwire;

//d = a + b
//module ADD #module ADD #(parameter DATAWIDTH=2)(input [DATAWIDTH-1:0] a,input [DATAWIDTH-1:0] b,output reg [DATAWIDTH-1:0] sum)
ADD #(32)(a,b,d);

//e = a + c
//module ADD #module ADD #(parameter DATAWIDTH=2)(input [DATAWIDTH-1:0] a,input [DATAWIDTH-1:0] b,output reg [DATAWIDTH-1:0] sum)
ADD #(32)(a,c,e);

//f = a - b
//module SUB #(parameter DATAWIDTH=2)(input [DATAWIDTH-1:0] a,input [DATAWIDTH-1:0] b,output reg [DATAWIDTH-1:0] diff);
SUB #(32)(a,b,f);

//dEQe = d == e
//module COMP #(parameter DATAWIDTH = 64)(input[DATAWIDTH-1:0]a,input[DATAWIDTH-1:0]b,output reg gt,output reg lt,output reg eq);//Comparator Module
COMP #(32)(d,e,gtwire,ltwire,qEQe);

//dLTe = d < e
//module COMP #(parameter DATAWIDTH = 64)(input[DATAWIDTH-1:0]a,input[DATAWIDTH-1:0]b,output reg gt,output reg lt,output reg eq);//Comparator Module
COMP #(32)(d,e,gtwire,dLTe,eqwire);

//g = dLTe ? d : e 
//module MUX2x1 #(parameter DATAWIDTH = 64)(input[DATAWIDTH-1:0]a,input[DATAWIDTH-1:0]b,input sel,output reg [DATAWIDTH-1:0]d);//Mux Module
MUX2x1 #(32)(d,e,dLTe,g);

//h = dEQe ? g : f 
//module MUX2x1 #(parameter DATAWIDTH = 64)(input[DATAWIDTH-1:0]a,input[DATAWIDTH-1:0]b,input sel,output reg [DATAWIDTH-1:0]d);//Mux Module
MUX2x1 #(32)(g,f,dEQe,h);

//xwire = g << dLTe
//module SHL #(parameter DATAWIDTH=2)(input [DATAWIDTH-1:0] a,input [DATAWIDTH-1:0] sh_amt,output reg [DATAWIDTH-1:0] d);
SHL #(32)(g,dLTe,xwire);

//zwire = h >> dEQe
//module SHR #(parameter DATAWIDTH=2)(input [DATAWIDTH-1:0] a,input [DATAWIDTH-1:0] sh_amt,output reg [DATAWIDTH-1:0] d);
SHR #(32)(h,dEQe,zwire);

//x = xwire
//module REG #(parameter DATAWIDTH = 64)(input[DATAWIDTH-1:0]d,input Clk,input Rst,output reg [DATAWIDTH-1:0]q);//Register Module
REG #(32)(xwire,clk,Rst,xwire2);

always@(*)begin
x <= xwire2;
end

//z = zwire
//module REG #(parameter DATAWIDTH = 64)(input[DATAWIDTH-1:0]d,input Clk,input Rst,output reg [DATAWIDTH-1:0]q);//Register Module
REG #(32)(zwire,clk,Rst,zwire2);

always@(*)begin
z <= zwire2;
end

    
endmodule
