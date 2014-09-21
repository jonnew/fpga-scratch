--------------------------------------------------------------------------------
-- Company: 
-- Engineer:
--
-- Create Date:   13:05:51 09/20/2014
-- Design Name:   
-- Module Name:   /home/jon/Public/elbert-scratch/00_1-bit-comparitor/comparitor/comparitor_testbench.vhd
-- Project Name:  comparitor
-- Target Device:  
-- Tool versions:  
-- Description:   
-- 
-- VHDL Test Bench Created by ISE for module: comparitor
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
 
ENTITY comparitor_testbench IS
END comparitor_testbench;
 
ARCHITECTURE behavior OF comparitor_testbench IS 
 
    -- Component Declaration for the Unit Under Test (UUT)
 
    COMPONENT comparitor
    PORT(
         A : IN  std_logic;
         B : IN  std_logic;
         Z : OUT  std_logic
        );
    END COMPONENT;
    

   --Inputs
   signal A : std_logic := '0';
   signal B : std_logic := '0';

 	--Outputs
   signal Z : std_logic;
   -- No clocks detected in port list. Replace <clock> below with 
   -- appropriate port name 
 
   constant <clock>_period : time := 10 ns;
 
BEGIN
 
	-- Instantiate the Unit Under Test (UUT)
   uut: comparitor PORT MAP (
          A => A,
          B => B,
          Z => Z
        );

   -- Clock process definitions
   <clock>_process :process
   begin
		<clock> <= '0';
		wait for <clock>_period/2;
		<clock> <= '1';
		wait for <clock>_period/2;
   end process;
 

   -- Stimulus process
   stim_proc: process
   begin		
      -- hold reset state for 100 ns.
      wait for 100 ns;	

      wait for <clock>_period*10;

      -- insert stimulus here 

      wait;
   end process;

END;
