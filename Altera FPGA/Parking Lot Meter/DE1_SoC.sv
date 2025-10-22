/*
	This module instantiates all of my submodules for the
  parking lot task. It has V_GPIO inputs, and LED outputs
	on the simulator. It has HEX display outputs onto the FPGA,
	and KEY0 and Switch9 inputs.
*/

module DE1_SoC (CLOCK_50, HEX0, HEX1, HEX2, HEX3, HEX4, HEX5, KEY, SW, LEDR, V_GPIO);

	// define ports
	input  logic CLOCK_50;
	output logic [6:0] HEX0, HEX1, HEX2, HEX3, HEX4, HEX5;
	input  logic [3:0] KEY; // KEY0 to advance day
	input  logic [9:0] SW; // SW9 as reset
	output logic [9:0] LEDR;
	inout  logic [35:23] V_GPIO;

	// FPGA output
	assign V_GPIO[26] = V_GPIO[28];	// LED parking 1
	assign V_GPIO[27] = V_GPIO[29];	// LED parking 2
	assign V_GPIO[32] = V_GPIO[30];	// LED parking 3
	assign V_GPIO[34] = (V_GPIO[28] && V_GPIO[29] && V_GPIO[30]);	// LED full
	assign V_GPIO[31] = LEDR[3];	// Open entrance
	assign V_GPIO[33] = LEDR[4];	// Open exit

	// FPGA input
	assign LEDR[0] = V_GPIO[28];	// Presence parking 1
	assign LEDR[1] = V_GPIO[29];	// Presence parking 2
	assign LEDR[2] = V_GPIO[30];	// Presence parking 3
	assign LEDR[3] = V_GPIO[23];	// Presence entrance
	assign LEDR[4] = V_GPIO[24];	// Presence exit
	
