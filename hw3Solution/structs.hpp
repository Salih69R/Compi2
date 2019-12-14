//
// Created by haitham on 12/8/2019.
//

#ifndef COMPI_3_STRUCTS_HPP
#define COMPI_3_STRUCTS_HPP

#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <assert.h>
#include "hw3_output.hpp"
extern int yylineno;


using std::cout;
using std::endl;
using std::stack;
using std::string;
using std::vector;
using namespace output;





/******************************************************************************/

typedef enum ScopeType_t{
    NORMAL , LOOP , GLOBAL , FUNCTION
} ScopeType;

typedef enum tokentype_t { VOID_t , INT_t ,
     BYTE_t, B_t, BOOL_t,
     AND_t ,OR_t , NOT_t 
     , TRUE_t , FALSE_t , RETURN_t ,
     IF_t , ELSE_t , WHILE_t , BREAK_t ,
     CONTINUE_t , SC_t ,COMMA_t ,
     LPAREN_t , RPAREN_t, LBRACE_t,
     RBRACE_t , ASSIGN_t , COMMENT_t, ID_t, NUM_t, STRING_t ,ADDOPS_t, MULTOPS_t ,EQUALOP_t, RELATIONOP_t , FUNCTION_t , UNDEFYET_t} TokenType;


vector<string> TokensToString(vector<TokenType>& vec);

/******************************************************************************/



/******************************************************************************/
/**
 * The rest of the token structs will inherit from this Node
 */
class Node{

public:
    string name;
    string value;
    TokenType type;

Node( TokenType type, string name = "",string value = "null"):name(name), type(type), value(value){};

};
#define YYSTYPE Node*




class Variable : public Node{
public:
    int offset;
	
    Variable(TokenType type , string name = "", int offset = 0):Node(type, name), offset(offset){}
};

class Function : public Variable{

    public:
    TokenType returnType;
	vector<TokenType> paramTypes;
    vector<Variable*> params;

    Function(string name , TokenType returnType);

    void addParam(Variable* param);



	void ValidateParameters(vector<TokenType>& callerParams);

};






class Scope{
public:

    stack<Variable*> local_table;
    ScopeType type;
    
    Scope(ScopeType type);
    void insertVar(Variable* var);
    Variable* getVar(string gname);
    ~Scope();

};



class Symbol_Table{

public:
    stack<int> offset_stack;
    vector<Scope> scopes_table;

    Variable* getVar(string name);
    void openScope(ScopeType type);
    void insertVar(Variable* var);
    void insertFunc(Function* f);//assumes f is full
    void closeScope();
    
};

#endif //COMPI_3_STRUCTS_HPP
