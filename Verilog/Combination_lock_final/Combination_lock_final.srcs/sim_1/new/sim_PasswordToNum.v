`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

module sim_PasswordToNum( );
reg clk;
reg resetting;
reg [7:0]password;
reg [7:0]password_resetting;
wire [6:0]led;
initial begin
    clk = 0;
    resetting = 0;
    password = 8'b10000000;
    password_resetting = 8'b00010000;
end

always #1 clk = ~clk;
always #2 begin
    if (password == 8'b00000001)
        password = 8'b10000000;
    else password = password >> 1;
end
always #2 begin
    if (password_resetting == 8'b00000001)
        password_resetting = 8'b10000000;
    else password_resetting = password_resetting >> 1;
end
always #16 resetting = ~resetting;
PasswordToNum p(clk,resetting,password,password_resetting,led);
endmodule
