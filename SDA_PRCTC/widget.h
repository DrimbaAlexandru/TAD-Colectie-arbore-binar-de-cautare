#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLayout>
#include <QListWidget>
#include <QPushButton>
#include <QLabel>
#include <QObject>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QString>
#include <QComboBox>
#include <QMessageBox>

#include "tad.h"
#include "ABC.h"

#define MOD_RSD 1
#define MOD_SRD 2
#define MOD_SDR 3


class SDA_GUI : public QWidget
{
private:
    ABC<produs> arb;

    QHBoxLayout *main_layout=new QHBoxLayout;
    QVBoxLayout *left_layout=new QVBoxLayout;
    QVBoxLayout *right_layout=new QVBoxLayout;
    QHBoxLayout *lef_under_layout=new QHBoxLayout;
    QListWidget *lista=new QListWidget;
    QHBoxLayout *r1=new QHBoxLayout,*r2=new QHBoxLayout,*r3=new QHBoxLayout,*r4=new QHBoxLayout;
    QLabel *l_nume=new QLabel("Denumire: "),*l_descriere=new QLabel("Descriere: "),*l_pret=new QLabel("Pret: "),*l_categorie=new QLabel("Categorie: ");
    QComboBox *cb_categorie=new QComboBox;
    QLineEdit *le_nume=new QLineEdit,*le_descriere=new QLineEdit;
    QDoubleSpinBox *sb_pret=new QDoubleSpinBox;
    QPushButton *pb_add=new QPushButton("ADAUGA");
    QPushButton *pb_cauta=new QPushButton("CAUTA");
    QPushButton *pb_delete=new QPushButton("STERGE");
    QPushButton *pb_RSD=new QPushButton("RSD");
    QPushButton *pb_SRD=new QPushButton("SRD");
    QPushButton *pb_SDR=new QPushButton("SDR");
    QPushButton *pb_clean=new QPushButton("Curata campurile");

