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

    Symbol(const char* id, const char* t_type, const char* val, int lineno)
    {
        ID = *(new string(id));
        Type = *(new string(t_type));
        value = *(new string(val));
        lineNumber = lineno;
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

    int isFuncExists(funcDeclaration & funcToAdd)
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

    int isArgExists(const char* ID)
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
    }


};


#endif //COMPI_3_SYMBOLTABLE_H
