/*
	Ben Davis
	1/23/24
	EE 371
	Lab 2, Task 2
	
	This is a module used to convert binary numbers to its
	equivalent on a 7 segment active low hex display. It takes
	a 5 bit input in, and has two outputs, each 7bits. There are 
	two outputs in case the number is double digits, it counts up
	to 31 from 0.
*/

module hex_number (in, out1, out2);
	//logic variables
	input logic [4:0] in;
	output logic [6:0] out1;
	output logic [6:0] out2;
	
	//assigns each digit to a different output
	always_comb begin
		case(in)
			
			5'b0: begin out1 <= 7'b1000000;
					out2 <= 7'b1111111; end
					
			5'b1: begin out1 <= 7'b1111001;
					out2 <= 7'b1111111; end
					
			5'b10: begin out1 <= 7'b0100100;
						out2 <= 7'b1111111; end
						
			5'b11: begin out1 <= 7'b0110000;
						out2 <= 7'b1111111; end
						
			5'b100: begin out1 <= 7'b0011001;
						out2 <= 7'b1111111; end
						
			5'b101: begin out1 <= 7'b0010010;
						out2 <= 7'b1111111; end
						
			5'b110: begin out1 <= 7'b0000010;
						out2 <= 7'b1111111; end
						
			5'b111: begin out1 <= 7'b1111000;
						out2 <= 7'b1111111; end
						
			5'b1000: begin out1 <= 7'b0000000;
							out2 <= 7'b1111111; end
							
			5'b1001: begin out1 <= 7'b0011000;
							out2 <= 7'b1111111; end
							
			5'b1010: begin out1 <= 7'b1000000;
							out2 <= 7'b1111001; end
							
			5'b1011: begin out1 <= 7'b1111001;
							out2 <= 7'b1111001; end
							
			5'b1100: begin out1 <= 7'b0100100;
							out2 <= 7'b1111001; end
			
			5'b1101: begin out1 <= 7'b0110000;
							out2 <= 7'b1111001; end
							
			5'b1110: begin out1 <= 7'b0011001;
							out2 <= 7'b1111001; end
							
			5'b1111: begin out1 <= 7'b0010010;
							out2 <= 7'b1111001; end
							
			5'b10000: begin out1 <= 7'b0000010;
							out2 <= 7'b1111001; end
							
			5'b10001: begin out1 <= 7'b1111000;
							out2 <= 7'b1111001; end
							
			5'b10010: begin out1 <= 7'b0000000;
							out2 <= 7'b1111001; end
							
			5'b10011: begin out1 <= 7'b0011000;
							out2 <= 7'b1111001; end
							
			5'b10100: begin out1 <= 7'b1000000;
							out2 <= 7'b0100100; end
							
			5'b10101: begin out1 <= 7'b1111001;
							out2 <= 7'b0100100; end
							
			5'b10110: begin out1 <= 7'b0100100;
							out2 <= 7'b0100100; end
							
			5'b10111: begin out1 <= 7'b0110000;
							out2 <= 7'b0100100; end
							
			5'b11000: begin out1 <= 7'b0011001;
							out2 <= 7'b0100100; end
							
			5'b11001: begin out1 <= 7'b0010010;
							out2 <= 7'b0100100; end
							
			5'b11010: begin out1 <= 7'b0000010;
							out2 <= 7'b0100100; end
							
			5'b11011: begin out1 <= 7'b1111000;
							out2 <= 7'b0100100; end
			
			5'b11100: begin out1 <= 7'b0000000;
							out2 <= 7'b0100100; end
							
			5'b11101: begin out1 <= 7'b0011000;
							out2 <= 7'b0100100; end
							
			5'b11110: begin out1 <= 7'b1000000;
							out2 <= 7'b0110000; end
							
			5'b11111: begin out1 <= 7'b1111001;
							out2 <= 7'b0110000; end
							
			default: begin out1 <= 7'b1111111;
							out2 <= 7'b1111111; end
							
		endcase
	end
endmodule
//testbench
module hex_number_testbench();
	//reset logic variables
	logic [4:0] in;
	logic [6:0] out1;
	logic [6:0] out2;
	//instantiate module
	hex_number dut (.in, .out1, .out2);
	
	//tests instances of the numbers 4, 6, 1,
	//2, and 16
	initial begin
		in <= 00100;
		in <= 00110; #5;
		in <= 00001; #10;
		in <= 00010; #15;
		in <= 10000; #20;
		$stop;
	end
endmodule 