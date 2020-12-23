`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/12/17 16:51:52
// Design Name: 
// Module Name: Time_Counter
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


module time_counter(
    input            IsLock,     // 是否上锁
    input            clk,        // 时钟信号
    input            restart,    // 重新开始信号
    input            resetting,  // 重置密码信号
    output reg [6:0] NixieTube,  // 输出七段数码管
    output reg       EndTime     // 倒计时结束
    );
 
reg [31:0] counter;
initial begin
    counter <= 32'd0;
    EndTime <= 0;
end
// 使用自带的100MHz的信号，每100_000_000表示一秒
// 设倒计时有10秒
always @(posedge clk or posedge restart) begin
    if((restart && !IsLock)||resetting) begin
        counter <= 32'd0;
    end
    else if (clk && !IsLock) begin
        if (counter < 32'd900_000_000) begin
            counter <= counter + 32'd1;
        end
    end
end

always @(posedge clk) begin
    if (!resetting) begin
        if ( counter < 32'd100_000_000 ) NixieTube <= 7'b1111011;
        else if ( counter < 32'd200_000_000 ) NixieTube <= 7'b1111111;
        else if ( counter < 32'd300_000_000 ) NixieTube <= 7'b1110000;
        else if ( counter < 32'd400_000_000 ) NixieTube <= 7'b1011111;
        else if ( counter < 32'd500_000_000 ) NixieTube <= 7'b1011011;
        else if ( counter < 32'd600_000_000 ) NixieTube <= 7'b0110011;
        else if ( counter < 32'd700_000_000 ) NixieTube <= 7'b1111001;
        else if ( counter < 32'd800_000_000 ) NixieTube <= 7'b1101101;
        else if ( counter < 32'd900_000_000 ) NixieTube <= 7'b0110000;
        else NixieTube <= 7'b1111110;
    end
    else NixieTube <= 7'b0000000;
end
// counter达到900_000_000时，倒计时结束
always @(posedge clk) begin
    if (counter == 32'd900_000_000) begin
        EndTime <= 1;
    end
    else begin
        EndTime <= 0;
    end
end
endmodule
