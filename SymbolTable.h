//
// Created by guy on 24/05/2021.
//

#ifndef COMPI_3_SYMBOLTABLE_H
#define COMPI_3_SYMBOLTABLE_H

#include "helpers.h"

typedef int type;

class Symbol
{
public:
    string Name;
    string Type;
    int Offset;

    Symbol(const char* id, const char* t_type, int offset)
    {
        Name = *(new string(id));
        Type = *(new string(t_type));
        Offset = offset;
    }

    ~Symbol() = default;

};

class SymbolTable
{
public:
    bool isMainExists;

    SymbolTable()
    {
        isMainExists = false;
    }
    bool isMainExist()
    {
        return isMainExists;
    }

    void pop()
    {
        //TODO: Pop from current scope
    }

    int addFunc(funcDeclaration & funcToAdd)
    {
        //TODO: Add func to database
        return 0;
    }

    int isFuncExistsByName(funcDeclaration funcToSearch)
    {
        return 0;
        //TODO: Check if func exists in DB
    }

    int argDuplicateInFuncSig(funcDeclaration & funcToAdd)
    {
        return 0;
        //TODO: Check for arg duplication
    }

    int AddNewTable(const char* type)
    {
        return 0;
    }

    int isVarExists(const char* ID)
    {
        return 0;
    }

    bool isInsideWhile()
    {
//        if(this.top.type="WHILE"){
//            return true;
//        }
//        else{
//            return false
//        }
        return true;
    }

    int addNewArg(Symbol s)
    {
        return 0;
    }

    bool isAssignLegal(const char* type1, const char* type2)
    {
        return true;
    }

    Symbol searchSymbolByName(const char* name)
    {
        return *(new Symbol("aa", "aa", 0));
    }

    funcDeclaration * getLastFunc()
    {
        return NULL;
    }

    bool isFunctionExist(funcDeclaration f, bool checkType)
    {
        //Check if function exists in database, with same parameters.
        //If checkType=true, we also check return type.
        return true;
    }

    char* getFunctionType(const char* funcName)
    {
        return NULL;
        //return the function's return type
    }

};


#endif //COMPI_3_SYMBOLTABLE_H
