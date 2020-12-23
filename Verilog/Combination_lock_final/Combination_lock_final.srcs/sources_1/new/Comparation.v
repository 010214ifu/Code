`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/12/17 16:51:52
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
    input             clk,               // 时钟信号
    input             restart,           // 重新开始
    input      [31:0] my_password,       // 输入的密码
    input      [31:0] correct_password,  // 正确的密码
    output reg        IsRight            // 是否正确
    );

initial begin IsRight <= 0; end

always @(posedge clk or posedge restart) begin
    // 若重新开始，密码置为未输入，则此时错误
    if (restart) IsRight <= 0;
    // restart的优先级比clk要高
    else if(clk) begin
    // 密码正确则IsRight为1，否在为0
        if (my_password == correct_password) begin
            IsRight <= 1;
        end
        else if (my_password != correct_password) begin
            IsRight <= 0;
        end
    end
end
endmodule
