`timescale 1ns / 1ps

module eq2_testbench;

	// Inputs
	reg [1:0] a, b;

	// Outputs
	wire aeqb;

	// Instantiate the Unit Under Test (UUT)
	eq2 uut (
		.a(a), 
		.b(b), 
		.aeqb(aeqb)
	);

	initial begin
        
		// Add stimulus here
		a = 2'b00;
		b = 2'b00;
		#200
		a = 2'b01;
		b = 2'b00;
		#200
		a = 2'b01;
		b = 2'b01;
		#200
		$stop;
	end
      
endmodule

