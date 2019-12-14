#include "structs.hpp"



Scope::Scope(ScopeType type): type(type){
        local_table = stack<Variable*>();
    }

       void Scope::insertVar(Variable* var){
       local_table.push(var);
    }


Variable* Scope::getVar(string gname){
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


    Scope::~Scope(){

        while(!local_table.empty()){

            delete(local_table.top());
            local_table.pop();
        }
    }


  Variable* Symbol_Table::getVar(string name){

        stack<Scope> cpy_stack = stack<Scope>();
        
        for(int i = scopes_table.size()-1; i >=0; i--){
            auto cur = scopes_table[i].getVar(name);
            if(cur != nullptr)
                return cur;
        }
        return nullptr;
    }


    void Symbol_Table::openScope(ScopeType type){
        scopes_table.push_back(Scope(type));
        offset_stack.push(offset_stack.empty() ? 0 : offset_stack.top()); 

    }

    void Symbol_Table::insertVar(Variable* var){
        scopes_table[scopes_table.size()-1].insertVar(var);

        int last_offset = offset_stack.top(); 
        offset_stack.pop(); 
        offset_stack.push(1 + last_offset); 

        var->offset = last_offset;
    }

    void Symbol_Table::closeScope(){
        scopes_table.pop_back();
        offset_stack.pop();


    }
