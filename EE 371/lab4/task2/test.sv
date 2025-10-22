module test (
			input logic clk,
			output logic true);
			
	logic [7:0] out;
	ram32x8 ram (.address(6'b10001), .clock(clk), .data(8'b0), .wren(0), .q(out));
	
	assign true = (out == 8'b00010010);
endmodule
`timescale 1ps/1ps
module test_tb ();

	logic clk, true;
	test dut (.clk, .true);
	
	initial begin
		#5;
		#5;
		$stop;
	end
endmodule 