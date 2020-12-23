`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/12/17 16:51:52
// Design Name: 
// Module Name: LED_Password
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


module LED_Password(
    input            clk,              // 时钟信号
    input            not_work,         // 错误三次不工作信号
    input            TimeEnd,          // 倒计时结束
    input            IsResetting,      // 重置密码信号
    input            right,            // 正确
    input            wrong,            // 错误
    input      [3:0] DN1_K,            // 密码显示分频信号
    input      [3:0] ChooseChange,     // 选择输入位数
    input      [3:0] ChangePassword,   // 选择修改位数
    input      [6:0] led_1,            // 第1个七段数码管显示内容
    input      [6:0] led_2,            // 第2个七段数码管显示内容
    input      [6:0] led_3,            // 第3个七段数码管显示内容
    input      [6:0] led_4,            // 第4个七段数码管显示内容
    output reg [6:0] LED,              // 数码管频闪内容
    output reg       DP                // 小数点
    );

initial begin DP <= 0; end
always @(posedge clk) begin
    // 错误三次，数码管不再显示
    if (not_work) begin
        LED <= 0;
        DP <= 0;
    end
    // 倒计时未结束，则显示输入的密码/更改中的密码
    // 4个led在PasswordToNum模块进行赋值
    else if (!TimeEnd || IsResetting) begin
    // 倒计时未结束显示正输入的密码，修改密码过程显示正修改的密码
        case(DN1_K)
            4'b1000: LED <= led_1;
            4'b0100: LED <= led_2;
            4'b0010: LED <= led_3;
            4'b0001: LED <= led_4;
            default: LED <= 7'b1001001;
        endcase
        // 小数点随变频进行频闪
        if (ChangePassword == DN1_K && IsResetting) DP <= 1;
        else if(ChooseChange == DN1_K && !IsResetting) DP <= 1;
        else DP <= 0;
    end
    // 正确，数码管显示OPEN
    else if(right) begin
        case(DN1_K)
            4'b1000: LED <= 7'b1111110;
            4'b0100: LED <= 7'b1100111;
            4'b0010: LED <= 7'b1001111;
            4'b0001: LED <= 7'b1110110;
            default: LED <= 7'b0000001;
        endcase
        DP <= 0;
    end
    // 错误，数码管显示EROR
    else if(wrong) begin
        case(DN1_K)
            4'b1000: LED <= 7'b1001111;
            4'b0100: LED <= 7'b1000110;
            4'b0010: LED <= 7'b1111110;
            4'b0001: LED <= 7'b1000110;
            default: LED <= 7'b0000001;
        endcase
        DP <= 0;
    end
end
endmodule