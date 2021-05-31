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
    vector<vector<Symbol>> variableTable;
    vector<funcDeclaration> funcList;
    vector<string> scopeTypes;
    vector<int> offsetTable;

    SymbolTable()
    {

        funcDeclaration print = *(new funcDeclaration("print",*(new vector<formalDeclaration>) ,"VOID"));
        print.paramList.push_back(*new formalDeclaration("STRING", " ", 0));

        funcDeclaration printi = *(new funcDeclaration("printi",*(new vector<formalDeclaration>) ,"VOID"));
        print.paramList.push_back(*new formalDeclaration("INT", " ", 0));

        isMainExists = false;
        variableTable = *(new vector<vector<Symbol>>);
        funcList = *(new vector<funcDeclaration>);
        offsetTable = *(new vector<int>);
        scopeTypes = *(new vector<string>);
        offsetTable.push_back(0);
    }

    bool isMainExist()
    {
        return isMainExists;
    }

    void print()
    {
        output::endScope();

        if(scopeTypes.back()!=string("IF") && scopeTypes.back()!=string("ELSE") && scopeTypes.back()!=string("WHILE")
            && scopeTypes.back()!=string("BLOCK")) //Current block is a function block.
        {
            string tmp = scopeTypes.back();
            int i = 0;
            while(tmp!=funcList[i].funcName)
            {
                i++;
            }

            for(i = 0; i<funcList[i].paramList.size(); i++)
            {
                output::printID(funcList[i].paramList[i].name, -i-1, funcList[i].paramList[i].type);
            }

        }

        for(int i = 0;i<variableTable.back().size(); i++)
        {
            output::printID(variableTable.back()[i].Name, variableTable.back()[i].Offset,variableTable.back()[i].Type);
        }
    }

    void pop()
    {
        print();
        variableTable.pop_back();
        offsetTable.pop_back();
        scopeTypes.pop_back();
    }

    int addFunc(funcDeclaration & funcToAdd)
    {
        funcList.push_back(funcToAdd);
        return 0;
    }

    bool isFuncExistsByName(funcDeclaration funcToSearch)
    {
        string fName = funcToSearch.funcName;
        for(int i = 0; i<funcList.size(); i++)
        {
            if(fName == funcList[i].funcName)
            {
                return true;
            }
        }
        return false;
    }

    int argDuplicateInFuncSig(funcDeclaration & funcToAdd)
    {
        for(int i = 0; i<funcToAdd.paramList.size(); i++)
        {
            for(int j = i+1; j<funcToAdd.paramList.size(); j++)
            {
                if(funcToAdd.paramList[i].name == funcToAdd.paramList[j].name)
                {
                    return i;
                }
            }
        }
        return -1;
    }

    int AddNewTable(const char* type)
    {
        offsetTable.push_back(offsetTable.back());
        variableTable.push_back(*(new vector<Symbol>()));
        scopeTypes.push_back(*(new string(type)));

        return 1;
    }

    bool isVarExists(const char* ID)
    {
        for(int i = 0; i<variableTable.size(); i++)
        {
            for(int j = 0; j<variableTable[i].size(); j++)
            {
                if(variableTable[i][j].Name == string(ID))
                {
                    return true;
                }
            }
        }

        return false;
    }

    bool isInsideWhile()
    {
        if(scopeTypes.back() == string("WHILE"))
        {
            return true;
        }
        return false;
    }

    int addNewArg(Symbol & s)
    {
        if(variableTable.size() == 0)
        {
            return -1;
        }

        s.Offset  = offsetTable[offsetTable.size()-1];

        offsetTable[offsetTable.size()-1]++;

        variableTable.back().push_back(s);

        return 1;

    }

    bool isAssignLegal(const char* type1, const char* type2)
    {
        string stype1 = string(type1);
        string stype2 = string(type2);

        if(stype1 == stype2 || (stype1 == string("INT") && stype2 == string("BYTE")))
        {
            return true;
        }

        return false;
    }

    Symbol searchSymbolByName(const char* name)
    {
        for(int i = 0; i<variableTable.size(); i++)
        {
            for(int j = 0; j<variableTable[i].size(); j++)
            {
                if(variableTable[i][j].Name==string(name))
                {
                    return variableTable[i][j];
                }
            }
        }

        return variableTable[0][0]; //should not reach here

    }

    funcDeclaration * getLastFunc()
    {
        return &funcList.back();
    }

    bool equals(funcDeclaration f1, funcDeclaration f2)
    {
        if(f1.paramList.size() != f2.paramList.size() || f1.funcName!=f2.funcName)
        {
            return false;
        }

        for(int i = 0; i<f1.paramList.size(); i++)
        {
            if(f1.paramList[i].type!=f2.paramList[i].type)
            {
                return false;
            }
        }

        return true;

    }


    bool isFunctionExist(funcDeclaration f, bool checkType)
    {
        for(int i = 0; i<funcList.size(); i++)
        {
            if(equals(f,funcList[i]))
            {
                if(checkType)
                {
                    if(f.returnType!=funcList[i].returnType)
                    {
                        return false;
                    }
                }

                return true;

            }
        }
        return false;
    }

    const char* getFunctionType(const char* funcName)
    {
        for(int i = 0; i<funcList.size(); i++)
        {
            if(funcList[i].funcName==string(funcName))
            {
                return funcList[i].returnType.c_str();
            }
        }
        return "NULL";
    }

};


#endif //COMPI_3_SYMBOLTABLE_H
