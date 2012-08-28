/*
 *
 * Authors: John Jones and Russell Toris
 * Version: April 7, 2010
 */

#include "dbasic.h"
#include "lib/sys.h"
#include "lib/stdio.h"
#include "lib/string.h"
#include "lib/stdlib.h"
#include "lib/math.h"

// Holds all of the variables declared in an instance of dbasic
struct variable globals[VARIABLES];

// Holds the program in an instance of dbasic
struct instruction program[INSTRUCTIONS];

// The program counter
int pc = 0;
int systemRunning = 0;
int color = 0;
enum mode mode;

/* 
 * Main prints out the version, initializes the variables and program, and starts the command line.
 */
int main()
{
	// Holds command-line input
	char command[COMMAND_LENGTH];
	enableInterrupts();
	dino_print("dinoBASIC v0.2\n\0");

	// Clear all variables and programs
	init_variables();
	init_program();

	// Loop forever (Exiting is handles elsewhere)
	while(1)
	{
		// Get a command
		dino_print(">\0");
		read_line(command,COMMAND_LENGTH);
		dino_print("\n\0");

		// Process the command
		if (strlen(command) > 0)
			read_input(command);
	}
	terminate();
}

/*
 * Help prints out all available commands
 */
void help() {
	dino_print("dinoBASIC v0.1\n\0");
	dino_print("\n\0");
}

/*
 * This digests command line text or file lines and determines whether the command is an immediate instruction or
 * part of the program.  To make a command part of the program, it must start with a line number.  Specifying a
 * used line-number overwrites the old command with the newly entered command.  The program is executed in line-
 * number order.
 */
void read_input(char* command)
{
	// Store as part of the program
	if (isNumeric(command[0])) {
		// s is where the line number ends
		int s = indexOf(command,' ');
		// The line number as an int
		int linen;
		// The line number as ascii
		char line[COMMAND_LENGTH];

		// Get the line number ascii
		strtok(command,' ',line);
		// Convert it to an int
		linen = atoi(line);
		// Insert the command into the program array
		insertCommand(linen,command+s+1);
	// Execute immediately
	} else {
		interp_command(command);
	}
}

/*
 * This is a help-method used by insertCommand to shift the program array down starting a given index in 
 * order to insert a command.
 * The last command in the array is thrown-out if the array is full
 */
void shiftDown(int s)
{
	int i;
	// Count from the end backwards shifting commands down by 1 and stop before i = s
	for(i=INSTRUCTIONS-1;i>s;i--)
	{
		int j;
		// This command number and instruction is equal to the number and instruction directly before it.
		program[i].number = program[i-1].number;
		for(j=0;j<COMMAND_LENGTH;j++)
			program[i].inst[j] = program[i-1].inst[j];
	}
}

/*
 * Insert a command into the program at a given line number.  The line numbers do not have to be contiguous.
 */
int insertCommand(int l,char* command)
{
	int i;
	// Iterate through the program array
	for (i=0;i<INSTRUCTIONS;i++)
	{
		// We've found a free index or similiar index before l > program[i].number, so insert the command
		if (program[i].number == -1 || program[i].number == l) {
			int j;
			// Set the line number
			program[i].number = l;
			// Copy the instruction char by char
			for(j=0;j<COMMAND_LENGTH;j++)
				program[i].inst[j] = command[j];
			// Return the index
			return i;
		// program[i].number > l so shift the program down so we can insert the command here.
		} else if (program[i].number > l) {
			int j;
			// Shift the program down by one to make a free space
			shiftDown(i);
			// Set the line number
			program[i].number = l;
			// Copy the instruction char by char
			for(j=0;j<COMMAND_LENGTH;j++)
				program[i].inst[j] = command[j];
			// Return the index
			return i;
		}
	}
	// Return -1 to indicate that the array is full
	return -1;
}

/*
 * Execute a command.
 */
