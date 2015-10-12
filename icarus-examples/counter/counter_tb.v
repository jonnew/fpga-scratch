// Simple counter module TEST BENCH
//
module counter_tb;

    reg reset = 0;

    initial begin
        // Waveform output
        $dumpfile("counter_tb.vcd");
        $dumpvars(0, counter_tb);

        // Count 17 and reset
        #17 reset = 1;

        // Count 11 and turn on
        #11 reset = 0;

        // Etc.
        #29 reset = 1;
        #11 reset = 0;
        #32000 $stop;
    end

    // Make a clock
    reg clk = 0;
    always
        #5 clk = ~clk;

    // The clock count
    // Note: Do not provide an assignment as this will
    //       be contiguous and conflict with the implicit
    //       assignment in counter module instantiation
    wire [15:0] value;

    // Counter instantiation
    counter #(16) val_count(value, clk, reset);

    // Monitor
    initial
        $monitor("At time %t, value = %h (%0d)", $time, value, value);

endmodule
