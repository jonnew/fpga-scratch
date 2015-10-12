// Simple counter module
// - Counts positive edges of input clk
// - Store count in out
// - Reset count to 0 when reset high
module counter(out, clk, reset);

    parameter WIDTH = 8;

    // Note: Implicit contiguous assignment to 0
    //       when we delare an output register here
    output reg [WIDTH-1:0] out;
    input wire clk, reset;

    always @ (posedge clk)
        out <= out +1;

    always @ (reset)
        if (reset)
            // Contiguos assignment
            assign out = 0;
        else
            deassign out;

endmodule
