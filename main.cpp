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

void FuncDeclGozerBlaBla4()
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
    //Node * tmp2 = (funcDeclaration*) a$2;
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

    //open a new if block block right after lbrace
    //pop the block after Statements

    //this is right after lbrace
    symbolTable->AddNewTable("BLOCK");

    //this is before rbrace
    symbolTable->pop();
    a$$ = new statement();
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

void StatementGozer_While_LPAREN_exp_RPAREN_Statement()
{
    //open a block because of while statement
    //open a block because of Braces?

    string type = ((Exp*)a$3)->type;

    if(type!="BOOL"){
        errorMismatch(yylineno);
        exit(0);
    }
    symbolTable->AddNewTable("WHILE");

    //After Statement
    symbolTable->pop();
    a$$ = new statement();
}

void StatementGozerBreakSC() {
    if (!symbolTable->isInsideWhile()) {
        errorUnexpectedBreak(yylineno);
        exit(0);
    }
    a$$ = new statement();
}

void StatementGozerContinueSC() {
    if (!symbolTable->isInsideWhile()) {
        errorUnexpectedBreak(yylineno);
        exit(0);
    }
    a$$ = new statement();
}

void Statement_Gozer_Type_Id_Assign_Exp_Cs()
{
    Exp * tmp = (Exp*)a$3;

    const char* id = a$2->info.c_str();
    const char* l_type = a$1->info.c_str();
    const char* r_type = tmp->type.c_str();

    Symbol arg = *(new Symbol(id, l_type, 0));

    //Check if ID already exists in containing block. If yes - ERROR.
    //Check if assign operator is legal. If no - ERROR.
    //Add Arg to symbol table.

    if(symbolTable->isArgExists(id))
    {
        //report ERROR
    }

    if(!symbolTable->isAssignLegal(l_type,r_type))
    {
        //report ERROR;
    }

    symbolTable->addNewArg(arg);

    a$$ = new statement();

}

void Statement_Gozer_Id_Assign_Exp_Cs()
{
    Exp * tmp = (Exp*)a$3;

    const char* id = a$1->info.c_str();
    const char* r_type = tmp->type.c_str();

    const char* l_type = symbolTable->searchSymbolByName(id).Type.c_str();

    //Check if Id exists on containing scope. If not - return ERROR.
    //Check if assign is legal. If not - return ERROR.
    if(!symbolTable->isArgExists(r_type))
    {
        //return ERROR
    }

    if(!symbolTable->isAssignLegal(l_type,r_type))
    {
        //report ERROR
    }

    a$$ = new statement();
}

void StatementGozer_IF_LPAREN_exp_RPAREN_Statement_precIF()
{
    //open a block because of while statement
    //open a block because of Braces?

    string type = ((Exp*)a$3)->type;

    if(type!="BOOL"){
        errorMismatch(yylineno);
        exit(0);
    }
    symbolTable->AddNewTable("IF");

    //After Statement
    symbolTable->pop();
    a$$ = new statement();
}

void StatementGozer_IF_LPAREN_exp_RPAREN_Statement_ELSE()
{
    //open a block because of while statement
    //open a block because of Braces?

    string type = ((Exp*)a$3)->type;

    if(type!="BOOL"){
        errorMismatch(yylineno);
        exit(0);
    }
    symbolTable->AddNewTable("IF");

    symbolTable->AddNewTable("ELSE");

    //After Statement
    symbolTable->pop();
    a$$ = new statement();
}

void StatementGozer_SWITCH_LPAREN_exp_RPAREN_Statement_ELSE()
{
    //open a block because of while statement
    //open a block because of Braces?

    string type = ((Exp*)a$3)->type;

    if(type!="BOOL"){
        errorMismatch(yylineno);
        exit(0);
    }
    symbolTable->AddNewTable("IF");

    //After Statement
    symbolTable->pop();
    a$$ = new statement();
}

void ExpList_Gozer_Exp()
{
    a$$ = new EXPlist((Exp*)a$1);
}

void ExpList_Gozer_Exp_COMMA_ExpList()
{
    a$$ = new EXPlist((Exp*)a$1,(EXPlist*)a$3);
}

int main()
{
    printf("ho");
    return 0;
}

