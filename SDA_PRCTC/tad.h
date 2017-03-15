

using namespace std;

#define CAT_CARTI 0
#define CAT_MANUSCRISE 1
#define CAT_ZIARE 2
#define CAT_PICTURI 3
#define CAT_MUZICA 4
#define CAT_ALTELE 5


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

