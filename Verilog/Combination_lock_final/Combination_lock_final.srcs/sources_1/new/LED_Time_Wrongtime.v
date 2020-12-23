`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/12/17 16:51:52
// Design Name: 
// Module Name: LED_Time_Wrongtime
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


module LED_Time_Wrongtime(
    input            clk,             // 时钟信号
    input            clr,             // 重置清楚信号
    input            right,           // 密码正确
    input            wrong,           // 密码错误
    input            IsResetting,     // 正在重置密码
    input      [1:0] DN0_K,           // 倒计时和显示错误次数的扫描信号
    input      [6:0] temp_led_time,   // 倒计时输入
    output reg [6:0] LED_time,        // 输出倒计时和错误次数频闪
    output reg       not_work         // 错误次数达三次，不再工作
    );

reg [1:0]NumWrong;
reg [6:0]NumWrong_NixieTube;
initial begin
    not_work <= 0;
    NumWrong <= 0;
    NumWrong_NixieTube <= 7'b1111110;
end

always @(posedge clk) begin
    // 错误次数与数码管显示对应关系
    case (NumWrong)
        2'b00: NumWrong_NixieTube <= 7'b1111110;
        2'b01: NumWrong_NixieTube <= 7'b0110000;
        2'b10: NumWrong_NixieTube <= 7'b1101101;
        2'b11: NumWrong_NixieTube <= 7'b1111001;
        default: NumWrong_NixieTube <= 7'b0000001; 
    endcase
    not_work = (NumWrong == 2'b11);
end

always @(DN0_K) begin
    // 频闪信号与输出的倒计时和错误次数对应
    if (not_work) LED_time <= 0;
    else begin
        case(DN0_K)
            2'b10: LED_time <= temp_led_time;
            2'b01: LED_time <= NumWrong_NixieTube;
            default: LED_time <= 7'b0000001;
        endcase
    end
end
// 输入错误则错误次数加一
// 错误次数清零情况：输入正确、清理、修改密码
always @(posedge right or posedge wrong or posedge clr or posedge IsResetting) begin
    if (right || clr || IsResetting) NumWrong <= 0;
    else if(wrong) NumWrong <= NumWrong + 2'b1;
end
endmodule
