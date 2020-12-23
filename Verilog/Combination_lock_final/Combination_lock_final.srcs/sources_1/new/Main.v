`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/12/17 16:51:52
// Design Name: 
// Module Name: Main
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


module Main(
    input      [7:0] password,            // 输入
    input            reset,               // 重置密码
    input            clk,                 // 时钟信号
    input            Lock,                // 上锁
    input            restart,             // 再来一次
    input            clr,                 // 清除全部
    output reg [6:0] LED_time_wrongtime,  // 显示倒计时和错误次数
    output reg [6:0] LED,                 // 显示输入密码
    output reg [3:0] DN1_K,               // 选择频闪
    output reg [1:0] DN0_K,               // 选择频闪
    output reg       DP,                  // 小数点
    output reg       IsLock,              // 上锁灯亮
    output reg       right,               // 正确灯亮
    output reg       wrong,               // 错误灯亮
    output reg       resetting            // 重置密码灯亮
);

// 中间变量，有时输出无法用于模块衔接，有时需要增加几个中间变量
wire [31:0] correct_password;
wire [31:0] my_password;
wire [6:0]  led_1;
wire [6:0]  led_2;
wire [6:0]  led_3;
wire [6:0]  led_4;
wire [3:0]  ChooseChange;
wire [3:0]  ChangePassword;
wire        TimeEnd;
wire        isopen;
wire        not_work;
wire [6:0]  temp_led_time;
wire [6:0]  temp_led_time_wrongtime;
wire [3:0]  temp_DN1_K;
wire [1:0]  temp_DN0_K;
wire [6:0]  temp_LED;
wire        temp_DP;
wire        temp_right;
wire        temp_wrong;

initial begin
    IsLock <= 1;
    resetting <= 0;
end

always @(posedge Lock) IsLock <= ~IsLock;
always @(posedge reset) resetting <= ~resetting;

Comparation        com(clk, restart, my_password, correct_password, isopen);
time_counter       tc(IsLock, clk, restart, resetting, temp_led_time, TimeEnd);
StroboFlash        strobo(clk, temp_DN1_K, temp_DN0_K);
PasswordToNum      v1(clk, resetting, my_password[31:24], correct_password[31:24], led_1);
PasswordToNum      v2(clk, resetting, my_password[23:16], correct_password[23:16], led_2);
PasswordToNum      v3(clk, resetting, my_password[15:8],  correct_password[15:8],  led_3);
PasswordToNum      v4(clk, resetting, my_password[7:0],   correct_password[7:0],   led_4);
PasswordChange     ch(resetting, IsLock, not_work, password, ChangePassword, correct_password);
Input_Password     ip(IsLock, TimeEnd, resetting, restart, password, ChooseChange, my_password);
LED_Password       lp(clk, not_work, TimeEnd, resetting, right, wrong, DN1_K, ChooseChange,
                      ChangePassword, led_1, led_2, led_3, led_4, temp_LED, temp_DP);
LED_Time_Wrongtime ltw(clk, clr, right, wrong, resetting, DN0_K, temp_led_time, temp_led_time_wrongtime, not_work);
Right_Wrong        rw(clk, restart, resetting, not_work, isopen, TimeEnd, temp_right, temp_wrong);

always @(posedge clk) begin
    DN1_K <= temp_DN1_K;
    DN0_K <= temp_DN0_K;
    LED <= temp_LED;
    DP <= temp_DP;
    LED_time_wrongtime <= temp_led_time_wrongtime;
    right <= temp_right;
    wrong <= temp_wrong;
end
endmodule