void interp_command(char* command)
{
	// Buffer to use when finding the command
	char parsed[COMMAND_LENGTH];
	// Tokenizer
	char r = ' ';
	// See if the command has a space
	int s = indexOf(command,' ');
	// If not, make the tokenizer a null
	if (s <= 0)
		r = '\0';
	// Tokenize the string to get the command
	strtok(command,r,parsed);
	
	// Handle the command.  See dinoBASIC README for details
	if (strcmp(parsed,"PRINT\0") == 0) {
		output(command+s);
	} else if (strcmp(parsed,"PRINTLN\0") == 0) {
		if (output(command+s) >= 0)
			dino_print("\n\0");
	} else if (strcmp(parsed,"INPUTSTR\0") == 0) {
		input(command+s,STRING);
	} else if (strcmp(parsed,"INPUTINT\0") == 0) {
		input(command+s,INT);
	} else if (strcmp(parsed,"LET\0") == 0) {
		assignmentExpression(command+s);
	} else if (strcmp(parsed,"IF\0") == 0) {
		ifthenBlock(command+s);
	} else if (strcmp(parsed,"WHILE\0") == 0) {
		whileBlock(command+s);
	} else if (strcmp(parsed,"GOTO\0") == 0) {
		gotoLine(command+s);
	} else if (strcmp(parsed,"SLEEP\0") == 0) {
		sleepCode(command+s);
	} else if (strcmp(parsed,"TEXT\0") == 0) {
		mode = TEXT;
		setTextMode();
		clear_scr();
	} else if (strcmp(parsed,"GRAPHICS\0") == 0) {
		mode = GRAPHICS;
		setVGAMode();
	} else if (strcmp(parsed,"PLOT\0") == 0) {
		plotCode(command+s);
	} else if (strcmp(parsed,"COLOR\0") == 0) {
		colorCode(command+s);
	} else if (strcmp(parsed,"LINE\0") == 0) {
		lineCode(command+s);
	} else if (strcmp(parsed,"RECT\0") == 0) {
		rectCode(command+s);
	} else if (strcmp(parsed,"CIRCLE\0") == 0) {
		circleCode(command+s);
	} else if (strcmp(parsed,"LOAD\0") == 0) {
		load(command+s+1);
	} else if (strcmp(parsed,"STORE\0") == 0) {	
		store(command+s+1);
	} else if (strcmp(parsed,"LIST\0") == 0) {
		list();
	} else if (strcmp(parsed,"RUN\0") == 0) {
		run();
	} else if (strcmp(parsed,"END\0") == 0) {
		pc = INSTRUCTIONS;
		systemRunning = 0;
	} else if (strcmp(parsed,"CLEAR\0") == 0) {
		init_variables();
		init_program();
	} else if (strcmp(parsed,"HOME\0") == 0) {
		clear_scr();
	} else if (strcmp(parsed,"HELP\0") == 0) {
		help();
	} else if (strcmp(parsed,"QUIT\0") == 0 || strcmp(parsed,"EXIT\0") == 0) {
		terminate();
	} else if (strcmp(parsed,"REM\0") == 0 || strlen(parsed) == 0) {
	} else {
		error(SYNTAX,"Syntax error\0");
	}
}

/*
 * Set all line numbers in the stored-program to -1 to represent an unused section.
 */
void init_program() {
	int i;
	// Loop through the program array and set the line number to -1
	for (i=0;i<INSTRUCTIONS;i++)
	{
		program[i].number = -1;
	}
}

/*
 * Set all the variable types to NONE to represent unused sections.
 */
void init_variables() {
	int i;
	// Loop through the variable array and set the type to NONE
	for(i=0;i<VARIABLES;i++)
	{
		globals[i].type = NONE;
	}
}

/*
 * Get the array index of the variable with the given name.  If the variable does not exist, return a free index
 * (represented by a NONE flag) but with the flag set to UNDEFINED.
 */
int variableIndex(char* variable) {
	int i;
	int free = -1;
	int j;
	// Loop through all of the variables
	for(i=0;i<VARIABLES;i++)
	{
		// If the names match, return the index.
		if (strcmp(globals[i].name,variable) == 0) {
			return i;
		// If a free index is found, remember it as it may be needed later
		} else if (free < 0 && globals[i].type == NONE) {
			free = i;
		}
	}
	// If we're here, it means that the variable has yet to be declared.
	// Set it to UNDEFINED to prevent it from being overwritten
	globals[free].type = UNDEFINED;
	// Copy the name
	for(j=0;j<VARIABLE_NAME_SIZE;j++)
		globals[free].name[j] = variable[j];
	// Return the index
	return free;
}

