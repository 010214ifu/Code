`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
module sim_LED_Time_Wrongtime( );
reg clk;
reg clr;
reg right;
reg wrong;
reg IsResetting;
reg [1:0]DN0_K;
reg [6:0]temp_led_time;
wire [6:0]LED_time;
wire not_work;

initial begin
    clk = 0;
    clr = 0;
    right = 0;
    wrong = 0;
    IsResetting = 0;
    DN0_K = 2'b10;
    temp_led_time = 7'b1111111;
end
always #1 clk = ~clk;
always #4
    if (DN0_K == 2'b10) DN0_K = 2'b01;
    else DN0_K = 2'b10;
always #8 {right,wrong,IsResetting} = {right,wrong,IsResetting} + 1;
LED_Time_Wrongtime ltw(clk,clr,right,wrong,IsResetting,DN0_K,
                        temp_led_time,LED_time,not_work);
endmodule
