#include "noduri.h"
#include "CoadaStiva.h"
#include <iostream>

using namespace std;


template <typename TElem>
class iterator_ABC_SRD;

template <typename TElem>
class iterator_ABC_SDR;

template <typename TElem>
class iterator_ABC_RSD;


///-----------------------------ARBORE BINAR DE CAUTARE------------------------------------
template <typename TElem>
class ABC
{
private:
    nod_abc<TElem> *varf;
public:
    ABC(){varf=nullptr;}
    ABC(nod_abc<TElem> *varf2){varf=varf2;}
    ABC(const ABC &other){varf=new nod_abc<TElem>(*(other.varf));}

    ///returneaza un pointer catre radacina arborelui
    nod_abc<TElem>* get_varf()
    {
        return varf;
    }

    ///adauga un element in arbore, dupa relatia <=
    void push(TElem el)
    {

        if(varf==nullptr)
            {varf=new nod_abc<TElem>(el); return;}
        nod_abc<TElem> *c=varf,*prec=nullptr,*p;
        p=cauta(el);
        if(p!=nullptr)
            {p->aparitii++;
            return;}
        while(c!=nullptr)
        {
            prec=c;
            if(el<=c->get_data())
                c=c->get_st();
            else
                c=c->get_dr();
        }
        if(el<=prec->get_data())
            prec->set_st(new nod_abc<TElem>(el));
        else
            prec->set_dr(new nod_abc<TElem>(el));
    }

    ///Returneaza un pointer catre nodul pe care se afla elementul cautat in arbore sau nullptr daca nu exista
    nod_abc<TElem>* cauta(TElem el)
    {
        nod_abc<TElem> *p=varf;
        while((p!=nullptr))
        {
            if(p->get_data()==el)
                return p;
            if(el<=p->get_data())
                p=p->get_st();
            else
                p=p->get_dr();
        }
        return nullptr;
    }

    ///returneaza nodul parinte al unui nod dat sau nullptr daca nodul dat nu se afla in arbore sau este radacina arborelui
    nod_abc<TElem>* get_parent(nod_abc<TElem>* n)
    {
        if(n==varf)
            return nullptr;
        if(n==nullptr)
            return nullptr;

        TElem el=n->get_data();
        nod_abc<TElem> *p=varf;

        while((p!=nullptr))
        {
            if(p->get_st()==n)
                return p;
            if(p->get_dr()==n)
                return p;
            if(el<=p->get_data())
                p=p->get_st();
            else
                p=p->get_dr();
        }
        return nullptr;
    }
    ///returneaza pointer catre nodul ce contine valoarea minima a subarborelui dat de nodul dat ca parametru
    nod_abc<TElem>* minim(nod_abc<TElem>* start)
    {
        nod_abc<TElem>* p=start;
        if(p==nullptr)
            return nullptr;
        while(p->get_st()!=nullptr)
            p=p->get_st();
        return p;
    }
    ///returneaza pointer catre nodul ce contine valoarea maxima a subarborelui dat de nodul dat ca parametru
    nod_abc<TElem>* maxim(nod_abc<TElem>* start)
    {
        nod_abc<TElem>* p=start;
        if(p==nullptr)
            return nullptr;
        while(p->get_dr()!=nullptr)
            p=p->get_dr();
        return p;
    }
    ///Sterge un element din arbore. Daca nu exista, nu se intampla nimic
    void sterge(TElem el)
    {
        nod_abc<TElem> *p=cauta(el);

        if(p==nullptr)
            return;
        if(p->aparitii>1)
            {p->aparitii--;
            return;}
        if(p->get_dr()==nullptr)
        {
            if(get_parent(p)==nullptr)
                varf=p->get_st();
            else
                {if(el<=get_parent(p)->get_data())
                    get_parent(p)->set_st(p->get_st());
                else
                    get_parent(p)->set_dr(p->get_st());
                }
            p->set_st(nullptr);
            p->set_dr(nullptr);
            delete p;
            return;
        }
        if(p->get_st()==nullptr)
        {
            if(get_parent(p)==nullptr)
                varf=p->get_dr();
            else
                {if(el<=get_parent(p)->get_data())
                    get_parent(p)->set_st(p->get_dr());
                else
                    get_parent(p)->set_dr(p->get_dr());
                }
            p->set_st(nullptr);
            p->set_dr(nullptr);
            delete p;
            return;
        }

        nod_abc<TElem> *pma,*ma;
        ma=maxim(p->get_st());
        pma=get_parent(ma);
        if(p==pma)
        {

            p->set_st(p->get_st()->get_st());
            p->set_data(ma->get_data());
            p->aparitii=ma->aparitii;
            ma->set_st(nullptr);
            ma->set_dr(nullptr);
            delete ma;
        }
        else
        {
            pma->set_dr(nullptr);
            p->set_data(ma->get_data());
            p->aparitii=ma->aparitii;
            ma->set_st(nullptr);
            ma->set_dr(nullptr);
            delete ma;
        }
    }

