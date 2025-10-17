/*

*/

module complete_bin (
				input logic clk,
				input logic reset,
				input logic start,
				input logic [7:0] A,
				output logic [6:0] hx0,
				output logic [6:0] hx1);
				
				
		logic finish, clear, comp, hold, found;
		logic [4:0] L;
				
		fsm_bin fsm (.clk(clk), .reset(reset), .start(start), .finish(finish),
						.clear(clear), .comp(comp), .hold(hold));
	
		data_bin asm (.clk(clk), .A(A), .clear(clear), .comp(comp), .hold(hold),
						.L(L), .finish(finish), .found(found));
						
						
		logic [6:0] hexd0;
		hexadecimal hex0 (.in(L[3:0]), .out(hexd0));
		
		logic [6:0] hexd1;
		hexadecimal hex1 (.in(L[4]), .out(hexd1));
		
		always_comb begin
			if(found) begin
				hx1 <= hexd1;
				hx0 <= hexd0;
			end else begin
				hx1 <= 7'b1111111;
				hx0 <= 7'b1111111;
			end
		end
endmodule

`timescale 1ps/1ps
module complete_bin_tb ();

	logic clk, reset, start;
	logic [7:0] A;
	logic [6:0] hx0, hx1;
	
	complete_bin dut (.clk, .reset, .start, .A, .hx0, .hx1);
	
	parameter clk_pd = 100;
	initial begin
		clk <= 0;
		forever #(clk_pd /2) clk <= ~clk;
	end
	
	initial begin
		reset <= 1'b0; start <= 1'b0; A <= 8'b00000001; @(posedge clk);
		reset <= 1'b0; start <= 1'b1; A <= 8'b00000001; @(posedge clk);
		reset <= 1'b0; start <= 1'b1; A <= 8'b00000001; @(posedge clk);
		reset <= 1'b0; start <= 1'b1; A <= 8'b00000001; @(posedge clk);
		reset <= 1'b0; start <= 1'b1; A <= 8'b00000001; @(posedge clk);
		reset <= 1'b0; start <= 1'b1; A <= 8'b00000001; @(posedge clk);
		reset <= 1'b0; start <= 1'b1; A <= 8'b00000001; @(posedge clk);
		reset <= 1'b0; start <= 1'b1; A <= 8'b00000001; @(posedge clk);
		reset <= 1'b0; start <= 1'b1; A <= 8'b00000001; @(posedge clk);
		reset <= 1'b0; start <= 1'b1; A <= 8'b00000001; @(posedge clk);
		reset <= 1'b0; start <= 1'b1; A <= 8'b00000001; @(posedge clk);
		reset <= 1'b0; start <= 1'b1; A <= 8'b00000001; @(posedge clk);
		reset <= 1'b0; start <= 1'b1; A <= 8'b00000001; @(posedge clk);
		$stop;
	end
endmodule //test end