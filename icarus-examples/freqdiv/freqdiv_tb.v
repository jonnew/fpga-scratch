// freqdiv TESTBENCH
//
module freqdiv_tb;

    reg reset = 0;

    initial begin
        // Waveform output
        $dumpfile("freqdiv_tb.vcd");
        $dumpvars(0, freqdiv_tb);
        
        // Start in reset state
        reset = 1;

        // Enable and disable
        #1 reset = 0;
        #10 reset = 1;
        #1 $stop;
    end

    // Make a clock with a period of 1 time unit
    reg clk = 0;
    always
        #1 clk = ~clk;

    wire clk_div2;
    wire clk_div3;
    wire clk_div4;

    // Frequency dividers instantiation
    freqdiv #(2) clockdiv2(clk_div2, clk, reset);
    freqdiv #(3) clockdiv3(clk_div3, clk, reset);
    freqdiv #(4) clockdiv4(clk_div4, clk, reset);

    // Monitor
    //initial
    //    $monitor("At time %t, clk2 = %h (%0d)", $time, value, value);

endmodule
