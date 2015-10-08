library ieee;
use ieee.std_logic_1164.all;

-- Two big greater than entity
entity gt_2b is
    port ( a        : in  std_logic_vector(1 downto 0); -- i0 is an input of type STD_LOGIC
           b        : in  std_logic_vector(1 downto 0);
           output   : out  std_logic);
end gt_2b;

-- The following implements a 2-bit greater than function using
-- miniterm expansion, sum of products, canonical normal form, etc
architecture behav of gt_2b is
	signal p: std_logic_vector(5 downto 0); -- Internal signals

begin
	-- sum of 6 products produces output
	output <= p(0) or p(1) or p(2) or p(3) or p(4) or p(5);
	
	-- define product terms
	p(0) <= (not a(1)) and a(0) and (not b(1)) and (not b(0));
	p(1) <= a(1) and (not a(0)) and (not b(1)) and (not b(0));
	p(2) <= a(1) and a(0) and (not b(1)) and (not b(0));
	p(3) <= a(1) and (not a(0)) and (not b(1)) and b(0);
	p(4) <= a(1) and a(0) and (not b(1)) and b(0);
	p(5) <= a(1) and a(0) and b(1) and (not b(0));

end behav;


