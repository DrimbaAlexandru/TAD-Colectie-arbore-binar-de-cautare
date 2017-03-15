#pragma once
#include <iostream>
#include "noduri.h"

using namespace std;

template <typename TElem>
class stiva
{
private:
    nod<TElem> *first;
public:
    stiva(){first=(nullptr);}
    void push(TElem data)
    {
        nod<TElem>* u=first;
        first=new nod<TElem>(data);
        first->set_next(u);
    }
    TElem pop()
    {
        TElem d=first->get_data();
        nod<TElem> *u=first;
        first=first->get_next();
        delete u;
        return d;
    }
    int valid()
    {
        return first!=nullptr;
    }
    TElem get_first()
    {
        return first->get_data();
    }
    ~stiva()
    {
        nod<TElem>* u=first;
        while(first!=nullptr)
        {
            u=first;
            first=first->get_next();
            delete u;
        }
    }
};

template <typename TElem>
class coada
{
private:
    nod<TElem> *first;
public:
    coada(){first=(nullptr);}
    void push(TElem data)
    {
        nod<TElem>* p=first;
        if(first==nullptr)
            first=new nod<TElem>(data);
        else
        {
            while(p->get_next()!=nullptr)
                p=p->get_next();
            p->set_next(new nod<TElem>(data));
        }
    }
    TElem pop()
    {
        TElem d=first->get_data();
        nod<TElem> *u=first;
        first=first->get_next();
        delete u;
        return d;
    }
    int valid()
    {
        return first!=nullptr;
    }
    TElem get_first()
    {
        return first->get_data();
    }
    ~coada()
    {
        nod<TElem>* u=first;
        while(first!=nullptr)
        {
            u=first;
            first=first->get_next();
            delete u;
        }
    }
};




