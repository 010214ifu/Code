`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/12/14 23:28:04
// Design Name: 
// Module Name: Right_Wrong
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


module Right_Wrong(
    input      clk,          // 时钟信号
    input      restart,      // 重新开始信号
    input      IsResetting,  // 重置密码信号
    input      not_work,     // 错误三次，不再工作
    input      isopen,       // 是否打开，Comparation信号
    input      TimeEnd,      // 倒计时结束
    output reg right,        // 输出正确信号
    output reg wrong         // 输出错误信号
    );

initial begin
    right <= 0;
    wrong <= 0;
end

always @(posedge clk or posedge restart) begin
    // 重置，未知正确与否
    if(restart || IsResetting || not_work) begin
        wrong <= 0;
        right <= 0;
    end
    else if (clk) begin
        if(!isopen && TimeEnd) begin
            wrong <= 1;
            right <= 0;
        end 
        else if(isopen && TimeEnd) begin
            wrong <= 0;
            right <= 1;
        end 
    end
end

endmodule
