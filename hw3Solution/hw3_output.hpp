#ifndef _236360_3_
#define _236360_3_

#include <vector>
#include <string>
using namespace std;

namespace output{
    void endScope();
    void printID(const string& id, int offset, const string& type);
    void printEnumType(const string& name, vector<string>& values);

    /* Do not save the string returned from this function in a data structure 
        as it is not dynamically allocated and will be destroyed(!) at the end of the calling scope.
    */
    string makeFunctionType(const string& retType, vector<string>& argTypes);

    void errorLex(int lineno);
    void errorSyn(int lineno);
    void errorUndef(int lineno, const string& id);
    void errorDef(int lineno, const string& id);
    void errorUndefFunc(int lineno, const string& id);
    void errorUndefEnum(int lineno, const string& id);
    void errorUndefEnumValue(int lineno, const string& id);
    void errorMismatch(int lineno);
    void errorPrototypeMismatch(int lineno, const string& id, vector<string>& argTypes);
    void errorUnexpectedBreak(int lineno);
    void errorUnexpectedContinue(int lineno);
    void errorMainMissing();
    void errorByteTooLarge(int lineno, const string& value);
}

/******************************************************************************/
typedef enum Varable_t{
    INT_t , VOID_t , BOOL_t , BYTE_t, STRING_t
} VariableType;


typedef enum ScopeType_t{
    NORMAL , LOOP , GLOBAL , FUNCTION
} ScopeType;
/******************************************************************************/



/******************************************************************************/
/**
 * The rest of the token structs will inherit from this Node
 */
class Node{};
#define YYSTYPE Node*


/**
 * TOKENS
 */
class VOID_T : public Node{
public:
    VariableType type = VOID_t;
};
class ASSIGN_T : public Node{};
class OR_T : public Node{};
class AND_T : public Node{};
class EQUALOP_T : public Node{};
class RELATIONOP_T: public Node{};
class ADDOPS_T : public Node{};
class IF_T : public Node{};
class MULTOPS_T : public Node{};
class LPAREN_T : public Node{};
class RPAREN_T : public Node{};
class NOT_T : public Node{};
class INT_T : public Node{
public:
    VariableType type = INT_t;
};
class BYTE_T : public Node{
public:
    VariableType type = BYTE_t;
};
class B_T : public Node{};
class BOOL_T : public Node{
public:
    VariableType type = BOOL_t;
};
class ENUM_T : public Node{

    //TODO MIGHT ADD STUFF HER E
};
class TRUE_T : public Node{
public:
    bool val = true;

};
class FALSE_T : public Node{
public:
    bool val = false;
};
class RETURN_T : public Node{};
class ELSE_T : public Node{};
class WHILE_T : public Node{};
class BREAK_T : public Node{};
class CONTINUE_T : public Node{};
class SC_T : public Node{};
class COMMA_T : public Node{};
class LBRACE_T : public Node{};
class RBRACE_T : public Node{};
class ID_T : public Node{
public:
    string id;
    int offset;
    VariableType type;
    string value;

};
class NUM_T : public Node{
public:
    int value;

};
class STRING_T : public Node{
public:
    string value;

};
/******************************************************************************/


#endif
