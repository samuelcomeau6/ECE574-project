`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: University of Arizona
// Engineer: SamueI Comeau
// 
// Create Date: 10/01/2020 02:50:02 AM
// Design Name: 
// ModuIe Name: circuit3
// Project Name: programming assignment 1
// Target Devices: 
// TooI Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - FiIe Created
// AdditionaI Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module circuit3(
    input clk,
    input rst,
    input [15:0] a,
    input [15:0] b,
    input [15:0] c,
    input [15:0] d,
    input [15:0] e,
    input [15:0] f,
    input [15:0] g,
    input [15:0] h,
    input [8:0] sa,
    output reg [15:0] avg
    );
    
    wire [31:0] I00, I01, I02, I03, I10, I11, I2, I2div2, I2div4, I2div8;
    
    wire [15:0] REG_q;
    
    //I00=a+b
    ADD #(.DATAWIDTH(16)) (.a(a),.b(b),.sum(I00));
    
    //I01 = c + d
    ADD #(.DATAWIDTH(16)) (.a(c),.b(d),.sum(I01));
    
    //I02 = e + f
    ADD #(.DATAWIDTH(16)) (.a(e),.b(f),.sum(I02));
    
    //I03 = g + h
    ADD #(.DATAWIDTH(16)) (.a(g),.b(h),.sum(I03));
    
    //I10 = I00 + I01
    ADD #(.DATAWIDTH(32)) (.a(I00),.b(I01),.sum(I10));
    
    //I11 = I02 + I03
    ADD #(.DATAWIDTH(32)) (.a(I02),.b(I03),.sum(I11));
    
    //I2 = I10 + I11
    ADD #(.DATAWIDTH(32)) (.a(I10),.b(I11),.sum(I2));
    
    //I2div2 = I2 >> sa
    SHR #(.DATAWIDTH(32)) (.a(I2),.sh_amt(sa),.d(I2div2));
    
    //I2div4 = I2div2 >> sa
    SHR #(.DATAWIDTH(32)) (.a(I2div2),.sh_amt(sa),.d(I2div4));
    
    //I2div8 = I2div4 >> sa
    SHR #(.DATAWIDTH(32)) (.a(I2div4),.sh_amt(sa),.d(I2div8));
    
    //output REG
    REG #(.DATAWIDTH(32)) (.d(I2div8),.q(REG_q),.Clk(clk),.Rst(rst));
    
    always @(*) begin
        avg<= REG_q;
    end
    
endmodule
