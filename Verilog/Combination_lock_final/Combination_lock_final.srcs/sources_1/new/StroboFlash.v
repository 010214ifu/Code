`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/12/17 16:51:52
// Design Name: 
// Module Name: StroboFlash
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


module StroboFlash #(parameter WIDTH = 16)
(
    input            clk,    //时钟信号
    output reg [3:0] DN1_K,  //密码显示的频闪选择
    output reg [1:0] DN0_K   //倒计时和错误次数的频闪
);

reg [WIDTH-1:0]counter;
initial begin
    counter <= 0;
    DN1_K <= 4'b1000;
    DN0_K <= 2'b10;
end
//时钟上升沿counter加一
always @(posedge clk) counter <= counter +1;
//每当counter最高位有一个上升沿，DN0_K和DN1_K右循环移动一位
always @(posedge counter[WIDTH-1]) begin
    if (DN1_K == 4'b0001)  DN1_K <= 4'b1000;
    else DN1_K <= DN1_K >> 1;
    if (DN0_K == 2'b10)  DN0_K <= 2'b01;
    else DN0_K <= 2'b10;
end
endmodule