/*
 * Run the commands stored in program by iterating through each index and calling interp_command.
 */
void run() {
	// Set the program counter to 0
	pc = 0;
	// Set the running flag to true
	systemRunning = 1;
	// Clear all variables
	init_variables();
	// Loop through the program array until pc is too large
	while(pc < INSTRUCTIONS)
	{
		if (program[pc].number >= 0) {
			// Run the command
			interp_command(program[pc].inst);
		}
		pc++;
	}
	systemRunning = 0;
}


/*
 * Used for debugging, this method dumps the contents of the variable index.
 */
void dumpvars()
{
	int v;
	// Loop through all variables
	for(v=0;v<VARIABLES;v++)
	{
		// If the variable is typed, display it
		if (globals[v].type != NONE) {
			dino_print("Name: \0");
			dino_print(globals[v].name);
			dino_print("\tType: \0");
			dino_printint(globals[v].type);
			dino_print("\tValue: \0");
			dino_print(globals[v].data.stringValue);
			dino_print("\n\0");
		}
	}
}

/*
 * List all of the stored program commands
 */
void list()
{
	int i;
	// Loop through all commands
	for (i=0;i<INSTRUCTIONS;i++)
	{
		// If the line number is greater than or equal to zero, print it
		if (program[i].number >= 0) {
			dino_printint(program[i].number);
			dino_print("\t\0");
			dino_print(program[i].inst);
			dino_print("\n\0");
		}
	}
}

/*
 * Called to send an error to the display.  Error types are defined as an enum to better categorize the possible
 * types of errors.
 */
void error(enum error e,char* message)
{
	dino_print("* ERROR:\n\0");
	
	if (error == SYNTAX)
		dino_print("\tSyntax Error: \0");
	else if (error == OVERFLOW)
		dino_print("\tOverflow Error: \0");
	else if (error == SYSTEM)
		dino_print("\tSystem Error: \0");
	
	dino_print(message);
	dino_print("\n\0");
}

/*
 * Scan the code given and find a number until a non-numeric character is reached.
 */
int parseInteger(char* code,int* buffer)
{
	// For counting the ascii length of the number
	int i=0;
	// Find an integer in the code string
	*buffer = atoi(code);
	// Count the ascii length of the number
	while(isNumeric(code[i]))
		i++;
	// Return the length
	return i;
}

/*
 * Scan the code for a string until a '"' is found
 * This throws an error if the string ends before a closing '"'
 */
int parseString(char* code,char* buffer)
{
	int i=0;
	int result = 0;
	// Loop so long as result = 0
	while(result == 0)
	{
		// If i is too large throw an error
		if (i >= STRING_SIZE) {
			error(OVERFLOW,"String declaration too large.\0");
			result = -1;
		// If a null is reached, the string was not declared properly
		} else if (code[i] == '\0') {
			error(SYNTAX,"Strings must be closed.\0");
			result = -1;
		// If the closeing '"' was found, end the search
		} else if (code[i] == '\"') {
			buffer[i] = '\0';
			// Set result to the number or characters parsed
			result = i;
		// Else copy the string to the buffer
		} else {
			buffer[i] = code[i];
		}
		i++;
	}
	
	return result;
}

/*
 * Scan the code for a variable until a space, a math operator, or an end of string is found
 */
int parseVariable(char* code,char* buffer) {
	int i=0;
	int j=0;
	int result = 0;
	// Marks when to start reading
	int started = 0;
	// Parse so long as result == 0
	while (result == 0)
	{
		// Throw an error if too many characters are parsed
		if (i >= VARIABLE_NAME_SIZE) {
			error(OVERFLOW,"Variable name too large.\0");
			result = -1;
		// Stop parsing at an end of string, an operator, or a space so long as started is set to 1
		} else if (started == 1 && isTeriminator(code[i])) {
			buffer[j] = '\0';
			result = i;
		// Else, read the character and make sure started is set to 1
		} else if (code[i] != ' ') {
			buffer[j] = code[i];
			started = 1;
			j++;
		}
		i++;
	}
	return result;
}

