----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    12:51:59 09/20/2014 
-- Design Name: 
-- Module Name:    comparitor - Behavioral 
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

entity comparitor is
    port ( i0 : in  STD_LOGIC;
           i1 : in  STD_LOGIC;
           o0 : out  STD_LOGIC);
end comparitor;

architecture eq1 of comparitor is
	signal p0: STD_LOGIC;
	signal p1: STD_LOGIC;

begin
	-- sum of two products produces output
	o0 <= p0 or p1;
	
	-- define product terms
	p0 <= (not i0) and (not i1);
	p1 <= i0 and i1;

end eq1;