    ~ABC()
    {
        delete varf;
    }

    ///Returneaza un iterator de parcurgere in inordine
    iterator_ABC_SRD<TElem> SRD_begin()
    {
        return iterator_ABC_SRD<TElem>(this);
    }

    ///Returneaza un iterator de parcurgere in postordine
    iterator_ABC_SDR<TElem> SDR_begin()
    {
        return iterator_ABC_SDR<TElem>(this);
    }

    ///Returneaza un iterator de parcurgere in preordine
    iterator_ABC_RSD<TElem> RSD_begin()
    {
        return iterator_ABC_RSD<TElem>(this);
    }

};

template <typename TElem>
class iterator_ABC_SRD
{
private:
    nod_abc<TElem> *poz;
    ABC<TElem> *arb;
    int contor;
    coada<nod_abc<TElem>*> c;
    stiva<nod_abc<TElem>*> s;
public:
    iterator_ABC_SRD(ABC<TElem> *abc):arb{abc}
    {
        nod_abc<TElem> *p=arb->get_varf();
        if(p==nullptr) return;
        while((s.valid())||(p!=nullptr))
        {
            while(p!=nullptr)
            {
                s.push(p);
                p=p->get_st();
            }
            c.push(s.get_first());
            p=s.pop();
            p=p->get_dr();
        }
        poz=c.get_first();
        contor=poz->aparitii;

    }

    bool valid()
    {
        return c.valid();
    }
    void operator++(int)
    {
        if(contor>1)
            contor--;
        else
        {
            if(c.valid())
            {
                c.pop();
                if(c.valid())
                {
                    poz=c.get_first();
                    contor=poz->aparitii;
                    return;
                }
            }
            poz=nullptr;
        }
    }
    TElem operator*()
    {
        return c.get_first()->get_data();
    }
};

template <typename TElem>
struct pk
{
    nod_abc<TElem> *nod=nullptr;
    int k=0;
};


template <typename TElem>
class iterator_ABC_SDR
{
private:
    nod_abc<TElem> *poz;
    ABC<TElem> *arb;
    int contor;
    coada<nod_abc<TElem>*> c;
    stiva<pk<TElem>> s;
public:
    iterator_ABC_SDR(ABC<TElem> *abc):arb{abc}
    {
        pk<TElem> aux;

        nod_abc<TElem> *p=arb->get_varf();
        if(p==nullptr) return;
        while((s.valid())||(p!=nullptr))
        {
            while(p!=nullptr)
            {
                aux.nod=p;
                aux.k=0;
                s.push(aux);
                p=p->get_st();
            }
            //c.push(s.get_first().nod);
            aux=s.pop();
            p=aux.nod;
            if(aux.k==0)
            {
                aux.k=1;
                aux.nod=p;
                s.push(aux);
                p=p->get_dr();
            }
            else
            {
                c.push(p);
                p=nullptr;
            }
        }
        poz=c.get_first();
        contor=poz->aparitii;

    }

    bool valid()
    {
        return c.valid();
    }
    void operator++(int)
    {
        if(contor>1)
            contor--;
        else
        {
            if(c.valid())
            {
                c.pop();
                if(c.valid())
                {
                    poz=c.get_first();
                    contor=poz->aparitii;
                    return;
                }
            }
            poz=nullptr;
        }
    }
    TElem operator*()
    {
        return c.get_first()->get_data();
    }
};


template <typename TElem>
class iterator_ABC_RSD
{
private:
    nod_abc<TElem> *poz;
    ABC<TElem> *arb;
    int contor;
    coada<nod_abc<TElem>*> c;
    stiva<nod_abc<TElem>*> s;
public:
    iterator_ABC_RSD(ABC<TElem> *abc):arb{abc}
    {
        nod_abc<TElem> *p=arb->get_varf();
        if(p==nullptr) return;
        s.push(p);
        while(s.valid())
        {
            p=s.get_first();
            c.push(s.pop());
            if(p->get_dr())
                s.push(p->get_dr());
            if(p->get_st())
                s.push(p->get_st());
        }

        poz=c.get_first();
        contor=poz->aparitii;

    }

    bool valid()
    {
        return c.valid();
    }
    void operator++(int)
    {
        if(contor>1)
            contor--;
        else
        {
            if(c.valid())
            {
                c.pop();
                if(c.valid())
                {
                    poz=c.get_first();
                    contor=poz->aparitii;
                    return;
                }
            }
            poz=nullptr;
        }
    }
    TElem operator*()
    {
        return c.get_first()->get_data();
    }
};
