-- Calculating gcd and lcm of given 2 numbers

class Main inherits IO{
	num1: Int;
	num2: Int;
	gcd: Int; -- gcd of num1 and num2 
	lcm: Int; -- lcm of num1 and num2
	m_num1: Int; -- modified num1
	m_num2: Int; -- modified num2
	temp: Int;
	main(): Object {{
		out_string("Enter first number\n");
		num1 <- in_int(); -- getting input of first number
		out_string("Enter second number\n");
		num2 <- in_int(); -- getting input of second number

		-- if first number is smaller then swapping the numbers
		if (num1 < num2) then
		{
			temp <- num1;
			num1 <- num2;
			num2 <- temp;
			m_num1 <- num1;
			m_num2 <- num2;
		}
		else
		{
			m_num1 <- num1;
			m_num2 <- num2;
		}
		fi;

		while (not(m_num2=0)) loop -- running loop till second number doesnt become 0
		{
			temp <- m_num1;
			m_num1 <- m_num2; 
			m_num2 <- temp - (temp/m_num2)*m_num2; -- m_num1 mod m_num2 
		}
		pool;

		gcd <- m_num1; 
		lcm <- (num1 * num2)/gcd; -- Calculating lcm

		out_string("GCD of ").out_int(num1).out_string(" and ").out_int(num2).out_string(" is ").out_int(gcd);
		out_string("\n");
		out_string("LCM of ").out_int(num1).out_string(" and ").out_int(num2).out_string(" is ").out_int(lcm);
		out_string("\n");
	}};
};