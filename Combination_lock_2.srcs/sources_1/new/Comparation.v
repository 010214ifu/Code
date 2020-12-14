`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/12/10 22:02:18
// Design Name: 
// Module Name: Comparation
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


module Comparation(
    input clk,
    input restart,
    input [31:0]password,
    input [31:0]correct,
    output reg IsRight
    );

initial begin
    IsRight <= 0;
end

always @(posedge clk or posedge restart) begin
if (restart) IsRight <= 0;
else if(clk) begin
    if (password == correct) begin
        IsRight <= 1;
    end
    else if (password != correct) begin
        IsRight <= 0;
    end
end
    // if (clk && !restart) begin
    //     if (password == correct) begin
    //         IsRight <= 1;
    //     end
    // end
    // else if(restart) begin
    //     IsRight <= 0;
    // end
end

endmodule
