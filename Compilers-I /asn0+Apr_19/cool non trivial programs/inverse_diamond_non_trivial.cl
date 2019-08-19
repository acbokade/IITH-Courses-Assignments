-- inverse diamond pattern printing

class Main inherits IO{
	i: Int;
	j: Int;
	n: Int; -- height of diamond 
	main(): Object{{

		out_string("Enter the height of diamond you want to print\n");
		n <- in_int(); -- taking input height
		--top half
		i <- 0;
		j <- 0;

		while i<n loop -- running loop for printing top portion
		{
			j <- i;
			--left portion consisting of *
			while j<n loop
			{
				out_string("*");
				j <- j+1;
			}
			pool;

			--middle portion consisting of " "
			j <- 0;
			while j<2*i+1 loop
			{
				out_string(" ");
				j <- j+1;
			}
			pool;

			--left portion consisting of *
			j <- i;
			while j<n loop
			{
				out_string("*");
				j <- j+1;
			}
			pool;
			out_string("\n");
			i <- i+1;
		}
		pool;
		
		--bottom half
		i <- 0;
		while i<n-1 loop -- running loop for printing bottom portion
		{
			j <- 0;
			--left portion consisting of *
			while j<i+2 loop
			{
				out_string("*");
				j <- j+1;
			}
			pool;

			--middle portion consisting of " "
			j <- 0;
			while j<2*(n-1-i) -1 loop
			{
				out_string(" ");
				j <- j+1;
			}
			pool;

			--left portion consisting of *
			j <- 0;
			while j<i+2 loop
			{
				out_string("*");
				j <- j+1;
			}
			pool;
			out_string("\n");
			i <- i+1;
		}
		pool;
		out_string("\n");
	}};
};