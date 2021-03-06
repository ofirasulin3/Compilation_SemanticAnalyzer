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
    funcDeclaration * toInsert = new funcDeclaration(tmp1->info.c_str(), tmp4->FormalDeclarationsList.formalsListDec,tmp1->retType.c_str());
    int dupelicateIndex;


    if(symbolTable->isFuncExistsByName(*toInsert))
    {
        errorDef(yylineno, toInsert->funcName);
    }

    dupelicateIndex = symbolTable->argDuplicateInFuncSig(*toInsert);

    if(dupelicateIndex!= -1) //TODO: Send real object referenced by $4
    {
        errorDef(yylineno, toInsert->paramList[dupelicateIndex].name);
    }


    symbolTable->addFunc(*toInsert);

    //Symbol funcSym = (*new Symbol(tmp1->info.c_str(), "FUNCTION", 0));

    symbolTable->AddNewTable(tmp1->info.c_str());

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
    a$$ = new RetType("VOID");
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

    if(symbolTable->isVarExists(id))
    {
        errorDef(yylineno,((Node*)a$2)->info);
    }

    //create new arg object and insert to the *last* table on the symbol table.


}

void StatementGozer_While_LPAREN_exp_RPAREN_Statement()
{
    //open a block because of while statement
    //No need to open a block because of Braces because it happens on statement rule

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

    if(symbolTable->isVarExists(id))
    {
        errorDef(yylineno,((Node*)a$2)->info);
    }

    if(!symbolTable->isAssignLegal(l_type,r_type))
    {
        errorMismatch(yylineno);
    }

    symbolTable->addNewArg(arg);

    a$$ = new statement();

}

void Statement_Gozer_Id_Assign_Exp_Cs()
{
    Exp * tmp = (Exp*)a$3;

    const char* id = a$1->info.c_str();
    const char* r_type = tmp->type.c_str();

    //Check if Id exists on containing scope. If not - return ERROR.
    //Check if assign is legal. If not - return ERROR.
    if(!symbolTable->isVarExists(r_type))
    {
        errorUndef(yylineno,((Node*)a$1)->info);
    }

    const char* l_type = symbolTable->searchSymbolByName(id).Type.c_str();

    if(!symbolTable->isAssignLegal(l_type,r_type))
    {
        errorMismatch(yylineno);
    }

    a$$ = new statement();
}

