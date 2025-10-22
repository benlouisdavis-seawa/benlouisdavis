/*
  This module scrolls through the ram for the amount
	of total cars that have visited the lot at that 
	hour in the day. it has no inputs, just a clock,
	a reset to "start" the system, and a 4 bit output.
*/

module scroller (clk, rst, out);

	input logic clk, rst; //clock, reset, increment, decrement
	output logic [3:0] out; //number of cars inside lot
	
	enum {s0, s1, s2, s3, s4, s5, s6, s7} ps, ns;
	
	//always ff block to reset the state to zero
	//or to move to the next state if need be
	always_ff @(posedge clk or posedge rst) begin
		if(rst) begin
			ps <= s0;
		end else begin
			ps <= ns;
	end end
	
	//the block to tell each state if it goes to the
	//next or previous state
	always_comb begin
		case(ps)
		
			s0: begin out <= 4'b0000; ns <= s1; end
					
			s1: begin out <= 4'b0001; ns <= s2; end
					
			s2: begin out <= 4'b0010; ns <= s3; end
					
			s3: begin out <= 4'b0011; ns <= s4; end
					
			s4: begin out <= 4'b0100; ns <= s5; end
					
			s5: begin out <= 4'b0101; ns <= s6; end
					
			s6: begin out <= 4'b0110; ns <= s7; end
					
			s7: begin out <= 4'b0111; ns <= s0; end
					
		endcase
	end
endmodule
	
module scroller_testbench();

	logic clk, rst; //repeating logic variables
	logic [3:0] out;
	
	//test counter_25 module
	scroller dut (.clk, .rst, .out);
	
	// clock setup
	parameter clock_period = 100;
	
	initial begin
		clk <= 0;
		forever #(clock_period /2) clk = ~clk;
	end // of clock setup
	
	//an instance where it counts up to five with a
	//space after the first increment, and then
	//decrements twice
	initial begin
		rst <= 0; @(posedge clk);
		rst <= 0; @(posedge clk);
		rst <= 0; @(posedge clk);
		rst <= 0; @(posedge clk);
		rst <= 0; @(posedge clk);
		rst <= 0; @(posedge clk);
		rst <= 0; @(posedge clk);
		rst <= 0; @(posedge clk);
		rst <= 0; @(posedge clk);
		$stop;
	end
endmodule 