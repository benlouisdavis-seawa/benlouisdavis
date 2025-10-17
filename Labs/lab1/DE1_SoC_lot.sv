/*
	Ben Davis
	1/12/23
	EE 371
	Lab 1
	
	This is a module that implements the parking lot
	counter onto a DE1 SoC board. Sw9 is sensor a, SW8 is sensor b,
	and SW0 is the reset button for the system. The system will keep
	track of how many cars are in the lot, and display the number of
	cars on the Hex displays. If there are 0 cars it will display
	"CLEAr," and when there are 25 cars it displays "FULL." The maximum
	number of cars is 25.
	
*/

module DE1_SoC_lot (CLOCK_50, V_GPIO, HEX0, HEX1, HEX2, HEX3, HEX4, HEX5, LEDR);

	input logic CLOCK_50; //clock
	//input logic [9:0] SW; //switches for a, b, and reset
	output logic [6:0] HEX0; // hex lights for displaying amount
	output logic [6:0] HEX1; // of cars in the lot
	output logic [6:0] HEX2;
	output logic [6:0] HEX3;
	output logic [6:0] HEX4;
	output logic [6:0] HEX5;
	output logic [9:0] LEDR; // a and b signals
	
	inout logic [35:23] V_GPIO;
	
	assign V_GPIO[34] = V_GPIO[23];
	assign V_GPIO[35] = V_GPIO[24];
	
	logic [4:0] out; //output to tell display what number to show
	logic enter; //a car enters the lot
	logic exit; //a car exits the lot
	
	//assign LEDR[1] = SW[9];
	//assign LEDR[0] = SW[8];
	
	//this module keeps track of whether a car leaves or enters the lot
	lot_counter parker (.clk(CLOCK_50), .rst(V_GPIO[30]), .a(V_GPIO[23]), .b(V_GPIO[24]),
								.enter(enter), .exit(exit));
	
	//this module keeps track of how many cars are inside the parking lot
	counter_25 c25 (.clk(CLOCK_50), .rst(V_GPIO[30]), .inc(enter), .dec(exit),
							.out(out));
	
	//the output of the counter_25 is used to determine what is displayed
	// on the hex board. goes from 1-24. For 0 displays "clear," for 25 displays
	// "full."
	always_comb begin
		if(out==5'b00000) begin
			HEX5 <= 7'b1000110;
			HEX4 <= 7'b1000111;
			HEX3 <= 7'b0000110;
			HEX2 <= 7'b0001000;
			HEX1 <= 7'b0101111;
			HEX0 <= 7'b1111111;
		end else if(out==5'b00001) begin
			HEX5 <= 7'b1111111;
			HEX4 <= 7'b1111111;
			HEX3 <= 7'b1111111;
			HEX2 <= 7'b1111111;
			HEX1 <= 7'b1111111;
			HEX0 <= 7'b1111001;
		end else if(out==5'b00010) begin
			HEX5 <= 7'b1111111;
			HEX4 <= 7'b1111111;
			HEX3 <= 7'b1111111;
			HEX2 <= 7'b1111111;
			HEX1 <= 7'b1111111;
			HEX0 <= 7'b0100100;
		end else if(out==5'b00011) begin
			HEX5 <= 7'b1111111;
			HEX4 <= 7'b1111111;
			HEX3 <= 7'b1111111;
			HEX2 <= 7'b1111111;
			HEX1 <= 7'b1111111;
			HEX0 <= 7'b0110000;
		end else if(out==5'b00100) begin
			HEX5 <= 7'b1111111;
			HEX4 <= 7'b1111111;
			HEX3 <= 7'b1111111;
			HEX2 <= 7'b1111111;
			HEX1 <= 7'b1111111;
			HEX0 <= 7'b0011001;
		end else if(out==5'b00101) begin
			HEX5 <= 7'b1111111;
			HEX4 <= 7'b1111111;
			HEX3 <= 7'b1111111;
			HEX2 <= 7'b1111111;
			HEX1 <= 7'b1111111;
			HEX0 <= 7'b0010010;
		end else if(out==5'b00110) begin
			HEX5 <= 7'b1111111;
			HEX4 <= 7'b1111111;
			HEX3 <= 7'b1111111;
			HEX2 <= 7'b1111111;
			HEX1 <= 7'b1111111;
			HEX0 <= 7'b0000010;
		end else if(out==5'b00111) begin
			HEX5 <= 7'b1111111;
			HEX4 <= 7'b1111111;
			HEX3 <= 7'b1111111;
			HEX2 <= 7'b1111111;
			HEX1 <= 7'b1111111;
			HEX0 <= 7'b1111000;
		end else if(out==5'b01000) begin
			HEX5 <= 7'b1111111;
			HEX4 <= 7'b1111111;
			HEX3 <= 7'b1111111;
			HEX2 <= 7'b1111111;
			HEX1 <= 7'b1111111;
			HEX0 <= 7'b0000000;
		end else if(out==5'b01001) begin
			HEX5 <= 7'b1111111;
			HEX4 <= 7'b1111111;
			HEX3 <= 7'b1111111;
			HEX2 <= 7'b1111111;
			HEX1 <= 7'b1111111;
			HEX0 <= 7'b0011000;
		end else if(out==5'b01010) begin
			HEX5 <= 7'b1111111;
			HEX4 <= 7'b1111111;
			HEX3 <= 7'b1111111;
			HEX2 <= 7'b1111111;
			HEX1 <= 7'b1111001;
			HEX0 <= 7'b1000000;
		end else if(out==5'b01011) begin
			HEX5 <= 7'b1111111;
			HEX4 <= 7'b1111111;
			HEX3 <= 7'b1111111;
			HEX2 <= 7'b1111111;
			HEX1 <= 7'b1111001;
			HEX0 <= 7'b1111001;
		end else if(out==5'b01100) begin
			HEX5 <= 7'b1111111;
			HEX4 <= 7'b1111111;
			HEX3 <= 7'b1111111;
			HEX2 <= 7'b1111111;
			HEX1 <= 7'b1111001;
			HEX0 <= 7'b0100100;
		end else if(out==5'b01101) begin
			HEX5 <= 7'b1111111;
			HEX4 <= 7'b1111111;
			HEX3 <= 7'b1111111;
			HEX2 <= 7'b1111111;
			HEX1 <= 7'b1111001;
			HEX0 <= 7'b0110000;
		end else if(out==5'b01110) begin
			HEX5 <= 7'b1111111;
			HEX4 <= 7'b1111111;
			HEX3 <= 7'b1111111;
			HEX2 <= 7'b1111111;
			HEX1 <= 7'b1111001;
			HEX0 <= 7'b0011001;
		end else if(out==5'b01111) begin
			HEX5 <= 7'b1111111;
			HEX4 <= 7'b1111111;
			HEX3 <= 7'b1111111;
			HEX2 <= 7'b1111111;
			HEX1 <= 7'b1111001;
			HEX0 <= 7'b0010010;
		end else if(out==5'b10000) begin
			HEX5 <= 7'b1111111;
			HEX4 <= 7'b1111111;
			HEX3 <= 7'b1111111;
			HEX2 <= 7'b1111111;
			HEX1 <= 7'b1111001;
			HEX0 <= 7'b0000010;
		end else if(out==5'b10001) begin
			HEX5 <= 7'b1111111;
			HEX4 <= 7'b1111111;
			HEX3 <= 7'b1111111;
			HEX2 <= 7'b1111111;
			HEX1 <= 7'b1111001;
			HEX0 <= 7'b1111000;
		end else if(out==5'b10010) begin
			HEX5 <= 7'b1111111;
			HEX4 <= 7'b1111111;
			HEX3 <= 7'b1111111;
			HEX2 <= 7'b1111111;
			HEX1 <= 7'b1111001;
			HEX0 <= 7'b0000000;
		end else if(out==5'b10011) begin
			HEX5 <= 7'b1111111;
			HEX4 <= 7'b1111111;
			HEX3 <= 7'b1111111;
			HEX2 <= 7'b1111111;
			HEX1 <= 7'b1111001;
			HEX0 <= 7'b0011000;
		end else if(out==5'b10100) begin
			HEX5 <= 7'b1111111;
			HEX4 <= 7'b1111111;
			HEX3 <= 7'b1111111;
			HEX2 <= 7'b1111111;
			HEX1 <= 7'b0100100;
			HEX0 <= 7'b1000000;
		end else if(out==5'b10101) begin
			HEX5 <= 7'b1111111;
			HEX4 <= 7'b1111111;
			HEX3 <= 7'b1111111;
			HEX2 <= 7'b1111111;
			HEX1 <= 7'b0100100;
			HEX0 <= 7'b1111001;
		end else if(out==5'b10110) begin
			HEX5 <= 7'b1111111;
			HEX4 <= 7'b1111111;
			HEX3 <= 7'b1111111;
			HEX2 <= 7'b1111111;
			HEX1 <= 7'b0100100;
			HEX0 <= 7'b0100100;
		end else if(out==5'b10111) begin
			HEX5 <= 7'b1111111;
			HEX4 <= 7'b1111111;
			HEX3 <= 7'b1111111;
			HEX2 <= 7'b1111111;
			HEX1 <= 7'b0100100;
			HEX0 <= 7'b0110000;
		end else if(out==5'b11000) begin
			HEX5 <= 7'b1111111;
			HEX4 <= 7'b1111111;
			HEX3 <= 7'b1111111;
			HEX2 <= 7'b1111111;
			HEX1 <= 7'b0100100;
			HEX0 <= 7'b0011001;
		end else if(out==5'b11001) begin
			HEX5 <= 7'b0001110;
			HEX4 <= 7'b1000001;
			HEX3 <= 7'b1000111;
			HEX2 <= 7'b1000111;
			HEX1 <= 7'b1111111;
			HEX0 <= 7'b1111111;
		end else begin
			HEX5 <= 7'b1111111;
			HEX4 <= 7'b1111111;
			HEX3 <= 7'b1111111;
			HEX2 <= 7'b1111111;
			HEX1 <= 7'b1111111;
			HEX0 <= 7'b1111111;
		end
	end
endmodule 
/*
module DE1_SoC_lot_testbench();

	logic CLOCK_50; // repeating variables
	logic [9:0] SW;
	logic [6:0] HEX5, HEX4, HEX3, HEX2, HEX1, HEX0;
	
	// clock setup
	logic clk;
	
	parameter clock_period = 100;
	
	initial begin
		clk <= 0;
		forever #(clock_period /2) clk = ~clk;
	end // of clock setup
	
	//module for testbench
	DE1_SoC_lot dut (.CLOCK_50(clk), .SW, .HEX0, .HEX1, .HEX2,
							.HEX3, .HEX4, .HEX5);
					
	// this instance follows the pattern of two cars entering the lot
	// followed by one car exiting the lot
	initial begin
		SW[0] <= 0; SW[9] <= 0; SW[8] <= 0; @(posedge clk);
		SW[0] <= 0; SW[9] <= 1; SW[8] <= 0; @(posedge clk);
		SW[0] <= 0; SW[9] <= 1; SW[8] <= 1; @(posedge clk);
		SW[0] <= 0; SW[9] <= 0; SW[8] <= 1; @(posedge clk);
		SW[0] <= 0; SW[9] <= 0; SW[8] <= 0; @(posedge clk);
		SW[0] <= 0; SW[9] <= 1; SW[8] <= 0; @(posedge clk);
		SW[0] <= 0; SW[9] <= 1; SW[8] <= 1; @(posedge clk);
		SW[0] <= 0; SW[9] <= 0; SW[8] <= 1; @(posedge clk);
		SW[0] <= 0; SW[9] <= 0; SW[8] <= 0; @(posedge clk);
		SW[0] <= 0; SW[9] <= 0; SW[8] <= 1; @(posedge clk);
		SW[0] <= 0; SW[9] <= 1; SW[8] <= 1; @(posedge clk);
		SW[0] <= 0; SW[9] <= 1; SW[8] <= 0; @(posedge clk);
		SW[0] <= 0; SW[9] <= 0; SW[8] <= 0; @(posedge clk);
		SW[0] <= 0; SW[9] <= 0; SW[8] <= 0; @(posedge clk);
		
		$stop;
	end
endmodule 
*/