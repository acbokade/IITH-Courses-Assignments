-- printing floyd traingle

class Main inherits IO {
  main(): Object {{
    out_string("Enter the height of floyd triangle\n");
    let n: Int <- in_int() in -- taking input of height of floyd triangle
    let i: Int <- 0, val: Int <- 1 in
    	while (i<n) loop -- running loop till row becomes height
    	{
    		let j: Int <-0 in
    			while (j<=i) loop
    			{
    				out_int(val).out_string(" "); -- printing current value
    				val <- val + 1;
    				j <- j+1;
    			}
    			pool;
    			out_string("\n");
    		i <- i+1;
    	}
    	pool;
  }};
};