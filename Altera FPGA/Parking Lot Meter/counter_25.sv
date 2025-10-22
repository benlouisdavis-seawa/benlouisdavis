/*
	This module counts up to 25 for the parking lot meter. 
	It takes in three inputs, a reset, a plus one (inc), and
	a minus one (dec). It returns the number of cars in the lot
	as a 5 bit output (out).
*/

module counter_25 (clk, rst, inc, dec, out);

	input logic clk, rst, inc, dec; //clock, reset, increment, decrement
	output logic [4:0] out; //number of cars inside lot
	
	enum {s0, s1, s2, s3, s4, s5, s6, s7, s8 //states to count the # of cars
			, s9, s10, s11, s12, s13, s14, s15
			, s16, s17, s18, s19, s20, s21, s22
			, s23, s24, s25} ps, ns;
	
	//always ff block to reset the state to zero
	//or to move to the next state if need be
	always_ff @(posedge clk) begin
		if(rst) begin
			ps <= s0;
		end else begin
			ps <= ns;
		end
	end
	
	//assigning each bit. each bit is one in specific states
	// example: first bit is only true in odd states
	assign out[0] = ((ps==s1)|(ps==s3)|(ps==s5)|(ps==s7)|(ps==s9)|
							(ps==s11)|(ps==s13)|(ps==s15)|(ps==s17)|(ps==s19)|
							(ps==s21)|(ps==s23)|(ps==s25));
							
	assign out[1] = ((ps==s2)|(ps==s3)|(ps==s6)|(ps==s7)|(ps==s10)|(ps==s11)|
							(ps==s14)|(ps==s15)|(ps==s18)|(ps==s19)|(ps==s22)|(ps==s23));
							
	assign out[2] = ((ps==s4)|(ps==s5)|(ps==s6)|(ps==s7)|(ps==s12)|(ps==s13)|(ps==s14)|
							(ps==s15)|(ps==s20)|(ps==s21)|(ps==s22)|(ps==s23));
							
	assign out[3] = ((ps==s8)|(ps==s9)|(ps==s10)|(ps==s11)|(ps==s12)|(ps==s13)|
							(ps==s14)|(ps==s15)|(ps==s24)|(ps==s25));
							
	assign out[4] = ((ps==s16)|(ps==s17)|(ps==s18)|(ps==s19)|(ps==s20)|(ps==s21)|
							(ps==s22)|(ps==s23)|(ps==s24)|(ps==s25));
	
	//the block to tell each state if it goes to the
	//next or previous state
	always_comb begin
		case(ps)
		
			s0: if(inc) ns <= s1;
					else ns <= s0;
					
			s1: if(inc) ns <= s2;
					else if(dec) ns <= s0;
					else ns <= s1;
					
			s2: if(inc) ns <= s3;
					else if(dec) ns <= s1;
					else ns <= s2;
					
			s3: if(inc) ns <= s4;
					else if(dec) ns <= s2;
					else ns <= s3;
					
			s4: if(inc) ns <= s5;
					else if(dec) ns <= s3;
					else ns <= s4;
					
			s5: if(inc) ns <= s6;
					else if(dec) ns <= s4;
					else ns <= s5;
					
			s6: if(inc) ns <= s7;
					else if(dec) ns <= s5;
					else ns <= s6;
					
			s7: if(inc) ns <= s8;
					else if(dec) ns <= s6;
					else ns <= s7;
					
			s8: if(inc) ns <= s9;
					else if(dec) ns <= s7;
					else ns <= s8;
					
			s9: if(inc) ns <= s10;
					else if(dec) ns <= s8;
					else ns <= s9;
					
			s10: if(inc) ns <= s11;
					else if(dec) ns <= s9;
					else ns <= s10;
					
			s11: if(inc) ns <= s12;
					else if(dec) ns <= s10;
					else ns <= s11;
					
			s12: if(inc) ns <= s13;
					else if(dec) ns <= s11;
					else ns <= s12;
					
			s13: if(inc) ns <= s14;
					else if(dec) ns <= s12;
					else ns <= s13;
					
			s14: if(inc) ns <= s15;
					else if(dec) ns <= s13;
					else ns <= s14;
					
			s15: if(inc) ns <= s16;
					else if(dec) ns <= s14;
					else ns <= s15;
					
			s16: if(inc) ns <= s17;
					else if(dec) ns <= s15;
					else ns <= s16;
					
			s17: if(inc) ns <= s18;
					else if(dec) ns <= s16;
					else ns <= s17;
					
			s18: if(inc) ns <= s19;
					else if(dec) ns <= s17;
					else ns <= s18;
					
			s19: if(inc) ns <= s20;
					else if(dec) ns <= s18;
					else ns <= s19;
					
			s20: if(inc) ns <= s21;
					else if(dec) ns <= s19;
					else ns <= s20;
					
			s21: if(inc) ns <= s22;
					else if(dec) ns <= s20;
					else ns <= s21;
					
			s22: if(inc) ns <= s23;
					else if(dec) ns <= s21;
					else ns <= s22;
					
			s23: if(inc) ns <= s24;
					else if(dec) ns <= s22;
					else ns <= s23;
					
			s24: if(inc) ns <= s25;
					else if(dec) ns <= s23;
					else ns <= s24;
					
			s25: if(dec) ns <= s24;
					else ns <= s25;
					
		endcase
	end
endmodule
	
module counter_25_testbench();

	logic clk, rst, inc, dec; //repeating logic variables
	logic [4:0] out;
	
	//test counter_25 module
	counter_25 dut (.clk, .rst, .inc, .dec, .out);
	
	// clock setup
	parameter clock_period = 100;
	
	initial begin
		clk <= 0;
		forever #(clock_period /2) clk = ~clk;
	end // of clock setup
	
	//an instance where it counts up to five with a
	//space after the first increment, and then
	//decrements twice
	initial begin
		rst <= 0; inc <= 1; dec <= 0; @(posedge clk);
		rst <= 0; inc <= 0; dec <= 0; @(posedge clk);
		rst <= 0; inc <= 1; dec <= 0; @(posedge clk);
		rst <= 0; inc <= 1; dec <= 0; @(posedge clk);
		rst <= 0; inc <= 1; dec <= 0; @(posedge clk);
		rst <= 0; inc <= 1; dec <= 0; @(posedge clk);
		rst <= 0; inc <= 0; dec <= 1; @(posedge clk);
		rst <= 0; inc <= 0; dec <= 0; @(posedge clk);
		$stop;
	end
endmodule 