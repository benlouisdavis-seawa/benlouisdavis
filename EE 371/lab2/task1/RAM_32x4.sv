/*
	Ben Davis
	1/22/24
	EE 371
	Lab 2, Task 1
	
	This module implements a 32 word x 4 bit RAM. It has a read
	and a write enable. Takes in a 4 bit input, 5 bit data address
	and a 4 bit output
	
*/

module RAM_32x4 (
						input logic clk, wen, 
						input logic [3:0] data_in, 
						input logic [4:0] data_addr,
						output logic [3:0] data_out
						);
	//ram memory
	logic [3:0] memory_array [31:0];
	
	//updates ram with current writes
	always_ff @(posedge clk) begin
		if(wen) begin
			memory_array[data_addr] <= data_in;
		end
		data_out <= memory_array[data_addr];
	end
	
endmodule
//testbench
module RAM_32x4_testbench();
	//reset logic variables
	logic clk, wen;
	logic [3:0] data_in;
	logic [4:0] data_addr;
	logic [3:0] data_out;
	//instantiate ram
	RAM_32x4 dut (.clk, .wen, .data_in, .data_addr, .data_out);
	
	// clock setup
	parameter clock_period = 100;
	
	initial begin
		clk <= 0;
		forever #(clock_period /2) clk = ~clk;
	end // of clock setup
	
	//tests instance of writing a piece of data, reading it,
	//and then writing a second piece of data and reading it
	initial begin
		
		wen <= 1; data_in <= 4'b0111; data_addr <= 4'b01111; @(posedge clk);
		wen <= 1; data_in <= 4'b0111; data_addr <= 4'b01111; @(posedge clk);
		wen <= 0; data_in <= 4'b0111; data_addr <= 4'b01111; @(posedge clk);
		wen <= 0; data_in <= 4'b0111; data_addr <= 4'b01111; @(posedge clk);
		wen <= 1; data_in <= 4'b0101; data_addr <= 4'b00010; @(posedge clk);
		wen <= 1; data_in <= 4'b0101; data_addr <= 4'b00010; @(posedge clk);
		wen <= 0; data_in <= 4'b0101; data_addr <= 4'b00010; @(posedge clk);
		wen <= 0; data_in <= 4'b0101; data_addr <= 4'b00010; @(posedge clk);
		
		$stop;
	end
endmodule 