/*
 * Print the given expression
 */
int output(char* code) {
	// Make a variable to store the expression result
	struct variable lvar;
	// Evaluate the expression
	int result = expression(code,&lvar);
	// If the expression was evaluated print it
	if (result >= 0) {
		// The type is an int
		if (lvar.type == INT) {
			dino_printint(lvar.data.intValue);
		// The type is a string
		} else if (lvar.type == STRING) {
			dino_print(lvar.data.stringValue);
		}
	}
	return result;
}

int input(char* code,enum datatype type) {
	// Make a variable to store the expression result
	struct variable var;
	// Get the name
	int result = parseVariable(code,var.name);
	// If the variable was read, continue
	if (result >= 0) {
		// Get the variable index
		int varIndex = variableIndex(var.name);
		// A buffer for the text input
		char inputBuffer[STRING_SIZE];
		// Set the type
		globals[varIndex].type = type;
		// Get the text
		read_line(inputBuffer,STRING_SIZE);
		dino_print("\n\0");
		// If the type is an int, convert the buffer contents to an int
		if (type == INT) {
			globals[varIndex].data.intValue = atoi(inputBuffer);
		// If the type is a string, copy the buffer contents
		} else if (type == STRING) {
			strcpy(globals[varIndex].data.stringValue, inputBuffer);
		} else {
			error(GENERAL,"Wrong variable type");
		}
	} else {
		error(SYNTAX,"Variable not specified");
	}
	return result;
}

/*
 * Assign the expression to a variable given in the code.  The type of the variable is changed if the variable
 * previously had a value.
 */
int assignmentExpression(char* code) {
	// Find the equals sign
	int split = indexOf(code,'=');
	// Only continue if the sign was found
	if (split > 0) {
		int result;
		// Declare a variable to store the name of the lval
		struct variable lvar;
		// Get the name of the lval
		result = parseVariable(code,lvar.name);
		// If the lval was found, continue
		if (result >= 0) {
			// Evaluate the right-hand-size of the the assignment
			result = expression(code+split+1,&lvar);
			// If it was evaluated correctly, continue
			if (result >= 0) {
				// Get the index of the lval from the variable array
				int lvarIndex = variableIndex(lvar.name);
				// If the lval was found, continue
				if (lvarIndex >= 0) {
					int i;
					// Change the type of the variable to match
					globals[lvarIndex].type = lvar.type;
					// Copy the string data if its a string
					if (lvar.type == STRING) {
						for(i=0;i<STRING_SIZE;i++)
							globals[lvarIndex].data.stringValue[i] = lvar.data.stringValue[i];
					// Copy the int data if its an int
					} else if (lvar.type == INT) {
						globals[lvarIndex].data.intValue = lvar.data.intValue;
					}
					return 0;
				}
			}
		}
		return result;
	} else {
		error(SYNTAX,"Lval missing.\0");
		return -1;
	}
}

/*
 * Evaluate an expression and assign it to the variable pointer.  An expression is either a constant or an arithmatic
 * operation.
 *
 * Ex.
 * "Foo"
 * "Foo" + "Bar"
 * A + " Test"
 * 4 / 2
 */
