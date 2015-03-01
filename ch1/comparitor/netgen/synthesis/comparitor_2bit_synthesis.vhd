--------------------------------------------------------------------------------
-- Copyright (c) 1995-2013 Xilinx, Inc.  All rights reserved.
--------------------------------------------------------------------------------
--   ____  ____
--  /   /\/   /
-- /___/  \  /    Vendor: Xilinx
-- \   \   \/     Version: P.20131013
--  \   \         Application: netgen
--  /   /         Filename: comparitor_2bit_synthesis.vhd
-- /___/   /\     Timestamp: Sat Feb 28 19:55:50 2015
-- \   \  /  \ 
--  \___\/\___\
--             
-- Command	: -intstyle ise -ar Structure -tm comparitor_2bit -w -dir netgen/synthesis -ofmt vhdl -sim comparitor_2bit.ngc comparitor_2bit_synthesis.vhd 
-- Device	: xc3s50a-5-tq144
-- Input file	: comparitor_2bit.ngc
-- Output file	: /home/jon/Public/elbert-scratch/n01_comparitor/netgen/synthesis/comparitor_2bit_synthesis.vhd
-- # of Entities	: 1
-- Design Name	: comparitor_2bit
-- Xilinx	: /opt/xilinx/14.7/ISE_DS/ISE/
--             
-- Purpose:    
--     This VHDL netlist is a verification model and uses simulation 
--     primitives which may not represent the true implementation of the 
--     device, however the netlist is functionally correct and should not 
--     be modified. This file cannot be synthesized and should only be used 
--     with supported simulation tools.
--             
-- Reference:  
--     Command Line Tools User Guide, Chapter 23
--     Synthesis and Simulation Design Guide, Chapter 6
--             
--------------------------------------------------------------------------------

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
use UNISIM.VPKG.ALL;

entity comparitor_2bit is
  port (
    z : out STD_LOGIC; 
    a : in STD_LOGIC_VECTOR ( 1 downto 0 ); 
    b : in STD_LOGIC_VECTOR ( 1 downto 0 ) 
  );
end comparitor_2bit;

architecture Structure of comparitor_2bit is
  signal a_0_IBUF_2 : STD_LOGIC; 
  signal a_1_IBUF_3 : STD_LOGIC; 
  signal b_0_IBUF_6 : STD_LOGIC; 
  signal b_1_IBUF_7 : STD_LOGIC; 
  signal z_OBUF_9 : STD_LOGIC; 
begin
  z1 : LUT4
    generic map(
      INIT => X"9009"
    )
    port map (
      I0 => a_1_IBUF_3,
      I1 => b_1_IBUF_7,
      I2 => a_0_IBUF_2,
      I3 => b_0_IBUF_6,
      O => z_OBUF_9
    );
  a_1_IBUF : IBUF
    port map (
      I => a(1),
      O => a_1_IBUF_3
    );
  a_0_IBUF : IBUF
    port map (
      I => a(0),
      O => a_0_IBUF_2
    );
  b_1_IBUF : IBUF
    port map (
      I => b(1),
      O => b_1_IBUF_7
    );
  b_0_IBUF : IBUF
    port map (
      I => b(0),
      O => b_0_IBUF_6
    );
  z_OBUF : OBUF
    port map (
      I => z_OBUF_9,
      O => z
    );

end Structure;

