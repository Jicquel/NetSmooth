#include "Save.h"

using namespace std;


void Save::load_session(string fileName)
{
    struct assoCable
    {
        string id;
        VueEntitee* vue;
    };

    struct assoCable asso[100];

    ifstream fichier(fileName.c_str(), ios::in);
    if(!fichier)
        return;

    VuePrincipale* vp=VuePrincipale::getInstanceOf();

    string line;
    int i=0;
    getline(fichier, line);
    if(line=="{")
        while(getline(fichier, line) && line!="}")
        {
            int type, posx, posy, id;
            string type_str;
            Entitee* e;
            if(line=="(")
            {
                getline(fichier, line); //type
                type_str=line;
                type=strtol(line.c_str(), NULL, 10);
                getline(fichier, line); //posx
                posx=strtol(line.c_str(), NULL, 10);
                getline(fichier, line); //posy
                posy=strtol(line.c_str(), NULL, 10);

                VueEntitee* v=(vp->ajoutEntitee(posx, posy, type));
                e=v->getModele();    /*renvoie le modele de l'objet cree*/

                getline(fichier, line); //id
                id=strtol(line.c_str(), NULL, 10);

                asso[i].id=type_str+line;
                asso[i].vue=v;

                e->setID(id);

                getline(fichier, line); //nom
                e->setNom(line);


                getline(fichier, line);

                while(line=="\\")   /*ips*/
                {
                    struct paramIp* ip = new paramIp;
                    getline(fichier, line);     /*interface*/
                    ip->interface=line;
                    getline(fichier, line);     /*ipv4*/
                    ip->ipv4=line;
                    getline(fichier, line);     /*mask4*/
                    ip->maskv4=line;
                    getline(fichier, line);     /*ipv6*/
                    ip->ipv6=line;
                    ((Machine*)e)->setIpConfig(ip);

                    getline(fichier, line);     /*\*/
                    getline(fichier, line);
                }
                while(line=="[4") /*route4*/
                {
                    struct paramRoutage* r = new paramRoutage;
                    getline(fichier, line);     /*interface*/
                    r->interface=line;
                    getline(fichier, line);     /*destination*/
                    r->destination=line;
                    getline(fichier, line);     /*passerelle*/
                    r->passerelle=line;
                    getline(fichier, line);     /*id*/
                    id=strtol(line.c_str(), NULL, 10);
                    r->id=id;
                    ((Machine*)e)->addRouteConfig4(*r);

                    getline(fichier, line);     /*]*/
                    getline(fichier, line);
                }
                while(line=="[6")   /*route6*/
                {
                    struct paramRoutage* r = new paramRoutage;
                    getline(fichier, line);     /*interface*/
                    r->interface=line;
                    getline(fichier, line);     /*destination*/
                    r->destination=line;
                    getline(fichier, line);     /*passerelle*/
                    r->passerelle=line;
                    getline(fichier, line);     /*id*/
                    id=strtol(line.c_str(), NULL, 10);
                    r->id=id;
                    ((Machine*)e)->addRouteConfig6(*r);

                    getline(fichier, line);     /*]*/
                    getline(fichier, line);
                }
            }
            i++;
        }
    getline(fichier, line);     /*}*/
    while(line=="<")
    {
        string type_str, id1, id2;
        getline(fichier, line);     /*type1*/
        type_str=line;
        getline(fichier, line);     /*ID1*/
        id1=type_str+line;

        getline(fichier, line);     /*type2*/
        type_str=line;
        getline(fichier, line);     /*ID2*/
        id2=type_str+line;

        int i;
        bool first=true;
        for(i=0 ; i<100 ;i++)
        {
            if(asso[i].id==id1 || asso[i].id==id2)
            {
                if(first)
                {
                    first=false;
                    VueCable::setPremiereSelection(asso[i].vue);
                }
                else
                {
                        bool test0=VueCable::getPremiereSelection()->getModele()->getType()==TYPE_HUB;
                        bool test1=asso[i].vue->getModele()->getType()==TYPE_HUB;
                        if(test0 && !test1 || !test0 && test1)
                                new VueCableControleur(new VueCable(
                                                               (test0)?((VueHub*)VueCable::getPremiereSelection()):((VueHub*)asso[i].vue),
                                                               (test0)?(VueMachine*)(asso[i].vue):(VueMachine*)(VueCable::getPremiereSelection())
                                                       ));
                }
            }
        }
        getline(fichier, line);     /*>*/
        getline(fichier, line);
    }
    fichier.close();
}

