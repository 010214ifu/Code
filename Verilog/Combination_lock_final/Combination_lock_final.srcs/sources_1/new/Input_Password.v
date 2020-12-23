`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/12/17 16:51:52
// Design Name: 
// Module Name: Input_Password
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


module Input_Password(
    input             IsLock,        // 是否上锁
    input             TimeEnd,       // 倒计时结束
    input             IsResetting,   // 是否在重置密码
    input             restart,       // 重新开始
    input      [7:0]  password,      // 输入密码
    output reg [3:0]  ChooseChange,  // 选择改变的位数
    output reg [31:0] my_password    // 输入后的密码
    );

// 检测八位之一是否有输入，且只能有一个输入
wire sumpassword;
assign sumpassword = password[0]||password[1]||password[2]||password[3]||
        password[4]||password[5]||password[6]||password[7];
// 初始改变位数设置为第一位，初始设为没有密码输入
initial begin
    ChooseChange <= 4'b1000;
    my_password <= 0;
end

always @(posedge sumpassword or posedge restart or posedge IsResetting) begin
    // 若重新开始或者重置密码，则输入后的密码置为未输入
    if (restart || IsResetting) begin
        my_password <= 0;
        ChooseChange <= 4'b1000;
    end
    // 在可以输入的情况下，循环右移输入密码
    // 可输入情况：没有上锁，倒计时没有结束，没有在输入密码
    else if (sumpassword && !IsLock && !TimeEnd && !IsResetting) begin
        if (ChooseChange == 4'b1000) begin
            my_password[31:24] <= password;
            ChooseChange <= ChooseChange >> 1;
        end
        else if(ChooseChange == 4'b0100) begin
            my_password[23:16] <= password;
            ChooseChange <= ChooseChange >> 1;
        end
        else if(ChooseChange == 4'b0010) begin
            my_password[15:8] <= password;
            ChooseChange <= ChooseChange >> 1;
        end
        else if(ChooseChange == 4'b0001) begin
            my_password[7:0] <= password;
            ChooseChange <= 4'b1000;
        end
    end
end
endmodule