int expression(char* code,struct variable *var) {
	// Buffer for the left and right values of the expression
	struct variable vars[2];
	// The arithmetic operator of the expression
	enum arithOp op = EQUAL;
	// Points to which vars array index to use
	int varCount = 0;
	// Character array index
	int i = 0;
	int result = 0;
	// Loop so long as result = 0, variables found is less than 2 and the end of the string hasn't been found
	while (code[i] != '\0' && varCount < 2 && result == 0) {
		char tmp[3];
		tmp[0] = code[i];
		tmp[1] = '\n';
		tmp[2] = '\0';
//		dino_print(tmp);

		if (isBoolop(code[i]) == 1 || (code[i] == 'T' && code[i+1] == 'H' && code[i+2] == 'E' && code[i+3] == 'N')) {
			result = i;
		// If an addition sign, set the operator to ADD
		} else if (code[i] == '+') {
			op = ADD;
		// If a subractions sign, set the operator to SUBTRACT
		} else if (code[i] == '-') {
			op = SUBTRACT;
		// If a multiplication sign, set the operator to MULTIPLY
		} else if (code[i] == '*') {
			op = MULTIPLY;
		// If a division sign, set the operator to DIVIDE
		} else if (code[i] == '/') {		
			op = DIVIDE;
		// If the character is numeric, read an integer constant
		} else if (isNumeric(code[i])) {
			// Check to make sure there is room for another value
			if (varCount == 0 || (varCount > 0 && op != EQUAL)) {
				// Set the type to INT
				vars[varCount].type = INT;
				// Parse the int
				result = parseInteger(code+i,&(vars[varCount].data.intValue));
				// Point to the next array index
				varCount++;
				// Reset result and advance i for the amount of characters parsed
				if (result >= 0) {
					i+= result -1;
					result = 0;
				}
			}
		// If the character is a '"', then read a string constant
		} else if (code[i] == '\"') {
			// Check to make sure there is room for another value
			if (varCount == 0 || (varCount > 0 && op != EQUAL)) {
				// Read the string
				result = parseString(code+i+1,vars[varCount].data.stringValue);
				// Set the type to STRING
				vars[varCount].type = STRING;
				// Point to the next array index
				varCount++;
				// Reset result and advance i for the amount of characters parsed
				if (result >= 0) {
					i+= result + 1;
					result = 0;
				}
			}
		// If it is anything else besides a ' ' character, then read a variable
		} else if (code[i] != ' ') {
			// Check to make sure there is room for another value
			if (varCount == 0 || (varCount > 0 && op != EQUAL)) {
				int varIndex = -1;
				// Read the variable
				result = parseVariable(code+i,vars[varCount].name);
				// If the variable was read, continue
				if (result >= 0) {
					// Advance the character array index by how many characters were parsed
					i += result;
					// Clear the result
					result = 0;
					// Get the variable index
					varIndex = variableIndex(vars[varCount].name);
					// If the variable was found and is typed, continue
					if (varIndex >= 0 && globals[varIndex].type != NONE && globals[varIndex].type != UNDEFINED) {
						// Change the vars variable type to match
						vars[varCount].type = globals[varIndex].type;
						// If it is a string, get the string value
						if (vars[varCount].type == STRING) {
							int j;
							for(j=0;j<STRING_SIZE;j++) {
								vars[varCount].data.stringValue[j] = globals[varIndex].data.stringValue[j];
							}
						// If it is an int, get the int value
						} else if (vars[varCount].type == INT) {
							vars[varCount].data.intValue = globals[varIndex].data.intValue;
						}
						// Point to the next array index
						varCount++;
					// Throw an error if the variable is not set
					} else {
						error(GENERAL,"Variable undefined\0");
						result = -1;
					}
				}
			}
		}
		i++;
	}

	// If only one variable was found, simply copy its value to the given variable pointer
	if (varCount == 1) {
		// Set the type
		var->type = vars[0].type;
		// If it is a string, copy the string value
		if (vars[0].type == STRING) {
			for(i=0;i<STRING_SIZE;i++)
				var->data.stringValue[i] = vars[0].data.stringValue[i];
		// If it is an int, copy the int value
		} else if (vars[0].type == INT) {
			var->data.intValue = vars[0].data.intValue;
		}
		result = i;
	// If two variables are found, perform an operation on them and assign the result to the given variable pointer
	} else if (varCount == 2) {
		// Throw an error if the variable types do not match
		if (vars[0].type != vars[1].type) {
			error(GENERAL,"Rval argument types must match.\0");
			result = -1;
		// If the type is a string
		} else if (vars[0].type == STRING) {
			// If the operator is ADD, then concat the second string onto the first
			if (op == ADD) {
				// Set the type to STRING
				var->type = STRING;
				// Concat the values
				concat(vars[0].data.stringValue,vars[1].data.stringValue,var->data.stringValue);
				result = i;
			// Throw an error if the operator is anything other than ADD
			} else {
				error(SYNTAX,"Only add (+) operator allowed on strings.\0");
				result = -1;
			}
		// If the type is an int
		} else if (vars[0].type == INT) {
			// Set the type to int
			var->type = INT;
			// Perform addition
			if (op == ADD) {
				var->data.intValue = vars[0].data.intValue + vars[1].data.intValue;
				result = i;
			// Perform subraction
			} else if (op == SUBTRACT) {
				var->data.intValue = vars[0].data.intValue - vars[1].data.intValue;
				result = i;
			// Perform multiplication
			} else if (op == MULTIPLY) {
				var->data.intValue = vars[0].data.intValue * vars[1].data.intValue;
				result = i;
			// Perform division
			} else if (op == DIVIDE) {
				// Only divide if the second value is anything other than zero
				if (vars[1].data.intValue != 0) {
					var->data.intValue = vars[0].data.intValue / vars[1].data.intValue;
					result = i;
				// Throw an error for division by zero
				} else {
					error(DIVISION,"Division by zero.\0");
					result = -1;
				}
			} else {
				error(GENERAL,"Operator error.\0");
				result = -1;
			}
		}
	} else if (varCount == 0) {
		error(SYNTAX,"Not enough rval arguments.\0");
	} else if (varCount > 2) {
		error(SYNTAX,"Too many rval arguments.\0");
	}

	return result;
}

