/*
	Ben Davis
	2/1/24
	EE 371
	Lab 3, Task 1
	
	This module is solely for the demo for Lab 3, task 1.
	It takes in two inputs to show four cases of displaying 
	the linedrawer module. A horizontal line, a vertical line,
	a line with slope=1, and a shallow sloped line. It then has
	four outputs of bits 9 and 10 to write in the x0,x1,y0, and y1
	inputs.
	
*/

module lab3_task1_inputter (
			input logic [1:0] in, //input
			output logic [9:0] x0, //start x
			output logic [8:0] y0, //start y
			output logic [9:0] x1, //end x
			output logic [8:0] y1 //end y   
);
			
	//for assigning outputs
	always_comb begin
		case(in)
		
			//slope of 1
			2'b00: begin
						x0 <= 0;
						y0 <= 0;
						x1 <= 255;
						y1 <= 255;
					 end
					 
			//horizontal line
			2'b01: begin
						x0 <= 50;
						y0 <= 255;
						x1 <= 450;
						y1 <= 255;
					 end
					
			//vertical line
			2'b10: begin
						x0 <= 300;
						y0 <= 0;
						x1 <= 300;
						y1 <= 511;
					 end
			
			//shallow slope
			2'b11: begin
						x0 <= 0;
						y0 <= 255;
						x1 <= 100;
						y1 <= 275;
					 end
						
			default: begin
							x0 <= 0;
							y0 <= 0;
							x1 <= 0;
							y1 <= 0;
						end
		endcase
	end
	
endmodule
//testbench start
module lab3_task1_inputter_testbench();
		
		//repeat logic variables
		logic [1:0] in;
		logic [9:0] x0;
		logic [8:0] y0;
		logic [9:0] x1;
		logic [8:0] y1;
		
		//reinstantiate module
		lab3_task1_inputter dut (.in, .x0, .y0, .x1, .y1);
		
		//tests instance of all four different inputs
		initial begin
			in <= 00; 
			in <= 01; #5;
			in <= 10; #5;
			in <= 11; #5;
			
			$stop;
		end
endmodule //testbench