/***
counting for parking spot 1
***/
	logic car1; //car1 input
	logic [4:0] spot1; //spot1 total cars for day
	singlePress P1 (.clk(CLOCK_50), .rst(SW[9]), .key(V_GPIO[28]), .onePress(car1));
	counter_25 space1 (.clk(CLOCK_50), .rst(SW[9]), .inc(car1), .dec(1'b0), .out(spot1));
	
/***
counting for parking spot 2
***/
	logic car2; //car2 input
	logic [4:0] spot2; //spot2 total cars for day
	singlePress P2 (.clk(CLOCK_50), .rst(SW[9]), .key(V_GPIO[29]), .onePress(car2));
	counter_25 space2 (.clk(CLOCK_50), .rst(SW[9]), .inc(car2), .dec(1'b0), .out(spot2));
	
/***
counting for parking spot 3
***/
	logic car3; //car3 input
	logic [4:0] spot3; //spot3 total cars for day
	singlePress P3 (.clk(CLOCK_50), .rst(SW[9]), .key(V_GPIO[30]), .onePress(car3));
	counter_25 space3 (.clk(CLOCK_50), .rst(SW[9]), .inc(car3), .dec(1'b0), .out(spot3));
	
//TIME (HOUR) INCREMENTER
	logic [3:0] hour; //current hour
	logic inc_hour; //incrementing hour
	singlePress SP (.clk(CLOCK_50), .rst(1'b0), .key(~KEY[0]), .onePress(inc_hour));
	hour_time tracker (.clk(CLOCK_50), .rst(SW[9]), .inc(inc_hour), .hour(hour));
	
//RUSH HOUR TRACKING
	logic [3:0] rush_start; //start of rush hour
	logic [3:0] rush_end; // end of rush hour
	rush_hour log (.clk(CLOCK_50), .rst(SW[9]), .car1(V_GPIO[28]), .car2(V_GPIO[29]), 
		.car3(V_GPIO[30]), .hour(hour), .rush_start(rush_start), .rush_end(rush_end));
	
//RAM inputs
	logic [15:0] total; // total cars for the day at that point in the day
	assign total = spot1 + spot2 + spot3;
	logic [15:0] whole_day; // output of ram of total
	ram8x16 ram (.clock(CLOCK_50), .data(total), .rdaddress(rdaddress), 
					.wraddress(hour), .wren(inc_hour), .q(whole_day));
					
	logic [3:0] rdaddress;
	always_ff @(posedge CLOCK_50) begin
		if(hour != 4'b1000) begin
			rdaddress <= hour;
		end else begin
			rdaddress <= scroll;
	end end
	
//RAM Scroll	
	logic [31:0] clock;
	clock_divider cdiv (.clock(CLOCK_50), .divided_clocks(clock));
	logic scroll_start;
	singlePress hour8 (.clk(CLOCK_50), .rst(SW[9]), 
					.key(hour == 4'b1000), .onePress(scroll_start));
	logic [3:0] scroll;
	scroller scrl (.clk(clock[25]), .rst(scroll_start), .out(scroll));
	
	
	/**********\
	HEX DISPLAYS
	\**********/
	
// HEXES 0-3
	//logic for during the day, showing lot space
	logic [1:0] cars;
	assign cars = (V_GPIO[28] + V_GPIO[29] + V_GPIO[30]);
	logic [6:0] hexzero;
	logic [6:0] hexone;
	logic [6:0] hextwo;
	logic [6:0] hexthree;
	lot_spots LS (.cars(cars), .hx0(hexzero), .hx1(hexone), 
									.hx2(hextwo), .hx3(hexthree));
									
	//logic for end of day parking information
	logic [6:0] hexone_data;
	logic [6:0] hextwo_addr;
	logic [3:0] lot_data;
	assign lot_data = whole_day[3:0];
	hexadecimal hx1 (.in(lot_data), .out(hexone_data));
	hexadecimal hx2 (.in(rdaddress), .out(hextwo_addr));
	
	//clocked always to switch between data
	logic [6:0] hexzero_fin;
	logic [6:0] hexone_fin;
	logic [6:0] hextwo_fin;
	logic [6:0] hexthree_fin;
	always_ff @(posedge CLOCK_50) begin
		if(hour != 4'b1000) begin
			hexzero_fin <= hexzero;
			hexone_fin <= hexone;
			hextwo_fin <= hextwo;
			hexthree_fin <= hexthree;
		end else begin
			hexzero_fin <= 7'b1111111;
			hexone_fin <= hexone_data;
			hextwo_fin <= hextwo_addr;
			if(rush_start == 4'b1111) begin
				hexthree_fin <= 7'b0111111;
			end else begin
				hexthree_fin <= hexthree_rush;
	end end end
	
	//logic for if the day has ended and there is no rush hour
	logic [6:0] hexthree_rush;
	hexadecimal hx3 (.in(rush_start), .out(hexthree_rush));
	
	assign HEX0 = hexzero_fin;
	assign HEX1 = hexone_fin;
	assign HEX2 = hextwo_fin;
	assign HEX3 = hexthree_fin;
// END OF HEXES 0-3
	
// HEXES 4-5
	logic [6:0] hexfour;
	logic [6:0] hexfive;
	logic [6:0] hexfive_hour;
	logic [6:0] hexfour_final;
	logic [6:0] hexfive_final;
	
	//hex display converters
	hexadecimal hx4_rush (.in(rush_end), .out(hexfour));
	hexadecimal hx5_hour (.in(hour), .out(hexfive_hour));
	
	//flip flops to allow the hex to display
	//different datapaths during and after the day
	always_ff @(posedge CLOCK_50) begin
		if(hour != 4'b1000) begin
			hexfour_final <= 7'b1111111;
			hexfive_final <= hexfive_hour;
		end else begin
			if(rush_end == 4'b1111) begin
				hexfour_final <= 7'b0111111;
			end else begin
				hexfour_final <= hexfour; end
			hexfive_final <= 7'b1111111;	
	end end
	
	//giving the hexes inputs
	assign HEX4 = hexfour_final;
	assign HEX5 = hexfive_final;
// END OF HEXES 4-5
		

endmodule  // DE1_SoC
//testbench
`timescale 1ps/1ps
module DE1_SoC_tb ();
	//define ports
	logic CLOCK_50;
   logic [6:0] HEX0, HEX1, HEX2, HEX3, HEX4, HEX5;
   logic [3:0] KEY; // KEY0 to advance day
	logic [9:0] SW; // SW9 as reset
	logic [9:0] LEDR;
	logic [35:23] V_GPIO;
	
	DE1_SoC dut (.CLOCK_50, .HEX0, .HEX1, .HEX2, .HEX3, .HEX4, .HEX5, .KEY, .SW, .LEDR, .V_GPIO);
	
	//clock setup
	parameter clock_pd = 100;
	initial begin
		CLOCK_50 <= 0;
		forever #(clock_pd /2) CLOCK_50 <= ~CLOCK_50;
	end //of clock setup
	
	//tests an instance where a car joins hour 1, another joins hour 3
	//a third joins hour 5, and they all leave hour 7
	initial begin
		SW[9] <= 0; KEY[0] <= 0; V_GPIO[30:28] <= 3'b000; @(posedge CLOCK_50); //hour 0
		SW[9] <= 0; KEY[0] <= 1; V_GPIO[30:28] <= 3'b000; @(posedge CLOCK_50);
		SW[9] <= 0; KEY[0] <= 0; V_GPIO[30:28] <= 3'b001; @(posedge CLOCK_50); //hour 1
		SW[9] <= 0; KEY[0] <= 0; V_GPIO[30:28] <= 3'b001; @(posedge CLOCK_50);
		SW[9] <= 0; KEY[0] <= 0; V_GPIO[30:28] <= 3'b001; @(posedge CLOCK_50); //hour 2
		SW[9] <= 0; KEY[0] <= 0; V_GPIO[30:28] <= 3'b001; @(posedge CLOCK_50);
		SW[9] <= 0; KEY[0] <= 0; V_GPIO[30:28] <= 3'b011; @(posedge CLOCK_50); //hour 3
		SW[9] <= 0; KEY[0] <= 0; V_GPIO[30:28] <= 3'b011; @(posedge CLOCK_50);
		SW[9] <= 0; KEY[0] <= 0; V_GPIO[30:28] <= 3'b011; @(posedge CLOCK_50); //hour 4
		SW[9] <= 0; KEY[0] <= 0; V_GPIO[30:28] <= 3'b011; @(posedge CLOCK_50);
		SW[9] <= 0; KEY[0] <= 0; V_GPIO[30:28] <= 3'b111; @(posedge CLOCK_50); //hour 5
		SW[9] <= 0; KEY[0] <= 0; V_GPIO[30:28] <= 3'b111; @(posedge CLOCK_50);
		SW[9] <= 0; KEY[0] <= 0; V_GPIO[30:28] <= 3'b111; @(posedge CLOCK_50); //hour 6
		SW[9] <= 0; KEY[0] <= 0; V_GPIO[30:28] <= 3'b111; @(posedge CLOCK_50);
		SW[9] <= 0; KEY[0] <= 0; V_GPIO[30:28] <= 3'b000; @(posedge CLOCK_50); //hour 7
		SW[9] <= 0; KEY[0] <= 0; V_GPIO[30:28] <= 3'b000; @(posedge CLOCK_50);
		SW[9] <= 0; KEY[0] <= 0; V_GPIO[30:28] <= 3'b000; @(posedge CLOCK_50);//closing time
		SW[9] <= 0; KEY[0] <= 0; V_GPIO[30:28] <= 3'b000; @(posedge CLOCK_50);
		SW[9] <= 0; KEY[0] <= 0; V_GPIO[30:28] <= 3'b000; @(posedge CLOCK_50);//scroll time
		$stop;
	end //of test
endmodule 