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



//Grammar variables



class EXP_T : public Node{
    VariableType type;
    string value;
};
class ENUMTYPE_T : public Node{};
class TYPE_T : public Node{};
class EXPLIST_T : public Node{};
class CALL_T : public Node{};
class STATEMENT_T : public Node{};
class STATEMENTS_T : public Node{};
class ENUMERATOR_T : public Node{};
class ENUMERATORLIST_T : public Node{};
class FORMALDECL_T : public Node{};
class FORMALSLIST_T : public Node{};
class FORMALS_T : public Node{};
class RETTYPE_T : public Node{};
class ENUMDECL_T : public Node{};
class ENUMS_T : public Node{};
class FUNCDEL_T : public Node{};
class FUNCS_T : public Node{};
class PROGRAM_T : public Node{};





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
//bool isContainItem(stack<base_type_info>& table_stack , base_type_info& item){
//
//    stack<base_type_info> cpy_stack;
//    bool found = false;
//    base_type_info cpy_item;
//
//    while(!table_stack.empty()){
//        //TODO check other identeinssfd
//        if (table_stack.top().name == item.name){
//            found = true;
//            break;
//        }
//        cpy_item = table_stack.top();
//        cpy_stack.push(cpy_item);
//        table_stack.pop();
//    }
//
//    while (!cpy_stack.empty()){
//        cpy_item = cpy_stack.top();
//        table_stack.push(cpy_item);
//        cpy_stack.pop();
//    }
//
//    return found;
//
//}
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
//
//void Open_a_Block(){
//
//    stack<base_type_info> new_block;
//    tables_stack.push(new_block);
//    offset_stack.push(offset_stack.empty() ? 0 : offset_stack.top());
//
//}
//
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
//void Insert_a_item(base_type_info item){
//
//    tables_stack.top().push(item);
//    assert(!offset_stack.empty() && !tables_stack.empty());
//
//    int current_ofsset = offset_stack.top();
//    offset_stack.pop();
//    offset_stack.push(1 + current_ofsset);
//
//}
//
//void Insert_a_function(base_type_info func){
//
//
//}


#endif //COMPI_3_STRUCTS_HPP
