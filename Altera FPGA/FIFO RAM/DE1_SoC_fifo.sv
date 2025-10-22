/*
	This is a module that takes the FIFO module and implements
	it onto the FPGA board. It takes in CLOCK_50, Switches 9-0, Keys
	3-0, LEDRs 9-0, and Hex displays 5-0.  It shows the write input
	data on hexes 5 and 4, and shows the read data on hexes 1 and 0.
	It uses switches 7 through 0 for an 8 bit data output. It uses 
	key 3 as the read input, key 2 as the write input, and key 0 as
	the reset input.

	Switches -> data (either written or being pulled from mem)
	Keys -> can reset mem, or read/write data
	LEDRs -> show full and empty status of FIFO
	
*/

module DE1_SoC_fifo (CLOCK_50, SW, KEY, LEDR, HEX0, HEX1, HEX4, HEX5);
	
	// input and outputs
	input logic CLOCK_50;
	input logic [9:0] SW;
	input logic [3:0] KEY;
	output logic [9:0] LEDR;
	output logic [6:0] HEX0;
	output logic [6:0] HEX1;
	output logic [6:0] HEX4;
	output logic [6:0] HEX5;
	
	//intermediat logic variables
	logic [7:0] out; // for outputbus
	logic key_two; //key2
	logic key_three; //key3
	
	
	// start of single pulse for keys 2 and 3
	enum {off, on, hold} ps, ns;
	//key2
	always_ff @(posedge CLOCK_50) begin
		if(~KEY[0]) begin
			ps <= off;
		end else begin
			ps <= ns;
		end
	end
	
	always_comb begin
		case(ps)
		
			off: if(~KEY[2]) ns <= on;
					else ns <= off;
			
			on: if (~KEY[2]) ns <= hold;
					else ns <= off;
					
			hold: if(~KEY[2]) ns <= hold;
					else ns <= off;
					
		endcase
	end
	
	enum {off1, on1, hold1} ps1, ns1;
	//key 3
	always_ff @(posedge CLOCK_50) begin
		if(~KEY[0]) begin
			ps1 <= off1;
		end else begin
			ps1 <= ns1;
		end
	end
	
	always_comb begin
		case(ps1)
		
			off1: if(~KEY[3]) ns1 <= on1;
					else ns1 <= off1;
			
			on1: if (~KEY[3]) ns1 <= hold1;
					else ns1 <= off1;
					
			hold1: if(~KEY[3]) ns1 <= hold1;
					else ns1 <= off1;
					
		endcase
	end
	
	assign key_two = (ps==on);
	assign key_three = (ps1==on1);
	//end of assignment for key single pulses
	
	//fifo to run the ram
	FIFO fifo_task3 (.clk(CLOCK_50), .reset(~KEY[0]), .read(key_three), .write(key_two),
							.inputBus(SW[7:0]), .empty(LEDR[8]), .full(LEDR[9]),
								.outputBus(out));
	
	// intermediate logic for all of the hex displays
	logic [6:0] hx0;
	logic [6:0] hx1;
	logic [6:0] hx4;
	logic [6:0] hx5;
	
	//running interm logic for hex displays and converting
	//to seven segment active low
	hexadecimal zero (.in(out[3:0]), .out(hx0));
	hexadecimal one (.in(out[7:4]), .out(hx1));
	hexadecimal four (.in(SW[3:0]), .out(hx4));
	hexadecimal five (.in(SW[7:4]), .out(hx5));
	
	//assigning hex display values
	assign HEX0 = hx0;
	assign HEX1 = hx1;
	
	assign HEX4 = hx4;
	assign HEX5 = hx5;
	
endmodule

//testbench
module DE1_SoC_fifo_testbench();
	
	//repeat logic variables
	logic CLOCK_50;
	logic [9:0] SW;
	logic [3:0] KEY;
	logic [9:0] LEDR;
	logic [6:0] HEX0;
	logic [6:0] HEX1;
	logic [6:0] HEX4;
	logic [6:0] HEX5;
	
	//create instance of module
	DE1_SoC_fifo dut (.CLOCK_50, .SW, .KEY, .LEDR, .HEX0, .HEX1, .HEX4, .HEX5);
	
	//testing instance with a write, a gap, and then a read
	initial begin
		KEY[3:0] <= 1111; SW[9:0] <= 0000000010; 
		KEY[3:0] <= 1011; SW[9:0] <= 0000000010; #5;
		KEY[3:0] <= 1111; SW[9:0] <= 0000000010; #10;
		KEY[3:0] <= 0111; SW[9:0] <= 0000000010; #15;
		KEY[3:0] <= 1111; SW[9:0] <= 0000000010; #20;
		$stop;
	end
endmodule
		