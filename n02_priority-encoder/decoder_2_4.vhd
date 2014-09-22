----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    18:02:05 09/21/2014 
-- Design Name: 
-- Module Name:    decoder_2_4 - Behavioral 
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

entity decoder_2_4 is
    Port ( A : in  STD_LOGIC_VECTOR (1 downto 0);
           en : in  STD_LOGIC;
           Z : out  STD_LOGIC_VECTOR (3 downto 0));
end decoder_2_4;

architecture Behavioral of decoder_2_4 is
begin
	Z <= 	"0000" when (en='0') else
			"0001" when (A="00") else
			"0010" when (A="01") else
			"0100" when (A="10") else
			"1000"; -- No condition checking req'd

end Behavioral;

