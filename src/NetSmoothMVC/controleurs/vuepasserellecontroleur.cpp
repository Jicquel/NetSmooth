#include "vuepasserellecontroleur.h"

VuePasserelleControleur::VuePasserelleControleur(VuePasserelle* vue0, VueEntiteeControleur *parent) : VueEntiteeControleur(vue0,parent)
{
	vue = vue0;

    connect(vue,SIGNAL(doubleClick()),this,SLOT(actionDoubleClick()));

}


void VuePasserelleControleur::actionDoubleClick()
{
    vue->terminal();
}
