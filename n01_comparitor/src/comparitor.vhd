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

-- STD_LOGIC types are suitable for synthesis,
-- Not all VHDL types are.
entity comparitor is
    port ( i0 : in  STD_LOGIC; -- i0 is an input of type STD_LOGIC
           i1 : in  STD_LOGIC;
           o0 : out  STD_LOGIC);
end comparitor;

 -- This is the logic implementation the defines the behavior of the
-- entity, comparitor, that we just created. You can define mulitple
-- architectures for each entity

architecture sop_arch of comparitor is
	signal p0, p1: STD_LOGIC; -- Internal signals

begin
    -- These statements are concurrennt (they are executed
    -- simultaneously, unlike a procedural language. For this
    -- reason, it is possible to use variables before they are
    -- 'assigned to'

	-- sum of two products produces output
	o0 <= p0 or p1;
	
	-- define product terms
	p0 <= (not i0) and (not i1);
	p1 <= i0 and i1;

end sop_arch;

