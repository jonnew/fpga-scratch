----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    13:29:40 09/20/2014 
-- Design Name: 
-- Module Name:    comparitor_2bit - Behavioral 
-- Project Name: 
-- Target Devices: 
-- Tool versions: 
-- Description: 
--
-- Dependencies: 
--
-- Revision: 
-- Revision 0.01 - File Created
-- Additional Comments: 
--
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity comparitor_2bit is
    Port ( 
		A, B : in STD_LOGIC_VECTOR(1 downto 0);
		z : out STD_LOGIC
		);
end comparitor_2bit;

architecture eq2 of comparitor_2bit is
	signal e0, e1: STD_LOGIC;
begin
	
	-- Instaniate 2 1-bit comparitors
	comp0 : entity work.comparitor(eq1)
		port map(i0 => A(0), i1 => B(0), o0 => e0);
	comp1 : entity work.comparitor(eq1)
		port map(i0 => A(1), i1 => B(1), o0 => e1);
	
	-- Ports A and B are equal if all bits are equal
	z <= e0 and e1;
end eq2;