    void populate_list(int mod)
    {
        lista->clear();
        auto it1=arb.RSD_begin();
        auto it2=arb.SDR_begin();
        auto it3=arb.SRD_begin();
        switch (mod)
        {
            case MOD_RSD:

                while(it1.valid())
                {
                    lista->addItem(QString::fromStdString((*it1).get_nume()));
                    it1++;
                }
                break;
            case MOD_SDR:

                while(it2.valid())
                {
                    lista->addItem(QString::fromStdString((*it2).get_nume()));
                    it2++;
                }
                break;
            case MOD_SRD:

                while(it3.valid())
                {
                    lista->addItem(QString::fromStdString((*it3).get_nume()));
                    it3++;
                }
            default:
                break;
        }
    }
    void conectare()
    {
        QObject::connect(pb_add,&QPushButton::clicked,[&]()
        {
           produs nou=produs(le_nume->text().toStdString(),
                             cb_categorie->currentText().toStdString(),
                             sb_pret->value(),
                             le_descriere->text().toStdString());
           if(nou.get_nume().empty())
           {
               QMessageBox msg;
               msg.setText("Numele nu poate fi vid!");
               msg.addButton(QMessageBox::Ok);
               msg.addButton(QMessageBox::Yes);
               msg.addButton(QMessageBox::Close);
               msg.addButton(QMessageBox::Cancel);
               msg.addButton(QMessageBox::No);
               msg.addButton(QMessageBox::Abort);

               msg.exec();
               return;
           }
           /*if(arb.cauta(nou)!=nullptr)
            {
               QMessageBox msg;
               msg.setText("Un produs cu acelasi nume exista deja!");
               msg.addButton(QMessageBox::Ok);
               msg.exec();
               return;
            }
           else*/
               arb.push(nou);
            populate_list(MOD_SRD);
        });
        QObject::connect(pb_cauta,&QPushButton::clicked,[&]()
        {

            string nume=le_nume->text().toStdString();
            auto p=arb.cauta(produs(nume,"",0,""));
            if(p==nullptr)
            {
                QMessageBox msg;
                msg.setText("Produsul nu exista!");
                msg.addButton(QMessageBox::Ok);
                msg.exec();
                return;
            }
            else
            {
                QMessageBox msg;
                msg.setText("Produsul exista!");
                msg.addButton(QMessageBox::Ok);
                msg.exec();
                return;
            }
        });
        QObject::connect(lista,&QListWidget::doubleClicked,[&]()
        {

            string nume=lista->currentItem()->text().toStdString();
            auto p=arb.cauta(produs(nume,"",0,""));
            if(p!=nullptr)
            {
                QMessageBox msg;
                QString text;
                msg.setWindowTitle("Informatii produs");
                text.append("Nume: ");
                text.append(QString::fromStdString(p->get_data().get_nume()));
                text.append('\n');
                text.append("Categorie: ");
                text.append(QString::fromStdString(p->get_data().get_categorie()));
                text.append('\n');
                text.append("Pret: ");
                text.append(QString::number(p->get_data().get_pret()));
                text.append('\n');
                text.append("Descriere: ");
                text.append(QString::fromStdString(p->get_data().get_descriere()));
                text.append('\n');
                msg.setText(text);
                msg.addButton(QMessageBox::Close);
                msg.exec();
                return;
            }
        });
        QObject::connect(lista,&QListWidget::clicked,[&]()
        {
            string nume=lista->currentItem()->text().toStdString();
            auto p=arb.cauta(produs(nume,"",0,""));
            if(p!=nullptr)
            {
                le_nume->setText(QString::fromStdString(p->get_data().get_nume()));
                le_descriere->setText(QString::fromStdString(p->get_data().get_descriere()));
                cb_categorie->setCurrentText(QString::fromStdString(p->get_data().get_categorie()));
                sb_pret->setValue((p->get_data().get_pret()));
            }
        });
        QObject::connect(pb_delete,&QPushButton::clicked,[&]()
        {
            string nume=le_nume->text().toStdString();
            arb.sterge(produs(nume,"",0,""));
            populate_list(MOD_SRD);
        });
        QObject::connect(pb_RSD,&QPushButton::clicked,[&]()
        {
            populate_list(MOD_RSD);
        });
        QObject::connect(pb_SRD,&QPushButton::clicked,[&]()
        {
            populate_list(MOD_SRD);
        });
        QObject::connect(pb_SDR,&QPushButton::clicked,[&]()
        {
            populate_list(MOD_SDR);
        });
        QObject::connect(pb_clean,&QPushButton::clicked,[&]()
        {
            le_descriere->clear();
            le_nume->clear();
            sb_pret->setValue(0);
        });
    }
public:
     SDA_GUI()
     {
        conectare();

        sb_pret->setMaximum(1000.0);
        cb_categorie->addItem("Carti");
        cb_categorie->addItem("Manuscrise");
        cb_categorie->addItem("Ziare");
        cb_categorie->addItem("Muzica");
        cb_categorie->addItem("Picturi");
        cb_categorie->addItem("Altele");

        this->setLayout(main_layout);
        main_layout->addLayout(left_layout);
        main_layout->addLayout(right_layout);
        left_layout->addWidget(lista);
        left_layout->addLayout(lef_under_layout);
        lef_under_layout->addWidget(pb_RSD);
        lef_under_layout->addWidget(pb_SRD);
        lef_under_layout->addWidget(pb_SDR);
        right_layout->addLayout(r1);
        right_layout->addLayout(r2);
        right_layout->addLayout(r3);
        right_layout->addLayout(r4);
        r1->addWidget(l_nume);
        r1->addWidget(le_nume);
        r2->addWidget(l_categorie);
        r2->addWidget(cb_categorie);
        r3->addWidget(l_pret);
        r3->addWidget(sb_pret);
        r4->addWidget(l_descriere);
        r4->addWidget(le_descriere);
        right_layout->addWidget(pb_add);
        right_layout->addWidget(pb_cauta);
        right_layout->addWidget(pb_delete);
        right_layout->addWidget(pb_clean);

        arb.push(produs("Hans Eckart Schlandt la orga Bisericii Negre din Brasov I 1","Muzica",12,"ELECTRECORD ST-ECE 01042, VG++/VG+. Lucrari de Bach, Bruhns, Pachelbel, Buxtehude"));
        arb.push(produs("Hans Eckart Schlandt la orga Bisericii Negre din Brasov II","Muzica",5,"ELECTRECORD ST-ECE 01271, VG+/VG+. Lucrari de JS Bach"));
        arb.push(produs("Hans Eckart Schlandt la orga Bisericii Negre din Brasov I 2","Muzica",10,"ELECTRECORD ST-ECE 01042, G/G. Lucrari de Bach, Bruhns, Pachelbel, Buxtehude"));
        arb.push(produs("Horst Gehann - Recital de orga (Bach, Buxtehude)","Muzica",10,"ELECTRECORD STM-ECE 0555, VG++/VG++. Lucrari de Bach si Buxtehude"));
        arb.push(produs("Horst Gehann - Muzica de orga de compozitori transilvaneni din sec. XVI-XVIII","Muzica",5,"ELECTRECORD STM-ECE 0560, VG++/VG++. Lucrari de Bakfark, Croner si Anonymus"));
        arb.push(produs("Horst Gehann - Recital de orga (Bach, Pachelbel)","Muzica",15,"ELECTRECORD ECD 1055, Generic/G+. FOARTE RAR. Lucrari de Bach si Pachelbel"));
        arb.push(produs("Ilse Maria Reich - Recital de orga","Muzica",10,"ELECTRECORD ST-ECE 02896, VG++/VG++. Lucrari de Bach, Bruhns, Sweelink si Buxtehude"));
        arb.push(produs("Istvan David - Recital de orga","Muzica",5,"ELECTRECORD ST-ECE 03107, VG++/VG++. Lucrari de Bruhns, Zipoli, Bohm, Pachelbel, Bach"));
        arb.push(produs("Joachim Grubich - Recital de orga","Muzica",10,"ELECTRECORD ECE 0275, G/G. RAR. Lucrari de Bach, Franck, Brahms, Messiaen"));
        arb.push(produs("Helmut Plattner - Recital de orga","Muzica",5,"ELECTRECORD ECD 28, VG+/G. FOARTE RAR. Lucrari de Bach, Frank"));
        arb.push(produs("JS Bach - Preludiu si fuga in mi minor, Helmut Plattner - orga","Muzica",5,"ELECTRECORD ECC 803, Discoteca pentru toti nr 29.FOARTE RAR. VG++/G."));
        arb.push(produs("Franz Xaver Dressler - Recital de orga","Muzica",20,"ELECTRECORD STM-ECE 0705, VG+/G+. Lucrari de Reger, Brahms, Frank"));
        arb.push(produs("Helmut Plattner, Horst Gehann - Recital de orga","Muzica",12,"ELECTRECORD ECE 1009, VG+/G. Lucrari de Bach, Frank, Pachelbel. Reeditare a discurilor ECD 28 si ECD 1055"));
        arb.push(produs("Franz Liszt. Matei Kozma - Orga","Muzica",15,"ELECTRECORD ST-ECE 01984, VG++/VG++."));
        populate_list(MOD_SRD);
     }
    ~SDA_GUI()
     {
         ;
     }
};
class QW:public QWidget
{

};
#endif // WIDGET_H
