#include "structs.hpp"
vector<string> TokensToString(vector<TokenType>& vec){
    vector<string> ret = vector<string>();
    for ( int i = 0; i < vec.size() ; i++)
    {
        switch (vec[i]){

            case INT_t : ret.push_back("INT_t"); break;
            case VOID_t : ret.push_back("VOID_t"); break;
            case BOOL_t : ret.push_back("BOOL_t"); break;
            case BYTE_t : ret.push_back("BYTE_t"); break;
            case B_t : ret.push_back("B_t"); break;
            case STRING_t : ret.push_back("STRING_t"); break;
            default : cout << "shouldnt be here - unexpected token in  TokensToString" << endl; break;
        }
    }

    return ret;
}









    Function::Function(string name , TokenType returnType): Variable(FUNCTION_t, name), returnType(returnType), preconditionCounter(0) {
		paramTypes = vector<TokenType>();
	}

    void Function::addParam(Variable* param) {

        if(name == param->name)
        {
            errorDef(yylineno,param->name);
            exit(0);
        }
        for (auto var : params)
        {
            if(var->name == param->name){
                errorDef(yylineno, param->name);
                exit(0);
            }
        }

        paramTypes.push_back(param->type);
        param->offset = -1 * (params.size() + 1);
		params.push_back(param);
	}

	void Function::ValidateParameters(vector<TokenType>& callerParams) {
		if (callerParams.size() != paramTypes.size()) {
			errorPrototypeMismatch(yylineno, name, TokensToString(paramTypes));
			exit(0);
		}

		for (int i = 0; i < paramTypes.size(); i++) {
            if(!(paramTypes[i] == (callerParams)[i] || ((callerParams)[i] == BYTE_t && paramTypes[i] == INT_t))){
                errorPrototypeMismatch(yylineno, name, TokensToString(paramTypes));
				exit(0);
            }
        }
	}




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


    void Symbol_Table::insertFunc(Function* f) {
		
        scopes_table[scopes_table.size()-1].insertVar(f);
        openScope(FUNCTION);//no need to open scope in parser
        for (int i = 0; i < f->paramTypes.size() ; i++)
        {
            insertVar(f->params[i]);
        }

        
	}


    void Symbol_Table::closeScope(){
        scopes_table.pop_back();
        offset_stack.pop();


    }



