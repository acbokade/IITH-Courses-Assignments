class Main inherits IO {
  main(): Object {{
  	let input: Bool <- True in -- Boolean constants true and false are case sensitive (first letter of true and false must be lowercase)
  	let pool: Int <- in_int() in -- pool is a reserved keyword in cool, hence can't be used as variable
  	out_int(pool);
  }};
};

-- ERRORS
-- "incorrect_prog4.cl", line 3: syntax error at or near TYPEID = True
-- "incorrect_prog4.cl", line 5: syntax error at or near POOL
-- Compilation halted due to lex and parse errors


