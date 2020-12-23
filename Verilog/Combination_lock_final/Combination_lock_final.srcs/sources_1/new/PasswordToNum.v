`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/12/17 16:51:52
// Design Name: 
// Module Name: PasswordToNum
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


module PasswordToNum(
    input             clk,                 // 时钟信号
    input             resetting,           // 重置密码信号
    input  wire [7:0] password,            // 输入密码
    input  wire [7:0] password_resetting,  // 重置密码过程输入
    output reg  [6:0] led
    );

reg [7:0]p;
initial begin
    led <= 8'b0000001;
    p <= 0;
end
// 寄存器p，当重置密码时显示重置输入，否则显示密码输入
always @(posedge clk) begin
    if (!resetting) p <= password;
    else p <= password_resetting;
end
// 密码与LED的对应关系
always @(posedge clk) begin
    case(p)
        8'b10000000: led <= 8'b1111110;
        8'b01000000: led <= 8'b0110000;
        8'b00100000: led <= 8'b1101101;
        8'b00010000: led <= 8'b1111001;
        8'b00001000: led <= 8'b0110011;
        8'b00000100: led <= 8'b1011011;
        8'b00000010: led <= 8'b1011111;
        8'b00000001: led <= 8'b1110000;
        default: led <= 8'b0000001;
    endcase
end
endmodule
