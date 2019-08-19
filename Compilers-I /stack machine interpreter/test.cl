-- Ajinkya Bokade
-- CS17BTECH11001

class MyStack inherits IO{
	isNil(): Bool{true};

	getTop(): String{
		{
			abort();
			"";
		}
	};

	getBottom(): MyStack{
		{
			abort();
			self;
		}
	};

	push(str: String): MyStack{
		(new ConsStack).init(str, self)
	};

	pop(): String{
		""
	};

	(*display(): MyStack{
		self
	};*)
};

class ConsStack inherits MyStack{
	top: String;
	bottom: MyStack;

	isNil(): Bool{false};
	
	getTop(): String{
		top
	};

	getBottom(): MyStack{
		bottom
	};

	init(str: String, rest: MyStack): MyStack{
		{
			top <- str;
			bottom <- rest;
			self;
		}
	};

	pop(): String{
		let topStr: String <- top in 
		{
			top <- bottom.getTop();
			bottom <- bottom.getBottom();
			topStr;
		}
	};

	(*display(): MyStack{
		{
			if not top = ""
			then out_string(top).out_string("\n")
			else false
			fi;
			bottom.display();
			self;
		}
	};*)
};

class Main inherits IO{
	flag: Bool <- true;
	input: String;
	newStack: MyStack;
	atoiFunc: A2I <- new A2I;

	(*display(stack: MyStack): Object{
		if stack.isNil() then out_string("\n")
		else
		{
			out_string(stack.getTop()).out_string("\n");
			display(stack.getBottom());
		}
		fi
	};*)

	additionEvaluate(stack: MyStack): Object{
		let first: String <- stack.pop(), second: String <- stack.pop() in
		{
			stack.push(atoiFunc.i2a(atoiFunc.a2i(first) + atoiFunc.a2i(second)));
		}

	};

	swap(stack: MyStack): Object{
		let first: String <- stack.pop(), second: String <- stack.pop() in
		{
			stack.push(first);
			stack.push(second);
		}
	};	

	temp: String;

	main(): Object{
		{
			newStack <- new MyStack;
			temp <-in_string();
			newStack.push(temp);
			out_string(newStack.getTop());
		}
	};
};
