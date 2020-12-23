`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
module sim_Right_Wrong( );
reg clk;
reg restart;
reg IsResetting;
reg not_work;
reg isopen;
reg TimeEnd;
wire right;
wire wrong;
initial begin
    clk = 0;
    restart = 0;
    IsResetting = 0;
    not_work = 0;
    isopen = 0;
    TimeEnd = 0;
end
always #1 clk = ~clk;
always #4 {restart, IsResetting, not_work,isopen, TimeEnd}
            = {restart, IsResetting, not_work, isopen, TimeEnd} + 1;
Right_Wrong rw(clk,restart,IsResetting,not_work,isopen,TimeEnd,right,wrong);
endmodule
