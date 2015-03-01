library ieee;
use ieee.std_logic_1164.ALL;
 

-- Testbench for the 2-bit greater than entity
entity gt_2b_tb is
end gt_2b_tb;
 
architecture behavior of gt_2b_tb is 
    
    -- Component Declaration for the Unit Under Test (UUT)
    
    component gt_2b
    port(
         a : IN  std_logic_vector(1 downto 0);
         b : IN  std_logic_vector(1 downto 0);
         output : OUT  std_logic
        );
    end component;
     
    
    --Inputs
    signal a : std_logic_vector(1 downto 0) := (others => '0');
    signal b : std_logic_vector(1 downto 0) := (others => '0');
    
    --Outputs
    signal output : std_logic;
     
    begin
    
        -- Instantiate the Unit Under Test (UUT)
        uut: gt_2b port map (
               a => a,
               b => b,
               output => output
             );
    process
    begin
        -- Test vector 
        a <= "00";
        b <= "00";
        wait for 200 ns;        
        -- Test vector 
        a <= "00";
        b <= "01";
        wait for 200 ns;
        -- Test vector 
        a <= "00";
        b <= "10";
        wait for 200 ns;
        -- Test vector 
        a <= "00";
        b <= "11";
        wait for 200 ns;
        -- Test vector 
        a <= "01";
        b <= "00";
        wait for 200 ns;
        -- Test vector 
        a <= "01";
        b <= "01";
        wait for 200 ns;
        -- Test vector
        a <= "01";
        b <= "10";
        wait for 200 ns;
        -- Test vector
        a <= "01";
        b <= "11";
        wait for 200 ns;
        -- Test vector
        a <= "10";
        b <= "00";
        wait for 200 ns;
        -- Test vector 
        a <= "11";
        b <= "11";
        -- Test vector
        wait for 200 ns;
        a <= "10";
        b <= "00";
        wait for 200 ns;
         -- Test vector 
        a <= "01";
        b <= "00";
        wait for 200 ns;
         -- Test vector
        a <= "11";
        b <= "10";
        wait for 200 ns;
         -- Test vector 
        a <= "10";
        b <= "11";
        wait for 200 ns;
 
        assert false
            report "Simulation complete."
            severity failure;
    end process;
    
end behavior;

