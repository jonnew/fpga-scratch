----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    18:31:38 09/21/2014 
-- Design Name: 
-- Module Name:    struct_desc - Behavioral 
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

entity struct_desc is
    Port ( Switch	 : in  STD_LOGIC_VECTOR (4 downto 0);
           DPSwitch : in STD_LOGIC_VECTOR (7 downto 0);
			  LED : out  STD_LOGIC_VECTOR (7 downto 0));
end struct_desc;

architecture Behavioral of struct_desc is
begin

	-- Instantiate an input_select
	input_select_0 : entity work.input_select(Behavioral)
		port map(S=>Switch(4 downto 1), O=>LED(7 downto 4));
	
	-- Instantiate a decoder_2_4
	decoder_2_4_0 : entity work.decoder_2_4(Behavioral)
		port map(A=>DPSwitch(1 downto 0), en=>Switch(0), Z=>LED(3 downto 0));

end Behavioral;

