class Main inherits IO {
	vec1: Vector; -- first vector
	vec2: Vector; -- second vector
	x1: Int; -- x component of first vector
	y1: Int; -- y component of first vector
	z1: Int; -- z component of first vector
	x2: Int; -- x component of second vector
	y2: Int; -- y component of second vector
	z2: Int; -- z component of second vector
	main(): Object{{
		-- taking inputs for components of vectors
		out_string("Enter the x component of first vector\n ");
		x1 <- in_int();
		out_string("Enter the y component of first vector\n ");
		y1 <- in_int();
		out_string("Enter the z component of first vector\n ");
		z1 <- in_int();
		out_string("Enter the x component of second vector\n ");
		x2 <- in_int();
		out_string("Enter the y component of second vector\n ");
		y2 <- in_int();
		out_string("Enter the z component of second vector\n ");
		z2 <- in_int();
		vec1 <- new Vector.init(x1,y1,z1); -- initializing first vector
		vec2 <- new Vector.init(x2,y2,z2); -- initializing second vector
		out_string("Enter 1 to add the vectors\n");
		out_string("Enter 2 to subtract the vectors\n");
		out_string("Enter 3 to calculate dot product of the vectors\n");
		out_string("Enter 4 to calculate cross product of the vectors\n");
		let temp: Int <- in_int() in
		if (temp = 1) then
		{
			vec1.addVectors(vec2);
			vec1.printVector(vec1);
		}
		else if (temp = 2) then
		{
			vec1.subtractVectors(vec2);
			vec1.printVector(vec1);
		}
		else if (temp = 3) then
		{
			out_string("The dot product is ").out_int(vec1.dotProduct(vec2)).out_string("\n");
		}
		else 
		{
			vec1.crossProduct(vec2);
			vec1.printVector(vec1);
		}
		fi fi fi;
	}};
};

-- Implementation of vector

class Vector inherits IO {
	x: Int; -- x component of vector
	y: Int; -- y component of vector
	z: Int; -- z component of vector

	-- initializing vector
	init(x_comp: Int, y_comp: Int, z_comp: Int): Vector{
		{
			x <- x_comp;
			y <- y_comp;
			z <- z_comp;
			self;
		}
	};

	-- getter for x component
	getX():Int{
		x
	};

	-- getter for y component
	getY():Int{
		y
	};

	-- getter for z component
	getZ():Int{
		z
	};

	-- adding current vector to vector given as parameter
	addVectors(v: Vector): Vector{
		{
			x <- x + v.getX();
			y <- y + v.getY();
			z <- z + v.getZ();
			self;
		}
	};

	-- subtracting current vector to vector given as parameter
	subtractVectors(v: Vector): Vector{
		{
			x <- x - v.getX();
			y <- y - v.getY();
			z <- z - v.getZ();
			self;
		}		
	};

	--  taking dot product of current vector and vector given as parameter
	dotProduct(v: Vector): Int{
			x * v.getX() + y * v.getY() + z * v.getZ()
	};

	-- taking cross product of current vector and vector given as parameter
	crossProduct(v: Vector): Object{
			let temp1: Int <- x in
			let temp2: Int <- y in
			let temp3: Int <- z in
			{
				x <- temp2*v.getZ() - temp3*v.getY();
				y <- temp3*v.getX() - temp1*v.getZ();
				z <- temp1*v.getY() - temp2*v.getX();
			}
	};

	-- printing all components of vector
	printVector(v: Vector): Object{
		{
			out_string("The resulting vector is (").out_int(v.getX()).out_string(", ").out_int(v.getY()).out_string(", ").out_int(v.getZ()).out_string(")\n");
			self;
		}
	};
};
