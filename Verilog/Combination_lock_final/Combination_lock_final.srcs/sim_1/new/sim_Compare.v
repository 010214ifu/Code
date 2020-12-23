`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

module sim_Compare( );
reg clk,restart;
reg [31:0]my_password;
reg[31:0]correct_password;
wire IsRight;
initial begin
    clk = 0;
    restart = 0;
    correct_password = 32'b00000010_00000010_00000010_00000010;
    my_password = 32'b10000000_10000000_10000000_10000000;
end
always #1 clk = ~clk;
always #16 begin
    if (my_password == 32'b00000001_00000001_00000001_00000001)
        my_password = 32'b10000000_10000000_10000000_10000000;
    else my_password = my_password >> 1;
end
always #8 restart = ~restart;
Comparation c(clk,restart,my_password,correct_password,IsRight);
endmodule
