//
// Created by haitham on 12/8/2019.
//

#ifndef COMPI_3_STRUCTS_HPP
#define COMPI_3_STRUCTS_HPP


#include <stack>
#include <string>
#include <assert.h>

using std::stack;
using std::string;





/******************************************************************************/

typedef enum ScopeType_t{
    NORMAL , LOOP , GLOBAL , FUNCTION
} ScopeType;

typedef enum tokentype { VOID_t , INT_t ,
     BYTE_t, B_t, BOOL_t,
     AND_t ,OR_t , NOT_t 
     , TRUE_t , FALSE_t , RETURN_t ,
     IF_t , ELSE_t , WHILE_t , BREAK_t ,
     CONTINUE_t , SC_t ,COMMA_t ,
     LPAREN_t , RPAREN_t, LBRACE_t,
     RBRACE_t , ASSIGN_t , COMMENT_t, ID_t, NUM_t, STRING_t ,ADDOPS_t, MULTOPS_t ,EQUALOP_t, RELATIONOP_t } TokenType;
     
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


class Scope{
public:

    stack<Variable*> local_table;
    ScopeType type;
    
    //TODO: when this constructor is called, on the outside need to update the offset stack (new push)
    Scope(ScopeType type): type(type){
        local_table = stack<Variable*>();
    }

//TODO: update offset when using this
    void insertVar(Variable* var){
       local_table.push(var);
    }



    Variable* getVar(string gname){
        stack<Variable*> cpy_stack = stack<Variable*>();
        Variable *curVar, *foundVar = nullptr;


        while(!local_table.empty()){
            if(local_table.top()->name == gname){
                foundVar = local_table.top();
                break;
            }
            curVar = local_table.top();
            local_table.pop();
            cpy_stack.push(curVar);
        }

         while (!cpy_stack.empty()){
            curVar = cpy_stack.top();
            local_table.push(curVar);
            cpy_stack.pop();
         }
         return foundVar;
    }

    ~Scope(){

        while(!local_table.empty()){

            delete(local_table.top());
            local_table.pop();
        }
    }


    //TODO : when using destructor update offset 
    //TODO check functions


};



class Sympol_Table{

public:
    stack<int> offset_stack;
    stack<Scope> scopes_table;

    Variable* GetVar(string name){

        stack<Scope> cpy_stack = stack<Scope>();
        Scope cpy_scope;
        Variable* found = nullptr;

        while(!scopes_table.empty()){

        }
    }
};



//bool isAlreadyDefined( base_type_info& item){
//
//
//    stack<stack<base_type_info>> cpy_table_stack;
//    stack<base_type_info> cpy_stack;
//    bool found = false;
//
//    while(!tables_stack.empty()){
//        if (isContainItem(tables_stack.top() , item)){
//            found = true;
//            break;
//        }
//        cpy_stack = tables_stack.top();
//        cpy_table_stack.push(cpy_stack);
//        tables_stack.pop();
//    }
//
//    while(!cpy_table_stack.empty()){
//        cpy_stack = cpy_table_stack.top();
//        tables_stack.push(cpy_stack);
//        cpy_table_stack.pop();
//    }
//
//    return found;
//
//
//
//
//}
//



//void Exit_a_block(){
//
//    while(!tables_stack.top().empty()){
//        tables_stack.top().pop();
//    }
//}
//
//
//void Close_a_Block(){
//
//    Exit_a_block();
//    offset_stack.pop();
//
//}
//
























/**
 * TOKENS
 */
// class VOID_T : public Node{
// public:
//     VariableType type = VOID_t;
// };
// class ASSIGN_T : public Node{
// };
// class OR_T : public Node{};
// class AND_T : public Node{};
// class EQUALOP_T : public Node{
//     string op;
// };
// class RELATIONOP_T: public Node{
//     string op;
// };
// class ADDOPS_T : public Node{
//     string op;
// };
// class IF_T : public Node{};
// class MULTOPS_T : public Node{
//     string op;
// };
// class LPAREN_T : public Node{};
// class RPAREN_T : public Node{};
// class NOT_T : public Node{};
// class INT_T : public Node{
// public:
//     VariableType type = INT_t;
// };
// class BYTE_T : public Node{
// public:
//     VariableType type = BYTE_t;
// };
// class B_T : public Node{};
// class BOOL_T : public Node{
// public:
//     VariableType type = BOOL_t;
// };
// class ENUM_T : public Node{

//     //TODO MIGHT ADD STUFF HER E
// };
// class TRUE_T : public Node{};
// class FALSE_T : public Node{};
// class RETURN_T : public Node{};
// class ELSE_T : public Node{};
// class WHILE_T : public Node{};
// class BREAK_T : public Node{};
// class CONTINUE_T : public Node{};
// class SC_T : public Node{};
// class COMMA_T : public Node{};
// class LBRACE_T : public Node{};
// class RBRACE_T : public Node{};
// class ID_T : public Node{
// public:
//     string id;
//     int offset;
//     VariableType type;
//     string value;
// };
// class NUM_T : public Node{
// public:
//     string value;
// };
// class STRING_T : public Node{
// public:
//     string value;
// };



// //Grammar variables



// class EXP_T : public Node{
//     VariableType type;
//     string value;
// };
// class ENUMTYPE_T : public Node{};
// class TYPE_T : public Node{};
// class EXPLIST_T : public Node{};
// class CALL_T : public Node{};
// class STATEMENT_T : public Node{};
// class STATEMENTS_T : public Node{};
// class ENUMERATOR_T : public Node{};
// class ENUMERATORLIST_T : public Node{};
// class FORMALDECL_T : public Node{};
// class FORMALSLIST_T : public Node{};
// class FORMALS_T : public Node{};
// class RETTYPE_T : public Node{};
// class ENUMDECL_T : public Node{};
// class ENUMS_T : public Node{};
// class FUNCDEL_T : public Node{};
// class FUNCS_T : public Node{};
// class PROGRAM_T : public Node{};





/******************************************************************************/




// typedef union Data_t{

// } Data_info;

// typedef enum ScopeType_t{
//     NORMAL , LOOP , GLOBAL , FUNCTION
// } ScopeType;


// class Scope{

// public:
//     ScopeType type;
//     stack<Data_info> scope_stack;

// };



//class base_type_info {
//
//public:
//
//    // we need to spilt these ********
//    string name;
//    //this refers to the token enums
//    int type;
//    string value;
//    //might remove
//    int offset;
//    string in;
//    bool isAssignable;
//
//
//
//
//};
//
//
///*
//
//union t {
//base_type_info expType;
//base_type_info opType;
//base_type_info BType;
//base_type_info CommentType;
//base_type_info ProgramType;
//base_type_info EnumType;
////..
//};
//
//
//
//
//class CType{
//public:
////enum = what type are you
//t ctype;
//
//
//
//};
//
//
//
//CType x;
////if enum is exp
//base_type_info tmpexp = x.ctype.expType;
//
//*/
//
//
//
//
//stack<int> offset_stack;
//stack<stack<base_type_info>> tables_stack;
//


//
//void Insert_a_function(base_type_info func){
//
//
//}


#endif //COMPI_3_STRUCTS_HPP
