#include <iostream>
#include "SymbolTable.h"
#include "hw3_output.h"
#include "helpers.h"
#define YYSTYPE Node*

SymbolTable * symbolTable = new SymbolTable();
/* Program -> funcs */
Node * a$$ = new Node();
Node * a$1 = new Node();
Node * a$2 = new Node();
Node * a$3 = new Node();
Node * a$4 = new Node();
Node * a$5 = new Node();
Node * a$6 = new Node();

int yylineno = 0;
const char* yytext = "yytext";
int x = 0;
SymbolTable * st = new SymbolTable();
funcDeclaration funcToAdd = *(new funcDeclaration());
using namespace output;

void programGozerFuncs1()
{
       if(!symbolTable->isMainExist())
       {
           errorMainMissing();
           exit(0);
       }
       a$$ = new Program();

       //TODO: Pop from symbol table
}

void FuncsGozerEpsilon2()
{
    a$$ = new Funcs();
}

void FuncsGozerFuncsDeclFuncs3()
{
    a$$ = new Funcs();
}

void FuncDeclGozerBlaBla4(int x)
{

    //RetType ID LPAREN Formals RPAREN LBRACE Statements RBRACE

    /*
    * Check if function already declared. If yes - ERROR.
    * Create new scope for the function's variable.
    * Add function to database.
    */

    //TODO: Change from a$n to $n

    //TODO: On parser.ypp this code is being add after (RetType ID LPAREN Formals RPAREN)
    //TODO: But before LBRACE Statements RBRACE

    RetType* tmp1 = (RetType*) a$1;
    Node * tmp2 = (funcDeclaration*) a$2;
    Formals * tmp4 = (Formals*) a$4;

    if(symbolTable->isFuncExists(funcToAdd))
    {
        //report ERROR
    }

    if(symbolTable->argDuplicateInFuncSig(funcToAdd)) //TODO: Send real object referenced by $4
    {
        //Report ERROR
    }

    funcDeclaration * toInsert = new funcDeclaration(tmp1->info.c_str(), tmp4->FormalDeclarationsList.formalsListDec,tmp1->retType.c_str());

    symbolTable->addFunc(*toInsert);

    //TODO: This adds after (LBRACE Statements RBRACE): (Not sure tho)
    symbolTable->pop();

}

void RetType_Gozer_Type()
{
    Type * tmp1 = (Type*)a$1;
    a$$ = new RetType(tmp1->type.c_str());
}

void RetType_Gozer_Void()
{
    a$$ = new RetType("void");
}

void Formals_Gozer_Epsilon()
{
    a$$ = new Formals();
}

void Formals_Gozer_FormalsList()
{
    a$$ = new Formals((FormalsList*)a$1);
}

void FormalsList_Gozer_Formalsdecl()
{
    a$$ = new FormalsList((formalDeclaration*)a$1);
}

void Formalsdecl_Gozer_FormalDeclCOMMAFormalsList()
{
    a$$ = new FormalsList((formalDeclaration*)a$1, (FormalsList*)a$3);
}

void Formalsdecl_Gozer_TypeID()
{
    a$$ = new formalDeclaration(((Type*)a$1)->type.c_str(), ((Node*)a$2)->info.c_str(), yylineno);
}

void Statements_Gozer_Statement()
{
    a$$ = new statements();
}

void Statements_Gozer_StatementsStatement()
{
    a$$ = new statements();
}

void Statements_Gozer_LBRACEStatementsRBRACE() {
    type a = 0;

    //open a new if block block right after lbrace
    //pop the block after Statements

    //this is right after lbrace
    symbolTable->AddNewTable("IF scope");

    //this is before rbrace
    symbolTable->pop();
    a$$ = new statement("");


}

void StatementGozerTypeIdSc()
{

    const char* id = a$2->info.c_str();

    //Check if the a variable with the same ID was not declared on containing scope.
    //Add to symbol table: Add this variable to the top table.

    if(symbolTable->isArgExists(id))
    {
        //Report ERROR
    }

    //create new arg object and insert to the *last* table on the symbol table.


}

void StatementGozerWhileLPARENexpRPARENStatement()
{
    //open a block because of while statement
    //open a block because of Braces

    string type = ((Exp*)a$3)->type;

    if(type!="BOOL"){
        errorMismatch(yylineno);
    }


}



int main()
{
    printf("ho");
    return 0;
}

