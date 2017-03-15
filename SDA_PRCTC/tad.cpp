#include <vector>
#include <algorithm>

using namespace std;

#define CAT_CARTI 0
#define CAT_MANUSCRISE 1
#define CAT_ZIARE 2
#define CAT_PICTURI 3
#define CAT_MUZICA 4
#define CAT_ALTELE 5

template <typename TElem>
class nod_abc
{
private:
    TElem data;
    nod_abc *st,*dr;
public:
    int aparitii=1;
    nod_abc(){st=nullptr;dr=nullptr;}
    nod_abc(TElem info){st=nullptr;dr=nullptr;data=info;}
    nod_abc(TElem info,nod_abc *sta,nod_abc *dre){st=sta;dr=dre;data=info;}
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

    void add_to_vector_SRD(vector<TElem> &v)
    {
        if(st!=nullptr)
            st->add_to_vector_SRD(v);
        v.push_back(this->get_data());
        if(dr!=nullptr)
            dr->add_to_vector_SRD(v);
    }
};



template <typename TElem>
class ABC
{
private:
    nod_abc<TElem> *varf;
    int nr_elemente=0;
    friend class iterator_ABC_SRD<TElem>;
public:
    ABC(){varf=nullptr;}
    ABC(nod_abc<TElem> *varf2){varf=varf2;}
    ABC(const ABC &other){varf=new nod_abc<TElem>(*(other.varf));}

    ///Returneaza un pointer la nodul din vaful arborelui sau nullptr daca arborele este vid
    nod_abc<TElem>* get_varf()
    {
        return varf;
    }

    ///Adauga elementul el in colectie
    void push(TElem el)
    {
        nr_elemente++;
        //Daca arborele e vid, varful devine nodul nou-creat
        if(varf==nullptr)
            {varf=new nod_abc<TElem>(el); return;}
        nod_abc<TElem> *c=varf,*prec=nullptr,*p;
        //Daca elementul exista deja, incrementam contorul sau
        p=cauta(el);
        if(p!=nullptr)
            {p->aparitii++;
            return;}
        //Cautam pozitia pe care trebuie adaugat noul nod
        while(c!=nullptr)
        {
            prec=c;
            if(el<=c->get_data())
                c=c->get_st();
            else
                c=c->get_dr();
        }
        //Cream noul nod si al legam de parintele sau
        if(el<=prec->get_data())
            prec->set_st(new nod_abc<TElem>(el));
        else
            prec->set_dr(new nod_abc<TElem>(el));
    }

    ///Cauta un element in colectie. Returneaza un pointer la nodul in care se afla sau nullptr daca nu exista
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

    ///Returneaza parintele unui nod. Daca nodul este varf sau nu se afla in arbore, se returneaza nullptr
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

    ///Returneaza valoarea minima dintr-un subarbore dat de nodul-varf start
    nod_abc<TElem>* minim(nod_abc<TElem>* start)
    {
        nod_abc<TElem>* p=start;
        if(p==nullptr)
            return nullptr;
        while(p->get_st()!=nullptr)
            p=p->get_st();
        return p;
    }

    ///Returneaza valoarea maxima dintr-un subarbore dat de nodul-varf start
    nod_abc<TElem>* maxim(nod_abc<TElem>* start)
    {
        nod_abc<TElem>* p=start;
        if(p==nullptr)
            return nullptr;
        while(p->get_dr()!=nullptr)
            p=p->get_dr();
        return p;
    }

    ///Sterge un element(sau decrementeaza numarul de aparitii) din colectie
    void sterge(TElem el)
    {
        nod_abc<TElem> *p=cauta(el);
        //Daca elementul nu exista, se revine
        if(p==nullptr)
            return;
        nr_elemente--;
        //Daca numarul de aparitii este diferit de 1, se decrementeaza
        if(p->aparitii>1)
            {p->aparitii--;
            return;}
        //Daca nu are subarbore drept, se muta subarborele stang in locul nodului pe care s-a gasit elementul si se sterge elementul
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
        //Idem pentru lipsa subarborelui stang
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

        //Daca are si subarbore stang, si subarbore drept,
        //se va inlocui valoarea din nodul in care s-a gasit elementul cu valoarea maxima a subarborelui stang
        //si se va elimina nodul vechi in care s-a gasit valoarea maxima
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
    int get_nr_elemente()
    {
        return nr_elemente;
    }
    vector<TElem> get_vector_SRD()
    {
        vector<TElem> v;
        if(varf!=nullptr)
            varf->add_to_vector_SRD(v);
        return v;
    }

    ~ABC()
    {
        delete varf;
    }

};
class produs
{
private:
    string nume;
    string categorie;
    float pret;
    string descriere;

public:
    produs()
    {

    }
    produs(string nume,string categorie, float pret,string descriere)
    {
        this->nume=nume;
        this->categorie=categorie;
        this->pret=pret;
        this->descriere=descriere;
    }
    bool operator<(const produs& other)
    {
        return(this->nume<other.nume);
    }

    bool operator <=(const produs& other)
    {
        return(this->nume<=other.nume);
    }
    bool operator==(const produs& other)
    {
        return(this->nume==other.nume);
    }

    string get_nume(){return nume;}
    string get_categorie(){return categorie;}
    float get_pret(){return pret;}
    string get_descriere(){return descriere;}

    void set_pret(float pret2){pret=pret2;}
    void set_descriere(string descr){descriere=descr;}
};

template <typename TElem>
class iterator_ABC_SRD
{
private:

};
