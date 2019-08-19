-- Ajinkya Bokade
-- CS17BTECH11001
-- Programming Assignment 2: Stack Machine interpreter

-- Class for stack 
-- Implementation is done same as that of list
-- There are 2 kinds of stacks, MyStack and ConsStack
-- MyStack defines operations for empty stack
-- ConsStack is specializtion of MyStack and inherits
-- from MyStack and defines operations for non-empty stack
class MyStack inherits IO{
	-- This class is basically used for operations of empty stack
	-- Always returns true since the stack is empty
	isNil(): Bool{true};

	-- Since stack is empty returns empty string
	getTop(): String{
		""
	};

	-- returns the empty stack
	getBottom(): MyStack{
		self
	};

   	-- First, we check if string which we passed is empty or not
   	-- If, it is empty then we just return stack
   	-- If, its not then we just call ConsStack init method which
   	-- pushes the input to stack
	push(str: String): MyStack{
		if not str = "" then
			(new ConsStack).init(str, self)
		else
			self
		fi
	};

	--Since stack is empty we just return empty string
	pop(): String{
		""
	};

	--Since the stack is empty we dont print anything
	printStack(): MyStack{
		self
	};
};

-- This class defines operations for non empty stack
-- It inherits from class MyStack
class ConsStack inherits MyStack{
	-- Represents the top element of stack
	top: String;
	-- Represents stack except top element
	bottom: MyStack;

	-- Since stack is non-empty, it return false
	isNil(): Bool{false};

	-- return top element of stack
	getTop(): String{
		top
	};

	-- returns stack except top element
	getBottom(): MyStack{
		bottom
	};

	-- method to create new stack taking string as input
	-- and a stack and creating a new stack with input as top
	-- element and stack as its bottom
	init(str: String, rest: MyStack): MyStack{
		{
			top <- str;
			bottom <- rest;
			self;
		}
	};

	-- removes top element from stack and returns it
	pop(): String{
		let topStr: String <- top in 
		{
			top <- bottom.getTop();
			bottom <- bottom.getBottom();
			topStr;
		}
	};

	-- prints all the elements of stack
	printStack(): MyStack{
		{
			if not top = "" -- if stack still contains non empty string we print it
			then out_string(top).out_string("\n") 
			else false -- if stack now contains empty string then we return false
			fi;
			bottom.printStack(); -- recurse to print remaining elements of stack except top
			self;
		}
	};
};

-- Main class
class Main inherits IO{
	flag: Bool <- true;
	input: String;
	newStack: MyStack; -- newStack
	-- creating object of atoi A2I class defined in atoi.cl file
	-- used to convert string to integer and vice versa
	-- used in additionEvaluate function defined later
	atoiFunc: A2I <- new A2I; 

	-- This pops top 2 elements from stack and adds them
	-- and pushes resulting sum to stack
	additionEvaluate(stack: MyStack): MyStack{
		let first: String <- stack.pop(), second: String <- stack.pop() in
		{
			stack <- stack.push(atoiFunc.i2a(atoiFunc.a2i(first) + atoiFunc.a2i(second)));
			stack;
		}

	};

	-- This pops top 2 elements from stack and pushes 1st element 
	-- from top to stack and then 2nd element from top
	swap(stack: MyStack): MyStack{
		let first: String <- stack.pop(), second: String <- stack.pop() in
		{
			stack <- stack.push(first);
			stack <- stack.push(second);
			stack;
		}
	};

	(*-- prints all the elements of stack
	displayStack(stack: MyStack): Object{
		if stack.isNil() 
			then out_string("")
        else 
        {
            out_string(stack.getTop()).out_string("\n");
           	displayStack(stack.getBottom());
        }
      fi
	};*)	

	main(): Object{
		{
			-- creating new MyStack object
			newStack <- new MyStack;
			while (flag = true) loop
			{
				-- prompt asking for input
				out_string(">");
				-- getting input as string
				input <- in_string();

				-- if input is "e", we check the top element of stack
				-- and if it is "+", we call additionEvaluate method 
				-- and if it is "s", we call swap method
				if (input = "e") then {
					let temp: String <- newStack.pop() in 
						{
							if (temp = "+") then
								newStack <- additionEvaluate(newStack)
							else if (temp = "s") then
								newStack <- swap(newStack)
							else
								newStack <- newStack.push(temp)
							fi fi;
						};
				}

				-- if input is "d", then we print all the contents of stack
				else if ( input = "d") then{
					newStack.printStack();
				}

				-- if input is "x", then we terminate loop by setting flag as false
				-- so that interpreter exits gracefully

				else if (input = "x") then{
					flag <- false;
				}

				-- else we push the given input to the stack
				else{
					newStack <- newStack.push(input);
				}
				fi fi fi;
			}
			pool;
		}
	};
};
