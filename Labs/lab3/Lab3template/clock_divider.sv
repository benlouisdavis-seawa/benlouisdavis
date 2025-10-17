/*
	Ben Davis
	2/1/24
	EE 371
	Lab 3, Task 2
	
	This module takes a clock period (frequency in Hz) and continuously
	divides each frequency by 1/2 until it reaches its 32nd index

*/

module clock_divider (clock, divided_clocks);
	
	input logic clock;
	//output array of 32 frequencies
	output logic [31:0] divided_clocks = 32'b0;
	
	always_ff @(posedge clock) begin
		divided_clocks <= divided_clocks + 1; //slows down clock
	end
endmodule


module clock_divider_testbench();
	logic clock;
	logic [31:0] divided_clocks;
	
	clock_divider dut (.clock, .divided_clocks);
	
	
	parameter clock_period = 100;
	
	initial begin
	
		clock <= 0;
		forever #(clock_period /2) clock <= ~clock; //cut frequency in half
	end //end initialization

	initial begin
        
        for (int i = 0; i < 100; i++) begin
            @(posedge clock); //loop through
        end
        
        $stop; // Stop the simulation
    end
endmodule