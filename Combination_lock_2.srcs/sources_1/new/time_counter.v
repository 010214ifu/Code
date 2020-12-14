`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/12/10 00:34:45
// Design Name: 
// Module Name: time_counter
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
    input IsLock,
    input clk,
    input restart,
    input resetting,
    output reg [6:0]NixieTube,
    output reg EndTime
    );
 
reg [31:0] counter;

initial begin
    counter <= 32'd0;
    EndTime <= 0;
end

always @(posedge clk or posedge restart) begin
//if (!IsLock) begin
    if(restart && !IsLock) begin
        counter <= 32'd0;
    end
    else if (clk && !IsLock) begin
        if (counter < 32'd900_000_000) begin
            counter <= counter + 32'd1;
        end
    end
//end
end

always @(posedge clk) begin
    if (!resetting) begin
        if( counter < 32'd100_000_000 ) NixieTube <= 7'b1111011;
        else if( counter < 32'd200_000_000 ) NixieTube <= 7'b1111111;
        else if( counter < 32'd300_000_000 ) NixieTube <= 7'b1110000;
        else if( counter < 32'd400_000_000 ) NixieTube <= 7'b1011111;
        else if( counter < 32'd500_000_000 ) NixieTube <= 7'b1011011;
        else if( counter < 32'd600_000_000 ) NixieTube <= 7'b0110011;
        else if( counter < 32'd700_000_000 ) NixieTube <= 7'b1111001;
        else if( counter < 32'd800_000_000 ) NixieTube <= 7'b1101101;
        else if( counter < 32'd900_000_000 ) NixieTube <= 7'b0110000;
        else NixieTube <= 7'b1111110;
    end
    else begin
        NixieTube <= 7'b0000000;
    end
end

always @(posedge clk or posedge restart) begin
//if (!IsLock) begin
    if(restart && !IsLock) begin
        EndTime <= 0;
    end
    else if (clk && !IsLock) begin
        if (counter == 32'd900_000_000) begin
            EndTime <= 1;
        end
    end
//end
end

endmodule
