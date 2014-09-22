--------------------------------------------------------------------------------
-- Company: 
-- Engineer:
--
-- Create Date:   13:47:22 09/20/2014
-- Design Name:   
-- Module Name:   /home/jon/Public/elbert-scratch/00_1-bit-comparitor/comparitor/comparitor_test.vhd
-- Project Name:  comparitor
-- Target Device:  
-- Tool versions:  
-- Description:   
-- 
-- VHDL Test Bench Created by ISE for module: comparitor_2bit
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
LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
 
-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--USE ieee.numeric_std.ALL;
 
ENTITY comparitor_test IS
END comparitor_test;
 
ARCHITECTURE behavior OF comparitor_test IS 

   --Inputs
   signal A : std_logic_vector(1 downto 0) := (others => '0');
   signal B : std_logic_vector(1 downto 0) := (others => '0');

 	--Outputs
   signal z : std_logic;

 
BEGIN
 
	-- Instantiate the Unit Under Test (UUT)
   uut: entity work.comparitor_2bit(eq2) PORT MAP (
          A => A,
          B => B,
          z => z
        );

   -- Stimulus process
   stim_proc: process
   begin		
      -- hold reset state for 100 ns.
      wait for 100 ns;	

      -- insert stimulus here 
		A <= "00";
		B <= "00";
		wait for 200 ns;
		
		A <= "01";
		B <= "00";
		wait for 200 ns;
		
		A <= "01";
		B <= "11";
		wait for 200 ns;
		
		A <= "10";
		B <= "10";
		wait for 200 ns;
		
		A <= "10";
		B <= "00";
		wait for 200 ns;
		
		A <= "11";
		B <= "11";
		wait for 200 ns;
		
		A <= "11";
		B <= "01";
		wait for 200 ns;
		
   end process;

END;
