/*
	Ben Davis
	2/2/24
	EE 371
	Lab 3, Task 2
	
	This is a module that takes in eight inputs. Four of them 
	are for the start and end coordinates of the beginning of
	the animation, and the other four are four the end coordinates
	of the animation. This module is fo task 2, so it has only 
	been programmed to draw a straight line moving.
	
*/

module animator (
		input logic clk, reset,
		input logic [9:0] x0, x1, w0, w1, //all x coordinates
		output logic [9:0] a0, a1 //next x coordinates
);

	int xw0_step;
	int xw1_step;
	
	assign xw0_step = (w0 > x0) ? 1 : -1;
	assign xw1_step = (w1 > x1) ? 1 : -1;

	always_ff @(posedge clk) begin
		if (reset) begin
			a0 <= x0;
			a1 <= x1;
		end else begin
		
			//expanding to the left
			if(a0 > w0) begin
				a0 <= a0 - 1;
			end else begin
				a0 <= a0;
			end
			
			//expanding to the right
			if(a1 < w1) begin
				a1 <= a1 + 1;
			end else begin
				a1 <= a1;
			end
		end
	end //of ff
	
endmodule
//testbench
module animator_testbench();

	logic clk, reset;
	logic [9:0] x0, x1, w0, w1, a0, a1;
	
	animator dut (.clk, .reset, .x0, .x1, .w0, .w1,
											.a0, .a1);
												
	parameter clk_p = 100;
	initial begin
		clk <= 0;
		forever #(clk_p /2) clk <= ~clk;
	end
	
	//testing the instance of drawing a horizontal line that
	//is always at y = 80, and moves from an initial x 200 to
	//200 to a line that spans 100 to 300
	initial begin
		reset <= 1; x0 <= 200; x1 <= 200; w0 <= 100; w1 <= 300;
													  @(posedge clk);
									  reset <= 0; @(posedge clk);
													  @(posedge clk);
													  @(posedge clk);
													  @(posedge clk);
													  @(posedge clk);
													  @(posedge clk);
		$stop;
	end
endmodule //testbench