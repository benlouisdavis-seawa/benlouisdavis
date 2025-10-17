/*
	Ben Davis
	1/23/24
	EE 371
	Lab 2, Task 2
	
	This module uses a 32x4 2 port ram to scroll through all
	of the written data (read), while simultaneously writing
	data at different addresses. It uses the SW 8-4 for the
	write address and HEX 5-4 to display said address. SW 3-0
	is the input for write data, and is displayed on HEX1. It
	takes in CLOCK_50 as the clock and uses KEY0 as a reset
	button. The read data is displayed on hex 3-2.
	
*/

module DE1_SoC_task2 (CLOCK_50, SW, KEY, HEX0, HEX1, HEX2
								, HEX3, HEX4, HEX5);
	//instantiate logic variables						
	input logic CLOCK_50;
	input logic [3:0] KEY;
	input logic [9:0] SW;
	output logic [6:0] HEX0;
	output logic [6:0] HEX1;
	output logic [6:0] HEX2;
	output logic [6:0] HEX3;
	output logic [6:0] HEX4;
	output logic [6:0] HEX5;
	//intermediate logic
	logic [3:0] q;
	logic [4:0] rdaddress;
	logic [31:0] clk;
	//instantiate clock divider
	clock_divider cdiv (CLOCK_50, clk);
	//instantiate counter_31
	counter_31 scroll (.clk(clk[25]), .rst(~KEY[0]), .out(rdaddress));
	//instantiate the dual port ram
	ram32x4 ram_task2 (.clock(CLOCK_50), .data(SW[3:0]), .rdaddress(rdaddress), 
								.wraddress(SW[8:4]), .wren(~KEY[3]), .q(q));
	// start of assigning data to hex displays						
	logic [6:0] zero_hex;	
	//use of hexadecimal data to convert and update
	//from binary to hexadecimal 7bit displays
	hexadecimal zero (.in(q), .out(zero_hex));
	
	logic [6:0] read_2;
	logic [6:0] read_3;
	hex_number two (.in(rdaddress[4:0]), .out1(read_2), .out2(read_3));
	
	logic [6:0] read_1;
	hexadecimal one (.in(SW[3:0]), .out(read_1));
	
	logic [6:0] read_4;
	logic [6:0] read_5;
	hex_number four (.in(SW[8:4]), .out1(read_4), .out2(read_5));
	
	assign HEX0 = zero_hex;
	assign HEX1 = read_1;
	assign HEX2 = read_2;
	assign HEX3 = read_3;
	assign HEX4 = read_4;
	assign HEX5 = read_5;
	
endmodule 
//testbench
`timescale 1s/1ps
module DE1_SoC_task2_testbench();
	//reset logic variables
	logic CLOCK_50;
	logic [9:0] SW;
	logic [3:0] KEY;
	logic [6:0] HEX0;
	logic [6:0] HEX1;
	logic [6:0] HEX2;
	logic [6:0] HEX3;
	logic [6:0] HEX4;
	logic [6:0] HEX5;
	//instantiate the module
	DE1_SoC_task2 dut (.CLOCK_50, .SW, .KEY, .HEX0, .HEX1
								, .HEX2, .HEX3, .HEX4, .HEX5);
	//clock setup				
	parameter clock_period = 100;
	
	initial begin
		CLOCK_50 <= 0;
		forever #(clock_period/2) CLOCK_50 <= ~CLOCK_50;
	end //of clock setup
	
	//tests an instance where nothing is written, checking to
	//see if it scrolls through the read data
	initial begin
		SW[9:0] <= 10'b0; KEY[3:0] <= 4'b0; @(posedge CLOCK_50);
		SW[9:0] <= 10'b0; KEY[3:0] <= 4'b0; @(posedge CLOCK_50);
		SW[9:0] <= 10'b0; KEY[3:0] <= 4'b0; @(posedge CLOCK_50);
		SW[9:0] <= 10'b0; KEY[3:0] <= 4'b0; @(posedge CLOCK_50);
		SW[9:0] <= 10'b0; KEY[3:0] <= 4'b0; @(posedge CLOCK_50);
		SW[9:0] <= 10'b0; KEY[3:0] <= 4'b0; @(posedge CLOCK_50);
		$stop;
	end 
endmodule 