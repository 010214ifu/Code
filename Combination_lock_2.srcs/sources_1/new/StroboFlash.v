`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/12/09 17:40:02
// Design Name: 
// Module Name: StroboFlash
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


 
module StroboFlash(
    input clk,
    output reg [3:0]DN1_K,
    output reg [1:0]DN0_K
    );
reg [31:0] counter_hz;

initial
    begin
        counter_hz <= 32'd0;
    end

always @(posedge clk)                                                          
    begin
        if (counter_hz == 32'd400_000)
            counter_hz <= 32'd0;                                                                                                                                                                        
        else
            counter_hz <= counter_hz + 32'd1;
    end
always @(posedge clk)
    begin
        if (counter_hz < 32'd100_000) begin
            DN1_K <= 4'b1000;
            DN0_K <= 2'b10;
        end 
        else if (counter_hz < 32'd200_000) begin
            DN1_K <= 4'b0100;
            DN0_K <= 2'b01;
        end 
        else if (counter_hz < 32'd300_000) begin
            DN1_K <= 4'b0010;
            DN0_K <= 2'b10;
        end 
        else  begin
            DN1_K <= 4'b0001;
            DN0_K <= 2'b01;
        end 
        // else if (counter_hz < 32'd200_000) DN1_K <= 4'b0100;
        // else if (counter_hz < 32'd300_000) DN1_K <= 4'b0010;
        // else DN1_K <= 4'b0001;
    end

endmodule