int booleanExpression(char* code,struct variable *var)
{
	// Buffer for the left and right values of the expression
	struct variable vars[2];
	// The arithmetic operator of the expression
	enum boolOp op = BEQUAL;
	// Points to which vars array index to use
	int varCount = 0;
	// Character array index
	int i = 0;
	int result = 0;
	while (code[i] != '\0' && varCount < 2 && result == 0) {
		if (code[i] == '=') {
			op = BEQUAL;
		} else if (code[i] == '<' && code[i+1] == '=') {
			op = LESSEQUAL;
			i++;
		} else if (code[i] == '>' && code[i+1] == '=') {
			op = GREATEREQUAL;
			i++;
		} else if (code[i] == '<') {
			op = LESS;
		} else if (code[i] == '>') {
			op = GREATER;
		} else if (code[i] == '\0') {
			result = i;
		} else if (code[i] != ' ') {
			result = expression(code+i,&vars[varCount]);
			if (result > 0) {
				// Advance the character array index by how many characters were parsed
				i += result-2;
				// Clear the result
				result = 0;
			}
			varCount++;
		}
		i++;
	}
	
	// If only one variable was found, simply see if it is 0
	if (varCount == 1) {
		var->type = BOOLEAN;
		if ((vars[0].type == INT && vars[0].data.intValue > 0) || (vars[0].type == STRING && strlen(vars[0].data.stringValue) > 0))
			var->data.boolValue = 1;
		else
			var->data.boolValue = 0;
		result = i;
	// Two variables were found so compare them
	} else if (varCount == 2) {
		// Throw an error if the variable types do not match
		if (vars[0].type != vars[1].type) {
			error(GENERAL,"Bool argument types must match.\0");
			result = -1;
			// If the type is a string
		} else if (vars[0].type == STRING) {
			error(GENERAL,"Bool argument types must be integers.\0");
			result = -1;
			// If the type is an int
		} else if (vars[0].type == INT) {
			var->type = BOOLEAN;
			if (op == BEQUAL) {
				if (vars[0].data.intValue == vars[1].data.intValue) {
					var->data.boolValue = 1;
				} else {
					var->data.boolValue = 0;
				}
				result = i;
			} else if (op == LESSEQUAL) {
				if (vars[0].data.intValue <= vars[1].data.intValue) {
					var->data.boolValue = 1;
				} else {
					var->data.boolValue = 0;
				}
				result = i;
			} else if (op == GREATEREQUAL) {
				if (vars[0].data.intValue >= vars[1].data.intValue) {
					var->data.boolValue = 1;
				} else {
					var->data.boolValue = 0;
				}
				result = i;
			} else if (op == LESS) {
				if (vars[0].data.intValue < vars[1].data.intValue) {
					var->data.boolValue = 1;
				} else {
					var->data.boolValue = 0;
				}
				result = i;
			} else if (op == GREATER) {
				if (vars[0].data.intValue > vars[1].data.intValue) {
					var->data.boolValue = 1;
				} else {
					var->data.boolValue = 0;
				}
				result = i;
			} else {
				error(GENERAL,"Operator error.\0");
				result = -1;
			}
		}
	} else if (varCount == 0) {
		error(SYNTAX,"Not enough bool arguments.\0");
	} else if (varCount > 2) {
		error(SYNTAX,"Too many bool arguments.\0");
	}
	
	return result;
}

