ENTITY mymux IS
PORT (
	a, b, c, d : IN BIT;
	s0, s1 : IN BIT;
	x : OUT BIT
);
END mymux;

ARCHITECTURE dataflow OF mymux IS
SIGNAL ss : INTEGER;
BEGIN
ss <= 0 WHEN s0 = '0' AND s1 = '0' ELSE
		1 WHEN s0 = '1' AND s1 = '0' ELSE
		2 WHEN s0 = '0' AND s1 = '1' ELSE
		3;
		
x <=  a  WHEN ss = 0 ELSE
		b  WHEN ss = 1 ELSE
		c  WHEN ss = 2 ELSE
		d ;
END dataflow;