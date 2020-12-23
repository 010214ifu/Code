`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/12/17 16:51:52
// Design Name: 
// Module Name: ChangePassword
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


module PasswordChange(
    input             IsResetting,    // 1处于正修改密码状态，0相反
    input             IsLock,         // 1表示上锁，无法输入
    input             not_work,       // 1表示密码错误3次，不再工作
    input      [7:0]  password,       // 输入的密码
    output reg [3:0]  ChangePassword, // 选择的修改位数
    output reg [31:0] NewPassword     // 得到的新密码
    );
// 检测输入八位之一是否有输入
wire sumpassword;
assign sumpassword = password[0]||password[1]||password[2]||password[3]||
        password[4]||password[5]||password[6]||password[7];

initial begin
    ChangePassword <= 4'b1000;
    NewPassword <= 32'b00000010_00000010_00000010_00000010;
end

// 检测到拨动开关有变化
// 状态处于正在修改密码
// 循环移动输入来对新密码赋值
// 所赋的值为拨动开关的输入
always @(posedge sumpassword) begin
    if (IsResetting && !IsLock && !not_work) begin
    // 降序从31开始，每八位表示一个密码
        if (ChangePassword == 4'b1000) begin
            NewPassword[31:24] <= password;
            ChangePassword <= ChangePassword >> 1;
        end
        else if(ChangePassword == 4'b0100) begin
            NewPassword[23:16] <= password;
            ChangePassword <= ChangePassword >> 1;
        end
        else if(ChangePassword == 4'b0010) begin
            NewPassword[15:8] <= password;
            ChangePassword <= ChangePassword >> 1;
        end
        else if(ChangePassword == 4'b0001) begin
            NewPassword[7:0] <= password;
            ChangePassword <= 4'b1000;
        end
    end
end
endmodule