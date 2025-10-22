/*
	Ben Davis
	2/23/24
	EE 371
	Lab 4, Task 2
	
	This module switches between the mp3 file input to the audio,
	and the tone written into a quartus created 1-port ROM. It has
	two inputs, clock and in.
	
*/

module audio_mux (
					input logic clk,
					input logic in,
					output logic [23:0] out);
					
	
	logic [15:0] address;
	logic [23:0] q;
					
	rom_note rn (.address(address), .clock(clk), .q(q));
	
	assign out = q;
	
	always_ff @(posedge clk) begin
		if(in) begin
			address <= address + 1;
		end else begin
			address <= 16'b0;
		end
	end
	
endmodule 
//testbench