int ifthenBlock(char* code) {
	int i = 0;
	struct variable var;
	i = booleanExpression(code,&var);
	if (i > 0) {
		while ((code[i] != 'T' && code[i+1] != 'H' && code[i+2] != 'E' && code[i+3] != 'N') && code[i] != 0x00) {			
			i++;
		}
		
		if (code[i] == 0x00) {
			error(SYNTAX,"IF statements must have THEN.\0");
			return -1;
		} else {
			int j = i+4;
			int charsfound =0;
			while (code[j] != 0x00) {
				j++;
				if (code[j] != ' ')
					charsfound = 1;
			}
			
			if (charsfound > 0 && var.data.boolValue > 0) {
				interp_command(code+i+5);
			} else if (systemRunning == 0) {
				error(GENERAL,"System must be running to accept IF blocks");
				return -1;
			} else if (systemRunning > 0) {
					pc++;
					while(pc < INSTRUCTIONS && strcmp(program[pc].inst,"ENDIF\0") != 0)
					{
						if (program[pc].number >= 0 && var.data.boolValue > 0) {
							// Run the command
							interp_command(program[pc].inst);
						}
						pc++;
					}
			}
		}
	}
	return 0;
}

int whileBlock(char* code) {
	int start = pc;
	int i = 0;
	struct variable var;
	booleanExpression(code,&var);
	pc++;
	while(pc < INSTRUCTIONS && var.data.boolValue > 0 && i < 5)
	{
		if (strcmp(program[pc].inst,"LOOP\0") == 0) {
			pc = start;
			booleanExpression(code,&var);
		}
			
		if (program[pc].number >= 0) {
			// Run the command
			interp_command(program[pc].inst);
		}
		pc++;
		i++;
	}
	return 0;
}

int gotoLine(char* code)
{
	int l = atoi(code);
	int i;
	// Iterate through the program array
	for (i=0;i<INSTRUCTIONS;i++)
	{
		if (program[i].number == l) {
			pc = i-1;
			return i-1;
		}
	}
	return -1;		
}

void sleepCode(char* code)
{
	struct variable var;
	expression(code,&var);
	if (var.type == INT) {
		sleep(var.data.intValue);
	} else {
		error(GENERAL,"SLEEP requires an integer value.\0");
	}
}

int orderedPair(char* code,struct variable *x,struct variable *y)
{
	int i = expression(code,x);
	i = indexOf(code,',')+1;
	i += expression(code+i,y);
	return i;
}

void colorCode(char* code)
{
	struct variable var;
	expression(code,&var);
	if (var.type == INT)
		color = var.data.intValue;
	else
		error(GENERAL,"COLOR requires an integer value.\0");
}

void plotCode(char* code)
{
	if (mode == GRAPHICS) {
		struct variable x;
		struct variable y;
		orderedPair(code,&x,&y);
		plot(x.data.intValue,y.data.intValue,color);
	} else {
		error(SYSTEM,"Must be in GRAPHICS mode to use PLOT");
	}
}

void lineCode(char* code)
{
	if (mode == GRAPHICS) {
		struct variable x1;
		struct variable y1;
		struct variable x2;
		struct variable y2;
		int i = 0;
		while (code[i] != 'T' || code[i+1] != 'O')
			i++;
		i += 2;
		orderedPair(code,&x1,&y1);
		orderedPair(code+i,&x2,&y2);
		line(x1.data.intValue,y1.data.intValue,x2.data.intValue,y2.data.intValue,color);
	} else {
		error(SYSTEM,"Must be in GRAPHICS mode to use LINE");
	}
}

