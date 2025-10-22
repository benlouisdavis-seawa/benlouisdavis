/*
	This module controls the read and write addresses for the
	FIFO module, as well as maintaing the full and empty signals.
	It takes in a clock, reset, read, and write, inputs. It outputs
	a write enable for when the write input is called and the RAM is
	not full. The empty and full outputs let the user know the state
	of their RAM. The readAddr, and writeAddr are updated to help the
	RAM stay orderly.
	
*/

module FIFO_Control #(
							 parameter depth = 4 //param
							 )(
								input logic clk, reset,
								input logic read, write,
							  output logic wr_en,
							  output logic empty, full,
							  output logic [depth-1:0] readAddr, writeAddr
							  );
	
	//maintaining the output signals
	always_ff @(posedge clk) begin
		if(reset) begin
			 readAddr <= 4'b0;
			writeAddr <= 4'b0;
				 empty <= 1'b1;
				  full <= 1'b0;
		end else begin
			empty <= (readAddr == writeAddr); //signals empty
			full <= (writeAddr + 1 == readAddr); //signals full
			if (read && ~empty) readAddr <= readAddr + 1; //increments read address
			if (write && ~full) writeAddr <= writeAddr + 1; //increments write address
		end
	end
	
	//assigns value to write enable signal for the FIFO
	assign wr_en = (write && ~full);
	
endmodule 
//testbench
module FIFO_Control_testbench();
	//reset param and logic variables
	parameter depth = 4;
	logic clk, reset, read, write, wr_en, empty, full;
	logic [depth-1:0] readAddr, writeAddr;
	//instantiate module
	FIFO_Control dut (.clk, .reset, .read, .write, .wr_en, .empty, .full
								, .readAddr, .writeAddr);
	//clock setup				
	parameter clock_period = 100;
	
	initial begin
		clk <= 0;
		forever #(clock_period/2) clk <= ~clk;
	end //of clock setup
	
	//tests instance with an initial reset, and two write
	//signals followed by one read signal
	initial begin
		reset <= 1; read <= 0; write <= 0; @(posedge clk);
		reset <= 0; read <= 0; write <= 1; @(posedge clk);
		reset <= 0; read <= 0; write <= 1; @(posedge clk);
		reset <= 0; read <= 1; write <= 0; @(posedge clk);
		reset <= 0; read <= 0; write <= 0; @(posedge clk);
		$stop;
	end
endmodule 