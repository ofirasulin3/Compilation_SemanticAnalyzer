//
// Created by guy on 24/05/2021.
//

#ifndef COMPI_3_HELPERS_H
#define COMPI_3_HELPERS_H
#include <string>
#include <vector>

using namespace std;

class Node {
public:
    string info;
    Node()
    {
        info = "";
    }

    explicit Node(const char *data)
    {
        info = *(new string(data));
    }

    ~Node() = default;
};

class Program:public Node {
public:
    Program() = default;

    ~Program() = default;
};

class Funcs:public Node {
public:
    Funcs() = default;

    ~Funcs() = default;
};


class formalDeclaration: public Node { //formalDecl
public:
    string type;
    string name;
    long lineNum;

    explicit formalDeclaration(const char* t_type, const char* id, long lineno)
    {
//        info = *(new string(data));
        type = *(new string(t_type));
        name = *(new string(id));
        long lineNum = lineno;
    }

    ~formalDeclaration() = default;
};

class funcDeclaration: public Node {
public:
    string funcName;
    vector<formalDeclaration> paramList;
    string returnType;

    funcDeclaration(const char* func_ID, vector<formalDeclaration> params, const char* retType)
    {
//        info = *(new string(data));
        funcName = *(new string(func_ID));
        paramList = *(new vector<formalDeclaration>(params));
        returnType = *(new string (retType));
    }

    funcDeclaration() = default;

    ~funcDeclaration() = default;
};

class Exp: public Node
{
public:
    string type;

    explicit Exp(const char* data, const char* t_type)
    {
        info = *(new string(data));
        type = *(new string(t_type));
    }

    ~Exp()  = default;
};


class statement: public Node
{
public:
    string ID;

    statement(const char* id = "")
    {
        ID = id;
    }
    string getData()
    {
        return this->info;
    }
    ~statement() = default;
};

class statements: public Node
{
public:
    statements() = default;

//    statements()
//    {
//        info = *(new string(" "));
//    };

};

class Type: public Node
{
public:
    string type;

    Type(const char* data, const char* t_type)
    {
        info = *(new string(data));
        type = *(new string(t_type));
    }
    ~Type() = default;
};

class EXPlist : public Node
{
public:
    vector<Exp> vectorOfExp;
    EXPlist(Exp* exp, EXPlist* expList = NULL)
    {
        //info = *(new string(data));
        this->vectorOfExp.push_back(*exp);
        if(expList!=NULL)
        {
//            this->vectorOfExp.insert(*exp);
//            this->vectorOfExp.insert(this->vectorOfExp.end(), expList->vectorOfExp.begin(), expList->vectorOfExp.end());
        }
    }
    EXPlist() = default;

    ~EXPlist() = default;
};

class call: public Node{

public:
    EXPlist expList;
    string type;
    string ID;

    //TODO: maybe need explicit?
    call(/*const char * data, */const char* t_type, const char* id, EXPlist* expList = NULL)
    {
        //info = *(new string(data));
        type = *(new string(t_type)); //return type of function
        ID = *(new string(id));//function name

        if(expList)
        {
            this->expList = *expList;
        }
    }
    ~call()  = default;
};

class FormalsList: public Node
{
public:
    vector<formalDeclaration> formalsListDec;
    vector<int> LineNumbers;

    FormalsList() = default;

    FormalsList(formalDeclaration* fDec, FormalsList* ftl = NULL)
    {
        this->formalsListDec.push_back(*fDec);
        this->LineNumbers.push_back(fDec->lineNum);

        if(ftl)
        {
            this->formalsListDec.insert(this->formalsListDec.end(), ftl->formalsListDec.begin(), ftl->formalsListDec.end());
            this->LineNumbers.insert(this->LineNumbers.end(), ftl->LineNumbers.begin(), ftl->LineNumbers.end());
        }
    }
    ~FormalsList() = default;
};

class Formals: public Node
{
public:
    FormalsList FormalDeclarationsList;

    explicit Formals(FormalsList* fList=NULL)
    {
        if(fList)
        {
            FormalDeclarationsList = *fList;
        }
    };
    Formals(const Formals& formals): Node(formals.info.c_str()), FormalDeclarationsList(formals.FormalDeclarationsList){};
//    Formals() = default;
    ~Formals()  = default;

    FormalsList retList()
    {
        return FormalDeclarationsList;
    }
};


class RetType: public Node
{
public:
    string retType;

    RetType(const char* ret_Type)
    {
        retType = *(new string(ret_Type));
//        info = *(new string(data));
    }
    ~RetType() = default;
};


#endif //COMPI_3_HELPERS_H
