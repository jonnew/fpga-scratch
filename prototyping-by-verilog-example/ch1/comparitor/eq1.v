// Timescale directive
// 1ns = simulation time unit
// 1ps = stimulation time step
`timescale 1ns / 1ps

// 1-bit equality comparitor
module eq1

	 // (1) IO ports decl.
	 (
		input wire i0, i1,
		output wire eq
    );
	 
	 // (2) Signal decl.
	 wire p0, p1;
	 
	 // (3) Body
	 // Sum of products
	 assign eq = p0 | p1;
	 assign p0 = ~i0 & ~i1;
	 assign p1 = i0 & i1;
	 
endmodule
