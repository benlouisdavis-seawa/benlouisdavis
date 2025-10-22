/*
	Ben Davis
	1/23/24
	EE371
	Lab2, Task 3
	
	This module implements a FIFO RAM. It takes in a depth and 
	width parameters.  For inputs, it has clk, reset, write, 
	read, and inputBus -- for input data. It has the outputs
	empty, full, and outputBus. This allows it to write data
	into the RAM, and then tells it what address to read it from,
	in a first in first out order.
	
*/

module FIFO #(
				  parameter depth = 4, //params
				  parameter width = 8
				  )(
					 input logic clk, reset,
					 input logic read, write,
					 input logic [width-1:0] inputBus,
					output logic empty, full,
					output logic [width-1:0] outputBus
				   );
					
	// intermediate logic variables for the module
	logic [depth-1:0] rdAddr;
	logic [depth-1:0] wrAddr;
	logic [width-1:0] out;
	logic wren;
	
	// instantiating a 16x8 2 port RAM
	RAM_16x8 ram2port (.clk(clk), .wen(wren), .data_in(inputBus), 
								.read_addr(rdAddr), .write_addr(wrAddr), .data_out(out));
	
	
	// instantiating the FIFO control module			
	FIFO_Control #(depth) FC (.clk, .reset, 
									  .read, 
									  .write, 
									  .wr_en(wren),
									  .empty,
									  .full,
									  .readAddr(rdAddr), 
									  .writeAddr(wrAddr)
									 );
		
	// assigning the output data
	assign outputBus = out;
	
	
endmodule 
//testbench
`timescale 1ps/1ps
module FIFO_testbench();
	//reset params
	parameter depth = 4, width = 8;
	//recall logic variables
	logic clk, reset;
	logic read, write;
	logic [width-1:0] inputBus;
	logic empty, full;
	logic [width-1:0] outputBus;
	//call test case of module
	FIFO #(depth, width) dut (.*);
	//clock setup
	parameter CLK_Period = 100;
	
	initial begin
		clk <= 1'b0;
		forever #(CLK_Period/2) clk <= ~clk;
	end // of clock setup
	
	//testing the instance of writing two pieces of data, and then reading two
	//pieces of data, with gaps scattered in between
	initial begin
		reset <= 1; read <= 0; write <= 0; inputBus <= 00000000; @(posedge clk);
		reset <= 0; read <= 0; write <= 0; inputBus <= 00000000; @(posedge clk);
		reset <= 0; read <= 0; write <= 1; inputBus <= 01111110; @(posedge clk);
		reset <= 0; read <= 0; write <= 1; inputBus <= 00101010; @(posedge clk);
		reset <= 0; read <= 1; write <= 0; inputBus <= 00000000; @(posedge clk);
		reset <= 0; read <= 0; write <= 0; inputBus <= 00000000; @(posedge clk);
		reset <= 0; read <= 1; write <= 0; inputBus <= 00000000; @(posedge clk);
		$stop;
	end
	
endmodule 