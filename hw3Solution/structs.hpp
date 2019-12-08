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



class base_type_info {

public:

    // we need to spilt these ********
    string name;
    //this refers to the token enums
    int type;
    string value;
    //might remove
    int offset;
    string in;
    bool isAssignable;




};


/*

union t {
base_type_info expType;
base_type_info opType;
base_type_info BType;
base_type_info CommentType;
base_type_info ProgramType;
base_type_info EnumType;
//..
};




class CType{
public:
//enum = what type are you
t ctype;



};



CType x;
//if enum is exp
base_type_info tmpexp = x.ctype.expType;

*/




stack<int> offset_stack;
stack<stack<base_type_info>> tables_stack;

bool isContainItem(stack<base_type_info>& table_stack , base_type_info& item){

    stack<base_type_info> cpy_stack;
    bool found = false;
    base_type_info cpy_item;

    while(!table_stack.empty()){
        //TODO check other identeinssfd
        if (table_stack.top().name == item.name){
            found = true;
            break;
        }
        cpy_item = table_stack.top();
        cpy_stack.push(cpy_item);
        table_stack.pop();
    }

    while (!cpy_stack.empty()){
        cpy_item = cpy_stack.top();
        table_stack.push(cpy_item);
        cpy_stack.pop();
    }

    return found;

}
bool isAlreadyDefined( base_type_info& item){


    stack<stack<base_type_info>> cpy_table_stack;
    stack<base_type_info> cpy_stack;
    bool found = false;

    while(!tables_stack.empty()){
        if (isContainItem(tables_stack.top() , item)){
            found = true;
            break;
        }
        cpy_stack = tables_stack.top();
        cpy_table_stack.push(cpy_stack);
        tables_stack.pop();
    }

    while(!cpy_table_stack.empty()){
        cpy_stack = cpy_table_stack.top();
        tables_stack.push(cpy_stack);
        cpy_table_stack.pop();
    }

    return found;




}


void Open_a_Block(){

    stack<base_type_info> new_block;
    tables_stack.push(new_block);
    offset_stack.push(offset_stack.empty() ? 0 : offset_stack.top());

}


void Exit_a_block(){

    while(!tables_stack.top().empty()){
        tables_stack.top().pop();
    }
}


void Close_a_Block(){

    Exit_a_block();
    offset_stack.pop();

}

void Insert_a_item(base_type_info item){

    tables_stack.top().push(item);
    assert(!offset_stack.empty() && !tables_stack.empty());

    int current_ofsset = offset_stack.top();
    offset_stack.pop();
    offset_stack.push(1 + current_ofsset);

}

void Insert_a_function(base_type_info func){


}


#endif //COMPI_3_STRUCTS_HPP
