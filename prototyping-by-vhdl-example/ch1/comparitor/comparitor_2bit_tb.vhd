--------------------------------------------------------------------------------
-- Company: 
-- Engineer:
--
-- Create Date:   19:51:47 02/28/2015
-- Design Name:   
-- Module Name:   /home/jon/Public/elbert-scratch/n01_comparitor/comparitor_2bit_tb.vhd
-- Project Name:  n01_comparitor
-- Target Device:  
-- Tool versions:  
-- Description:   
-- 
-- VHDL Test Bench Created by isE for module: comparitor_2bit
-- 
-- Dependencies:
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
--
-- Notes: 
-- This testbench has been automatically generated using types std_logic and
-- std_logic_vector for the ports of the unit under test.  Xilinx recommends
-- that these types always be used for the top-level I/O of a design in order
-- to guarantee that the testbench will bind correctly to the post-implementation 
-- simulation model.
--------------------------------------------------------------------------------
library ieee;
use ieee.std_logic_1164.ALL;
 
-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--USE ieee.numeric_std.ALL;

entity comparitor_2bit_tb is
end comparitor_2bit_tb;
 
architecture  behavior of comparitor_2bit_tb is 
    
    -- Component Declaration for the Unit Under Test (UUT)
    
    component comparitor_2bit
    port(
         a : IN  std_logic_vector(1 downto 0);
         b : IN  std_logic_vector(1 downto 0);
         z : OUT  std_logic
        );
    end component;
     
    
    --Inputs
    signal a : std_logic_vector(1 downto 0) := (others => '0');
    signal b : std_logic_vector(1 downto 0) := (others => '0');
    
     --Outputs
    signal z : std_logic;
     
    begin
    
        -- Instantiate the Unit Under Test (UUT)
        uut: comparitor_2bit port map (
               a => a,
               b => b,
               z => z
             );
        
        -- Clock process definitions
    process
    begin
        
        -- Test vector 1
        a <= "00";
        b <= "01";
        wait for 200 ns;
        -- Test vector 1
        a <= "00";
        b <= "10";
        wait for 200 ns;
        -- Test vector 1
        a <= "00";
        b <= "11";
        wait for 200 ns;
        -- Test vector 1
        a <= "01";
        b <= "00";
        wait for 200 ns;
        -- Test vector 1
        a <= "01";
        b <= "01";
        wait for 200 ns;
        -- Test vector 1
        a <= "01";
        b <= "10";
        wait for 200 ns;
        -- Test vector 1
        a <= "01";
        b <= "11";
        wait for 200 ns;
        -- Test vector 1
        a <= "10";
        b <= "00";
        wait for 200 ns;
        -- Test vector 1
        a <= "11";
        b <= "11";
        wait for 200 ns;
        assert false
            report "Simulation complete."
            severity failure;
    end process;
    
end behavior;
