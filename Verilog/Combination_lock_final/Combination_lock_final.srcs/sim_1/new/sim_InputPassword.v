`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

module sim_InputPassword( );
reg IsLock, TimeEnd, IsResetting, restart;
reg [7:0]password;
reg [7:0]temp_password;
wire a,b,c,d;
wire [31:0]my_password;
initial begin
    IsLock = 0;
    TimeEnd = 0;
    IsResetting = 0;
    restart = 0;
    password = 8'b00000000;
    temp_password = 8'b10000000;
end
always #1 begin
    if (password == 0) password = temp_password;
    else password = 0;
end
always #2 begin
    if (temp_password == 8'b00000001)
        temp_password = 8'b10000000;
    else temp_password = password >> 1;
end
always #16 restart = ~restart;
always #32 IsResetting = ~IsResetting;
always #64 TimeEnd = ~TimeEnd;
always #128 IsLock = ~IsLock;
Input_Password ip(IsLock, TimeEnd, IsResetting,restart, 
                    password,{a,b,c,d},my_password);
endmodule
