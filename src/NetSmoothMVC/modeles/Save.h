#ifndef SAVE_DEF
#define SAVE_DEF

#include <iostream>
#include <vector>
#include <QObject>
#include <fstream>
#include <string>
#include <iostream>
#include <cstdio>
#include <stdlib.h>

class Save;

#include "modeles/Entitee.h"
#include "vues/vueprincipale.h"
#include "controleurs/VueCableControleur.h"

class Save
{
        public:
                static void save_session(std::string fileName);
                static void load_session(std::string fileName);

        private:
};

#endif

