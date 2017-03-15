#pragma once

template <typename TElem>
class nod_abc
{
private:
    TElem data;
    nod_abc *st,*dr;
public:
    int aparitii=1;
    nod_abc(){st=nullptr;dr=nullptr;
    }
    nod_abc(TElem info){st=nullptr;dr=nullptr;data=info;
    }
    nod_abc(TElem info,nod_abc *sta,nod_abc *dre){st=sta;dr=dre;data=info;
    }
    nod_abc(const nod_abc &other)
    {

        this->data=other.data;
        if(other.st==nullptr)
            this->st=nullptr;
        else
            this->st=new nod_abc(*other.st);
        if(other.dr==nullptr)
            this->dr=nullptr;
        else
            this->dr=new nod_abc(*other.dr);
    }
    ~nod_abc()
    {

        if(this->st!=nullptr) {delete(this->st);}
        if(this->dr!=nullptr) {delete(this->dr);}
    }
    TElem get_data(){return data;}
    nod_abc* get_st(){return st;}
    nod_abc* get_dr(){return dr;}
    void set_st(nod_abc *urm){st=urm;}
    void set_dr(nod_abc *urm){dr=urm;}
    void set_data(TElem info){data=info;}
};

template <typename TElem>
class nod
{
private:
    TElem data;
    nod *urm;
public:
    nod(){urm=nullptr;}
    nod(TElem info){data=info;urm=nullptr;}
    nod(const nod *baza)
    {
        nod *p=this,*c=baza;
        data=baza->data;
        while(c!=nullptr)
        {
            p->urm=new nod(c->data);
            p=p->urm;
            c=c->urm;
        }
    }
    TElem get_data()
    {
        return data;
    }
    nod*  get_next()
    {
        return urm;
    }
    void  set_data(TElem d)
    {
        data=d;
    }
    void set_next(nod* n)
    {
        urm=n;
    }
};
