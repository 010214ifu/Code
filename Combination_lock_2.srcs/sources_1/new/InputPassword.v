`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/12/08 22:35:36
// Design Name: 
// Module Name: InputPassword
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

module InputPassword(password, reset, clk, Lock,
LED, LED_time, DN1_K, DN0_K, OK, open, DP, restart, locking, right, wrong, resetting, clr);

input [7:0]password;
input reset;
input clk;
input Lock;
input OK;
input restart;
input clr;
output reg [6:0]LED_time;
output reg [6:0]LED;
output reg [3:0]DN1_K;
output reg [1:0]DN0_K;
output reg open;
output reg DP;
output reg locking;
output reg right;
output reg wrong;
output reg resetting;

reg [7:0]password_1;
reg [7:0]password_2;
reg [7:0]password_3;
reg [7:0]password_4;
reg [7:0]pswd_1;
reg [7:0]pswd_2;
reg [7:0]pswd_3;
reg [7:0]pswd_4;

wire [6:0]temp_led_time;
wire [3:0]temp_DN1_K;
wire [1:0]temp_DN0_K;
wire [6:0]led_1;
wire [6:0]led_2;
wire [6:0]led_3;
wire [6:0]led_4;
reg [3:0]ChooseChange;
reg [3:0]ChangePassword;
wire TimeEnd;
wire isopen;
reg IsLock;
reg changed;
reg IsResetting;
reg [1:0]NumWrong;
wire sumpassword;
reg [6:0]NumWrong_NixieTube;

wire not_work;

assign not_work = (NumWrong == 2'b11);

initial begin
    password_1 <= 8'b00000000;
    password_2 <= 8'b00000000;
    password_3 <= 8'b00000000;
    password_4 <= 8'b00000000;
    pswd_1 <= 8'b00000010;
    pswd_2 <= 8'b00000010;
    pswd_3 <= 8'b00000010;
    pswd_4 <= 8'b00000010;
    ChooseChange <= 4'b1000;
    ChangePassword <= 4'b1000;
    DN1_K <= 4'b1000;
    DN0_K <= 2'b10;
    DP <= 0;
    IsLock <= 1;
    locking <= 1;
    right <= 0;
    wrong <= 0;
    changed <= 0;
    resetting <= 0;
    IsResetting <= 0;
    NumWrong <= 0;
    NumWrong_NixieTube <= 7'b1111110;
end

assign sumpassword = password[0]||password[1]||password[2]||password[3]||
        password[4]||password[5]||password[6]||password[7];

Comparation com(clk, restart,{password_1,password_2,password_3,password_4},
                {pswd_1,pswd_2,pswd_3,pswd_4},isopen);
time_counter t(IsLock, clk, restart, resetting, temp_led_time, TimeEnd);
StroboFlash strobo(clk, temp_DN1_K, temp_DN0_K);
PasswordToNum v1(clk, resetting, password_1, pswd_1, led_1);
PasswordToNum v2(clk, resetting, password_2, pswd_2, led_2);
PasswordToNum v3(clk, resetting, password_3, pswd_3, led_3);
PasswordToNum v4(clk, resetting, password_4, pswd_4, led_4);

always @(posedge clk) begin
    case (NumWrong)
        2'b00: NumWrong_NixieTube <= 7'b1111110;
        2'b01: NumWrong_NixieTube <= 7'b0110000;
        2'b10: NumWrong_NixieTube <= 7'b1101101;
        2'b11: NumWrong_NixieTube <= 7'b1111001;
        default: NumWrong_NixieTube <= 7'b0000001; 
    endcase
end

always @(posedge reset) begin
    IsResetting <= ~IsResetting;
    resetting <= ~resetting;
end

always @(posedge sumpassword) begin
    if (IsResetting && !IsLock && !not_work) begin
        if (ChangePassword == 4'b1000) begin
            pswd_1 <= password;
            ChangePassword <= ChangePassword >> 1;
        end
        else if(ChangePassword == 4'b0100) begin
            pswd_2 <= password;
            ChangePassword <= ChangePassword >> 1;
        end
        else if(ChangePassword == 4'b0010) begin
            pswd_3 <= password;
            ChangePassword <= ChangePassword >> 1;
        end
        else if(ChangePassword == 4'b0001) begin
            pswd_4 <= password;
            ChangePassword <= 4'b1000;
        end
    end
end


always @(posedge Lock) begin
        IsLock <= ~IsLock;
        locking <= ~locking;
end

always @(DN0_K) begin
    if (not_work) begin
        LED_time <= 0;
    end
    else begin
        case(DN0_K)
            2'b10: LED_time <= temp_led_time;
            2'b01: LED_time <= NumWrong_NixieTube;
            default: LED_time <= 7'b0000001;
        endcase
    end
    
end

always @(posedge clk) begin
    DN1_K <= temp_DN1_K;
    DN0_K <= temp_DN0_K;
    open <= isopen;
end

always @(posedge clk or posedge restart) begin
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

always @(posedge right or posedge wrong or posedge clr) begin
    if (right || clr) begin
        NumWrong <= 0;
    end
    else if(wrong) begin
        NumWrong <= NumWrong + 2'b1;
    end
end

always @(posedge clk) begin
    if (not_work) begin
        LED <= 0;
        DP <= 0;
    end
    else if (!TimeEnd) begin
        case(DN1_K)
            4'b1000: LED <= led_1;
            4'b0100: LED <= led_2;
            4'b0010: LED <= led_3;
            4'b0001: LED <= led_4;
            default: LED <= 7'b1001001;
        endcase
        if (ChangePassword == DN1_K && IsResetting) DP <= 1;
        else if(ChooseChange == DN1_K && !IsResetting) DP <= 1;
        else DP <= 0;
    end
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

always @(posedge sumpassword or posedge restart) begin
    if (restart) begin
        password_1 <= 0;
        password_2 <= 0;
        password_3 <= 0;
        password_4 <= 0;
        ChooseChange <= 4'b1000;
    end
    else if (sumpassword && !IsLock && !TimeEnd && !IsResetting) begin
        if (ChooseChange == 4'b1000) begin
            password_1 <= password;
            ChooseChange <= ChooseChange >> 1;
        end
        else if(ChooseChange == 4'b0100) begin
            password_2 <= password;
            ChooseChange <= ChooseChange >> 1;
        end
        else if(ChooseChange == 4'b0010) begin
            password_3 <= password;
            ChooseChange <= ChooseChange >> 1;
        end
        else if(ChooseChange == 4'b0001) begin
            password_4 <= password;
            ChooseChange <= 4'b1000;
        end
    end
end
endmodule
