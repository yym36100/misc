library ieee;
use ieee.std_logic_1164.all;
 
entity boolean1 is
port(
a,b,c,d: in std_logic;
x: out std_logic
);
end boolean1;
 
architecture arc of boolean1 is
begin
	x<= ((a or not b) and (b or c)) and b;
end arc;