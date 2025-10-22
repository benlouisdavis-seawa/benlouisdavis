/*
	Ben Davis
	1/11/23
	EE 371
	Lab 1
	
	This is a module that is used for a parking lot counter
	It has to inputs, a and b. It also has two outputs, enter 
	and exit. When a car passes through a and then b, the enter 
	signal is one. If a car passes through b then a, the exit 
	signal is on.
*/

module lot_counter (
							input logic clk, //clock
							input logic rst, //reset
							input logic a, //sensor a
							input logic b, //sensor b
							output logic enter, //a car enters
							output logic exit //a car exits
							);
							
	enum {empty, sa, sb, fulla, fullb, left, entered} ps, ns;
	
	// resets the state to empty, otherwise moves to next state
	always_ff @(posedge clk) begin
		if(rst) begin
			ps <= empty;
		end else begin
			ps <= ns;
		end
	end
	
	//state process that keeps track of whether a car leaves or enters
	// without confusing one for the other. only marks a car that fully
	// leaves or fully enters
	always_comb begin
		case(ps)
		
			empty: if(a) ns <= sa;
						else if(b) ns <= sb;
						else ns <= empty;
						
			sa: if(a&b) ns <= fulla;
					else if(a & ~b) ns <= sa;
					else ns <= empty;
					
			sb: if(a&b) ns <= fullb;
					else if(~a & b) ns <= sb;
					else ns <= empty;
					
			fulla: if(a&b) ns <= fulla;
						else if(~a & b) ns <= entered;
						else if(a & ~b) ns <= sa;
						else ns <= empty;
						
			fullb: if(a&b) ns <= fullb;
						else if(a & ~b) ns <= left;
						else if(~a & b) ns <= sb;
						else ns <= empty;
					
			left: if(a & b) ns <= fullb;
					else if(a & ~b) ns <= left;
					else ns <= empty;
					
			entered: if(a&b) ns <= fulla;
						else if(~a & b) ns <= entered;
						else ns <= empty;
						
		endcase
	end
	
	assign enter = ((ps==entered) & ~b); // assigning the enter and exit outputs
	assign exit = ((ps==left) & ~a);     // so they correctly identify cars movements
	
endmodule 

module lot_counter_testbench();

	logic clk, rst, a, b, enter, exit; //repeating same variables
	
	lot_counter dut (.clk, .rst, .a, .b, .enter, .exit); // creating another 
																		  // instance of this module
	
	// clock setup
	parameter clock_period = 100;
	
	initial begin
		clk <= 0;
		forever #(clock_period /2) clk = ~clk;
	end // of clock setup
	
	/*
		This code tests an instance of one car entering the lot completely,
		and another car leaving the lot halfway, and then backing up into
		the lot without leaving
	*/
	initial begin
		rst <= 0; a <= 0; b <= 0; @(posedge clk);
		rst <= 0; a <= 1; b <= 0; @(posedge clk);
		rst <= 0; a <= 1; b <= 1; @(posedge clk);
		rst <= 0; a <= 0; b <= 1; @(posedge clk);
		rst <= 0; a <= 0; b <= 0; @(posedge clk);
		rst <= 0; a <= 0; b <= 0; @(posedge clk);
		rst <= 0; a <= 0; b <= 1; @(posedge clk);
		rst <= 0; a <= 1; b <= 1; @(posedge clk);
		rst <= 0; a <= 0; b <= 1; @(posedge clk);
		rst <= 0; a <= 0; b <= 0; @(posedge clk);
		rst <= 0; a <= 0; b <= 0; @(posedge clk);
		$stop;
	end
endmodule 