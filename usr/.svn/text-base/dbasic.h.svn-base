/*
 *
 * Authors: John Jones and Russell Toris
 * Version: March. 28, 2010
 */

#define COMMAND_LENGTH 80
#define VARIABLES 20
#define STRING_SIZE 255
#define VARIABLE_NAME_SIZE 20
#define INSTRUCTIONS 50
#define NTERMINATORS 10
#define NBOOLOPS 3

typedef char byte;

enum mode {
	TEXT,
	GRAPHICS
};

enum error {
	GENERAL,	
	SYNTAX,
	OVERFLOW,
	DIVISION,
	SYSTEM
};

enum arithOp {
	EQUAL,
	ADD,
	SUBTRACT,
	MULTIPLY,
	DIVIDE
};

enum boolOp {
	BEQUAL,
	LESS,
	GREATER,
	LESSEQUAL,
	GREATEREQUAL
};

union variableData {
	int intValue;
	int boolValue;
	char stringValue[STRING_SIZE];
};

enum datatype {
	NONE,
	UNDEFINED,
	INT,
	STRING,
	BOOLEAN
};

struct variable {
	char name[VARIABLE_NAME_SIZE];
	enum datatype type;
	union variableData data;
};

struct instruction {
	
	int number;
	char inst[COMMAND_LENGTH];
};

char* terminators = " \0=+-*/<>";
char* boolops = "=<>";

void help();

void load(char* file);
void store(char* file);

void init_variables();
void init_program();

int variableIndex(char* variable);

void interp_command(char* command);
void read_input(char* command);
int insertCommand(int l,char* command);

void run();
void list();
void error(enum error e,char* message);

int parseInteger(char* code,int* buffer);
int parseString(char* code,char* buffer);
int parseVariable(char* code,char* buffer);

int output(char* code);
int input(char* code,enum datatype type);

int assignmentExpression(char* code);
int expression(char* code,struct variable *var);

int booleanExpression(char* code,struct variable *var);

int isTeriminator(char c);
int isBoolop(char c);

int ifthenBlock(char* code);
int whileBlock(char* code);

int gotoLine(char* code);

void sleepCode(char* code);

int orderedPair(char* code,struct variable *x,struct variable *y);
void colorCode(char* code);
void plotCode(char* code);
void lineCode(char* code);
void rectCode(char* code);
void circleCode(char* circle);

void enableInterrupts();