void rectCode(char* code)
{
	if (mode == GRAPHICS) {
		struct variable x1;
		struct variable y1;
		struct variable w;
		struct variable h;
		int windex = indexOf(code,'W');
		int hindex = indexOf(code,'H');
		orderedPair(code,&x1,&y1);
		expression(code+windex+1,&w);
		expression(code+hindex+1,&h);
		rect(x1.data.intValue,y1.data.intValue,w.data.intValue,h.data.intValue,color);
	} else {
		error(SYSTEM,"Must be in GRAPHICS mode to use RECT");
	}
}

void circleCode(char* code)
{
	if (mode == GRAPHICS) {
		struct variable x1;
		struct variable y1;
		struct variable r;
		int rindex = indexOf(code,'R');
		orderedPair(code,&x1,&y1);
		expression(code+rindex+1,&r);
		circle(x1.data.intValue,y1.data.intValue,r.data.intValue,color);
	} else {
		error(SYSTEM,"Must be in GRAPHICS mode to use CIRCLE");
	}
}

int isTeriminator(char c)
{
	int i;
	for(i=0;i<NTERMINATORS;i++)
		if (terminators[i] == c)
			return 1;
	return 0;
}

int isBoolop(char c)
{
	int i;
	for(i=0;i<NBOOLOPS;i++)
		if (boolops[i] == c)
			return 1;
	return 0;
}

/*
 * Load a program from disk into the program array
 */
void load(char* file) {
	// The file buffer
	char f[13312];
	// Open the file and proceed if it is opened
	if (fopen(file, f, 13312) >= 0) {
		// An array of buffers for holding instructions
		char linebuffer[INSTRUCTIONS][COMMAND_LENGTH];
		// Count the instructions
		int inst = 0;
		int i;
		// If a return is found that means the first line is code
		if (strtok(f,'\r',linebuffer[inst]) != 0x00) {
			// Increment the instruction counter
			inst++;
			// Continue to find instructions so long as inst is within the size and returns are found
			while (strtok(0x00,'\r',linebuffer[inst]) != 0x00 && inst < INSTRUCTIONS)
			{
				inst++;
			}
		}
		
		// Print the results
		dino_printint(inst);
		dino_print(" instructions read.\n\0");
		
		// Analyze the buffer
		for (i=0;i<inst;i++)
			read_input(linebuffer[i]);
	} else {
		error(SYSTEM,"File not found.\0");
	}
}

/*
 * Store the program array to disk
 */
void store(char* file) {
	// Instruction array index counter
	int i;
	// File buffer index
	int j=0;
	// Fwrite return
	int ret;
	// File buffer
	char f[13312];
	// Instruction counter
	int inst = 0;
	// Loop through all instructions
	for(i=0;i<INSTRUCTIONS;i++)
	{
		// If the instruction is set, proceed
		if (program[i].number != -1)
		{
			// Copy the instruction until a null or the end of the string is reached
			int k = 0;
			char linenumber[10];
			int l = itoa(program[i].number,linenumber);
			for (k=0;k<l;k++)
			{
				f[j] = linenumber[k];
				j++;
			}
			
			f[j++] = ' ';
			
			k=0;
			while (k<COMMAND_LENGTH && program[i].inst[k] != 0x00)
			{
				f[j] = program[i].inst[k];
				j++;
				k++;
			}
			// Set a return at the end of the instruction
			f[j] = '\r';
			// Advance the file buffer index
			j++;
			// Advance the instruction counter
			inst++;
		}
	}
	// Null terminate the file
	f[j] = 0x00;
	
	// Write the file to the disk
	ret = fwrite(file, f, (strlen(f)/512)+1);
	// Check if it was successful
	if (ret == -2) {
		error(SYSTEM,"Disk is full.\0");
	} else if (ret == -1) {
		error(SYSTEM,"Disk directory is full.\0");
	} else {
		dino_printint(inst);
		dino_print(" instructions written.\n\0");
	}
}