void StatementGozer_IF_LPAREN_exp_RPAREN_Statement_precIF()
{
    //open a block because of while statement
    //No need to open a block because of Braces because it happens on statement rule

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
    //No need to open a block because of Braces because it happens on statement rule

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

void Exp_Gozer_LPAREN_Exp_RPAREN()
{
    a$$ = new Exp("", ((Exp*)a$1)->type.c_str());
}

void Exp_Gozer_Exp_BINOP_Exp()
{
    string leftType = ((Exp*)a$1)->type;
    string rightType = ((Exp*)a$3)->type;
    if((leftType != "INT" && leftType != "BYTE") || (rightType != "INT" && rightType != "BYTE")){
        errorMismatch(yylineno);
        exit(0);
    }
    else{
        string resultType;
        if(leftType == "INT" || rightType != "INT")
            resultType = "INT";
        else
            resultType = "BYTE";
        a$$ = new Exp("", resultType.c_str());
    }
}

void Exp_Gozer_Call()
{
    a$$ = new Exp("", ((call*)a$1)->type.c_str());
}

void Exp_Gozer_NUM()
{
    a$$ = new Exp("", "INT");
}

void Exp_Gozer_STRING()
{
    a$$ = new Exp(((Exp*)a$1)->info.c_str(), "STRING");
}

void Exp_Gozer_Exp_AND_Exp()
{
    string leftType = ((Exp*)a$1)->type;
    string rightType = ((Exp*)a$3)->type;
    if(leftType!="BOOL" || rightType!="BOOL"){
        errorMismatch(yylineno);
        exit(0);
    }
    a$$ = new Exp("","BOOL");
}

void Exp_Gozer_Exp_OR_Exp()
{
    string leftType = ((Exp*)a$1)->type;
    string rightType = ((Exp*)a$3)->type;
    if(leftType!="BOOL" || rightType!="BOOL"){
        errorMismatch(yylineno);
        exit(0);
    }
    a$$ = new Exp("","BOOL");
}

void Exp_Gozer_Exp_RELOP_Exp()
{
    string leftType = ((Exp*)a$1)->type;
    string rightType = ((Exp*)a$3)->type;
    if((leftType != "INT" && leftType != "BYTE") || (rightType != "INT" && rightType != "BYTE")){
        errorMismatch(yylineno);
        exit(0);
    }
    a$$ = new Exp("","BOOL");
}

void statement_gozer_Return_sc()
{
    //Check if function return type is void - report ERROR



    if(symbolTable->getLastFunc()->returnType!="void")
    {
        errorMismatch(yylineno);
        exit(0);
    }
    a$$ = new statement("");
}

void statement_gozer_return_ex_sc()
{

    const char* type = ((Exp*)a$2)->type.c_str();

    //Check if function return type is same as expression type - report ERROR
    if(symbolTable->getLastFunc()->returnType!=type)
    {
        errorMismatch(yylineno);
        exit(0);
    }
    a$$ = new statement("");
}

void call_gozer_id_lparen_explist_rparen()
{
    //Check if function name already exists
    //Check argument match
    EXPlist * tmp = (EXPlist*)a$3;
    vector<formalDeclaration> tmp1;
    vector<formalDeclaration> paramList;
    vector<Exp> vectorOfExp = *(new vector<Exp>(tmp->vectorOfExp));
    vector<string> idVector;
    while(vectorOfExp.size()>0)
    {
        const char* param_type = vectorOfExp.back().type.c_str();
        idVector.push_back(*(new string(param_type)));
        vectorOfExp.pop_back();
        formalDeclaration * toInsert = new formalDeclaration(param_type, "", 0);
        tmp1.push_back((*toInsert));
    }

    for(int i = 0; i<tmp1.size(); i++)
    {
            paramList[i] = tmp1[tmp1.size()-1-i];
    }

    const char* funcName = a$1->info.c_str();
    funcDeclaration * newFunc = new funcDeclaration(funcName,paramList , " ");
    if(!symbolTable->isFuncExistsByName(*newFunc))
    {
        errorUndefFunc(yylineno,((Node*)a$1)->info);
        exit(0);
    }
    if(!symbolTable->isFunctionExist(*newFunc, false))
    {
        errorPrototypeMismatch(yylineno,newFunc->funcName, idVector);
        exit(0);
    }


    a$$ = new call(symbolTable->getFunctionType(funcName), funcName);
}

void call_gozer_ID_Lparen_rparen()
{
    //Check if function exists in DB
    //Check parameters match
    const char* funcName = a$1->info.c_str();
    vector<formalDeclaration> paramList;
    funcDeclaration * newFunc = new funcDeclaration(funcName,paramList , " ");

    if(!symbolTable->isFuncExistsByName(*newFunc))
    {
        errorUndefFunc(yylineno,((Node*)a$1)->info);
        exit(0);
    }

    a$$ = new call(symbolTable->getFunctionType(funcName), funcName);

}

void exp_gozer_id()
{
    //Check if ID exist on DB. If not - report ERROR.
    if(!symbolTable->isVarExists(a$1->info.c_str()))
    {
        errorUndef(yylineno,((Node*)a$1)->info);
        exit(0);
    }

    a$$ = new Exp("", symbolTable->searchSymbolByName(a$1->info.c_str()).Type.c_str());
}

void exp_gozer_numb()
{
    int maxVal = 255;
    if(stoi(((Node*)a$1)->info) > maxVal)
    {
        errorByteTooLarge(yylineno,((Node*)a$1)->info);
        exit(0);
    }
}

void exp_gozer_not_exp()
{
    Exp* tmp = (Exp*)a$2;
    if(tmp->type == *(new string("bool")))
    {
        a$$ = new Exp("bool","");
    }
    else
    {
        errorMismatch(yylineno);
        exit(0);
    }
}

void statement_gozer_callSC()
{
    a$$ = new statement();
}

void type_gozer_int()
{
    a$$ = new Type("","INT");
}

void type_gozer_byte()
{
    a$$ = new Type("","byte");
}

void type_gozer_bool()
{
    a$$ = new Type("","bool");
}


void StatementGozer_SWITCH_LPAREN_exp_RPAREN_LBRACE_CaseList_RBRACE()
{
    //open a block because of switch statement
    //open a block because of Braces

    string type = ((Exp*)a$3)->type;

    if(!symbolTable->isVarExists(((Exp*)a$3)->info.c_str())){
        errorDef(yylineno, ((Exp*)a$3)->info);
        exit(0);
    }
    symbolTable->AddNewTable("SWITCH");

    //After LBRACE
    symbolTable->AddNewTable("SWITCH SCOPE");

    //After RBRACE
    symbolTable->pop();
    symbolTable->pop();
    a$$ = new statement();
}

void CaseList_Gozer_CaseDecl_CaseList()
{
    a$$ = new CaseList();
}

void CaseList_Gozer_CaseDecl()
{
    a$$ = new CaseList();
}

void CaseList_Gozer_DEFAULT_COLON_Statements()
{
    a$$ = new CaseList();
}

void CaseList_Gozer_CASE_NUM_COLON_Statements()
{
    a$$ = new CaseList();
}



int main()
{
    printf("ho");


    return 0;
}

