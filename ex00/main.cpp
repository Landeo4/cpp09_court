#include "BitcoinExchange.hpp"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "Error: wrong number of argument, please 1 file" << std::endl;
        return 1;
    }
    std::string verif = argv[1];
    if (verif.find(".txt") == std::string::npos)
    {
        std::cout << "wrong file passed in argument" << std::endl;
        return 1;
    }
    BitcoinExchange obj;
    if (obj.check_file(argv) == 1)
        return 1;
    return 0;
}

// cree un programme qui renvoie la valeur d'un certain nombre de bitcoin d'une certaine date

// ce programme doit utilise une database en csv qui va represente le prix du bitcoin
// dans le temps. cette base de donne est donnee dans le sujet

// le programe doit prendre en parametre une seconde base de donnee, stocker les differents prix/date

// le programme doit respecter ces regles:

// le nom du programme est btc
// votre programme doit prendre en argument un fichier
// chaque ligne dans le fichier doit suivre le format "date | valeur"
// une date valide sera toujours dans le format "ANNEE-MOIS-JOUR"
// une valeur valide sera sois un float ou un int positif, entre 0 et 1000

//gerer les erreurs avec un message approprie

// votre programme doit afficher sur la sortie standard le result de la valeur multiplie
// par le taux d'echange a la date indique dans ta base de donnee
