// A frequency divider module

module freqdiv(out, clk, reset);

    // Clock period muliplier
    parameter [31:0] N = 2;

    output out;
    input wire clk, reset;

    // Internal counter
    // Note: This must be of the same type as the parameter N
    //       (unsigned int). If you declare it to be an integer
    //       it is signed twos-complement and therefore logical
    //       comparison with N will always return false!
    reg [31:0] pcount = 32'b0;
    reg [31:0] ncount = 32'b0;
    wire [31:0] count = 32'b0;
   
    //
    assign count = pcount + ncount;
        
    always @ (posedge clk)
        if (reset)
            pcount <= 0;
        else if (pcount == N-1)
            pcount <= 0;
        else
            pcount <= pcount + 1;

    always @ (negedge clk)
        if (reset)
            ncount <= 0;
        else if (ncount == N-1)
            ncount <= 0;
        else
            ncount <= ncount + 1;

    // Slow positive edge period counter
    assign out = count < N;

endmodule

