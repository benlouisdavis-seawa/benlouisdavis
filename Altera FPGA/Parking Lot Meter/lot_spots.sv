/* 
	This module takes in the car prescence inputs and
	outputs a 7 bit value for the HEX displays to show
	the available spots.
*/
	
module lot_spots (
	input logic [1:0] cars, //amount of cars in lots
	output logic [6:0] hx0, //hex0 value
	output logic [6:0] hx1, //hex1 value
	output logic [6:0] hx2, //hex2 value
	output logic [6:0] hx3  //hex3 value
);

	//uses an always comb value to have the hexes
	//show the available amount of spots left
	//goes from 3-1, and displays "FULL" if
	//0 spots are left
	always_comb begin
		case(cars)
			2'b00: begin
						hx0 <= 7'b0110000;
						hx1 <= 7'b1111111;
						hx2 <= 7'b1111111;
						hx3 <= 7'b1111111;
					 end
			2'b01: begin
						hx0 <= 7'b0100100;
						hx1 <= 7'b1111111;
						hx2 <= 7'b1111111;
						hx3 <= 7'b1111111;
					 end
			2'b10: begin
						hx0 <= 7'b1111001;
						hx1 <= 7'b1111111;
						hx2 <= 7'b1111111;
						hx3 <= 7'b1111111;
					 end
			2'b11: begin
						hx0 <= 7'b1000111;
						hx1 <= 7'b1000111;
						hx2 <= 7'b1000001;
						hx3 <= 7'b0001110;
					 end
		endcase
	end
endmodule
//testbench
module lot_spots_tb();
	//logic variables
	logic [1:0] cars;
	logic [6:0] hx0, hx1, hx2, hx3;
	
	lot_spots dut(.*);
	
	//tests a case where the lot fills up one car at a time
	initial begin
		cars <= 2'b00; #5;
		cars <= 2'b01; #5;
		cars <= 2'b10; #5;
		cars <= 2'b11; #5;
		$stop;
	end
endmodule 