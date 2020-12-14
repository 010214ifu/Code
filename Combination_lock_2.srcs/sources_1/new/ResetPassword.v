`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/12/10 22:04:23
// Design Name: 
// Module Name: ResetPassword
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


module ResetPassword(
    // input clr,
    input reset,
    input [7:0]RePassword,
    output reg [31:0]NewPassword,
    output reg seted
    );

reg [1:0]setting;

initial begin
    seted <= 1'b0;
    setting <= 2'b00;
end

always @(posedge reset) begin
    if (!seted) begin
        if (setting == 2'b00) begin
            NewPassword[31:24] <= RePassword;
            setting <= setting + 1;
        end
        else if(setting == 2'b01) begin
            NewPassword[23:16] <= RePassword;
            setting <= setting + 1;
        end
        else if(setting == 2'b10) begin
            NewPassword[15:8] <= RePassword;
            setting <= setting + 1;
        end
        else if(setting == 2'b11) begin
            NewPassword[8:0] <= RePassword;
            seted <= 1'b1;
        end
    end
end

endmodule
