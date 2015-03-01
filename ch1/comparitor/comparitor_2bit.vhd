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
library ieee;
use ieee.std_logic_1164.all;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity comparitor_2bit is
    Port ( 
		-- Since this is a top-level file, these signal names actually
		-- correspond to physical pins as specified in the ucf.
		a, b : in std_logic_vector(1 downto 0);
		z : out std_logic
		);
end comparitor_2bit;

architecture eq2 of comparitor_2bit is
	signal e0, e1: std_logic;
begin
	
    -- Instaniate 2 1-bit comparitors using 'component instantiation'
    -- A component instantiation uses the following template
    --
    -- unit_label: entity lib_name.entity_name(arch_name)
    --     port map(
    --         formal_signal => actual _signal
    -- );
    -- A couple things to note:
    -- 1.   The work library is the default lib in which compiled objects
    --      are stored
    -- 2.   Formal signals are i/o ports decplared in the component and
    --      Actual signals are those used in the current arch body

	comp0 : entity work.comparitor(sop_arch)
		port map(i0 => a(0), i1 => b(0), o0 => e0);
	comp1 : entity work.comparitor(sop_arch)
		port map(i0 => a(1), i1 => b(1), o0 => e1);
	
	-- Ports A and B are equal if all bits are equal
	z <= e0 and e1;
end eq2;

