`timescale 1ns / 1ps

// 2-bit equality comparitor
module eq2

	// (1) IO Ports
	 (
	 input wire[1:0] a, b,
	 output wire aeqb
	 );
	 
	 // (2) Signal decl.
	 wire e0, e1;
	 
	 // (3) Body
	 eq1 eq_b0 (.i0(a[0]), .i1(b[0]), .eq(e0));
	 eq1 eq_b1 (.i0(a[1]), .i1(b[1]), .eq(e1));
	 
	 assign aeqb = e0 & e1;

endmodule