void Save::save_session(string fileName)
{
        ElementListeChainee* ent;
        int i, j, k;
        bool ok;
        ofstream fichier(fileName.c_str(), ios::out|ios::trunc);
        if(!fichier)
        {
                cout << "marche po" << endl;
                return;
        }
        cout << "marche" << endl;
        vector<Cable*> cables;

        fichier << "{" << endl;

        for(i=0 ; i<3 ; i++)
        {
                ent=new ElementListeChainee;
                if(i==0)
                        ent->nextElement=DataBase::getListPasserelle();
                if(i==1)
                        ent->nextElement=DataBase::getListOrdinateur();
                if(i==2)
                        ent->nextElement=DataBase::getListHub();

                while(ent->nextElement!=NULL)
                {
                        fichier << "(" << endl;
                        ent=ent->nextElement;

                        Entitee* e=ent->entitee;

                        vector<Cable*> *cab=e->getCables();

                        for(j=0 ; j<(int)cab->size() ; j++)
                        {
                                ok=true;
                                for(k=0 ; k<(int)cables.size() ; k++)
                                        if((*cab)[j]==cables[k])
                                                ok=false;

                                if(ok==true)
                                        cables.push_back((*cab)[j]);
                        }
                        VuePrincipale* vp=VuePrincipale::getInstanceOf();

                        fichier << e->getType() << endl;
                        fichier << e->getVue()->getColGrille()*vp->getHauteurCaseEntiere() << endl;
                        fichier << e->getVue()->getLigneGrille()*vp->getLargeurCaseEntiere() << endl;
                        fichier << e->getID() << endl;
                        fichier << e->getNom() << endl;
                        if(e->getType()!=TYPE_HUB)
                        {
                                vector<paramIp*> ips=e->getIpConfig();
                                for(j=0 ; j<(int)ips.size() ; j++)
                                {
                                        if(ips[j]->ipv4!="" || ips[j]->maskv4!="" || ips[j]->ipv6!="")
                                        {
                                                fichier << "\\" << endl;
                                                fichier << ips[j]->interface << endl;
                                                fichier << ips[j]->ipv4 << endl;
                                                fichier << ips[j]->maskv4 << endl;
                                                fichier << ips[j]->ipv6 << endl;
                                                fichier << "/" << endl;
                                        }
                                }
                                vector<paramRoutage> r4=((Machine*)e)->getRouteConfig4();
                                for(j=0 ; j<(int)r4.size() ; j++)
                                {
                                        fichier << "[4" << endl;
                                        fichier << r4[j].interface << endl;
                                        fichier << r4[j].destination << endl;
                                        fichier << r4[j].passerelle << endl;
                                        fichier << r4[j].id << endl;
                                        fichier << "]4" << endl;
                                }
                                vector<paramRoutage> r6=((Machine*)e)->getRouteConfig6();
                                for(j=0 ; j<(int)r6.size() ; j++)
                                {
                                        fichier << "[6" << endl;
                                        fichier << r6[j].interface << endl;
                                        fichier << r6[j].destination << endl;
                                        fichier << r6[j].passerelle << endl;
                                        fichier << r6[j].id << endl;
                                        fichier << "]6" << endl;
                                }
                        }

                        fichier << ")" << endl;
                }
        }
        fichier << "}" << endl;

        for(i=0 ; i<(int)cables.size() ; i++)
        {
                Cable* c=cables[i];
                fichier << "<" << endl;
                fichier << c->getHub()->getType() << endl;
                fichier << c->getHub()->getID() << endl;
                fichier << c->getMachine()->getType() << endl;
                fichier << c->getMachine()->getID() << endl;
                fichier << ">" << endl;
        }
        fichier.close();
}
