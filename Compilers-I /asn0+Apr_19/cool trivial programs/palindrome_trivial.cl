-- checking if a given string is a palindrome or not

class Main inherits IO {
	main():Object{{
		out_string("Enter the string to check if its palindrome or not\n");
		let input: String <- in_string() in -- taking input string
		if(isPalindrome(input)) then
			out_string("Yes, The given string is a palindrome\n")
		else
			out_string("No, The given string isn't a palindrome\n")
		fi;
	}};

	-- function to check if string is palindrome or not
	isPalindrome(str: String): Bool{
		if str.length() = 0 then -- if length is 0 then string is palindrome
			true
		else if str.length() = 1 then -- if length is 1 then string is palindrome
			true
		else if str.substr(0,1) = str.substr(str.length()-1,1) then  -- if first letter from start and corresponding letter from end is same then recursing it
			isPalindrome(str.substr(1,str.length()-2))
		else -- if first letter from start is not equal to corresponding letter from end then string cant be palindrome
			false
		fi fi fi
	};
};