#include <string>
using namespace std;


bool 
validerFormatNom(const string& p_nom)
{
    // Vérifie si le premier caractère est une lettre
    if (isalpha(p_nom[0]))
    {
        int i = 1;
        // Parcourt les caractères suivants
        while (i < p_nom.length())
        {
            // Vérifie si le caractère est une lettre
            if (isalpha(p_nom[i]))
            {
                // Vérifie si c'est le dernier caractère du nom
                if (i == p_nom.length() - 1)
                {
                    // Le format du nom est valide
                    return true;
                }
                else
                {
                    // Passe au caractère suivant
                    i++;
                }
            }
            // Vérifie si le caractère est un tiret (-) ou un espace
            else if (p_nom[i] == '-' || p_nom[i] == ' ')
            {
                if (i < p_nom.length() - 1)
                {
                    // Vérifie si le caractère suivant est également un tiret ou un espace
                    if (p_nom[i + 1] == '-' || p_nom[i + 1] == ' ')
                    {
                        // Deux tirets ou espaces consécutifs ne sont pas autorisés
                        return false;
                    }
                    else
                    {
                        // Passe au caractère suivant
                        i++;
                    }
                }
                else
                {
                    // Le dernier caractère ne peut pas être un tiret ou un espace
                    return false;
                }
            }
            else
            {
                // Caractère invalide dans le nom
                return false;
            }
        }
    }
    // Le premier caractère n'est pas une lettre, le format du nom est invalide
    return false;
}


bool
validerCodeIssn (const string & p_issn)
{
  // Vérification du format ISSN
  // ISSN 1234-5678
  // 01234567891111
  if (p_issn.substr (0, 5) != "ISSN " || p_issn.length () != 14)
    {
      return false;
    }

  // Vérification des séparateurs
  if (p_issn[9] != '-' )
    {
      return false;
    }

  // Vérification des chiffres partie 1
  for (int i = 5; i < 9; i++)
    {
      if (!isdigit (p_issn[i]))
        {
          return false;
        }
    }
  // Vérification des chiffres partie 2
  for (int i = 10; i < 14; i++)
    {
      if (!isdigit (p_issn[i]))
        {
          return false;
        }
    }

  // Calcul de la clé
  int somme = 0;
  for (int i = 0; i < 4; i++)
    {
      somme += (p_issn[i + 5] - '0') * (8 - i);
    }

  for (int i = 4; i < 7; i++)
    {
      somme += (p_issn[i + 6] - '0') * (8 - i);
    }

  int cle = (11 - (somme % 11)) % 11;

  // Vérification de la clé
  if (cle != (p_issn[13] == 'X' ? 10 : p_issn[13] - '0'))
    {
      return false;
    }

  return true;
}


bool
validerCodeIsbn (const string & p_isbn)
{
  // Vérifier la longueur de l'ISBN
  // ISBN 978-2-7605-5379-8
  // 0123456789ABCDEF678921
  if (p_isbn.length () != 22)
    {
      return false;  // Longueur invalide
    }

  // Vérifier le préfixe de l'ISBN
  if (p_isbn.substr (0, 5) != "ISBN ")
    {
      return false;  // Préfixe invalide
    }
  // verifier la position du "-"
  if (p_isbn[8] != '-' )
    {
      return false;
    }
  // Vérifier les 3 premier chiffre
  if (!(p_isbn.substr (5, 3) == "978" || p_isbn.substr (5, 3) == "979"))
    {
      return false;  // Préfixe invalide
    }
  // Vérifier domaine
  int index = 9;
  string domaineStr;
  while (p_isbn[index] != '-')
    {
      if (!isdigit (p_isbn[index]) || index > 14)
        {
          return false;
        }
      domaineStr.push_back (p_isbn[index]);
      index++;
    }
  if (domaineStr.length () == 0)
    {
      return false;
    }
  int domaine;
  domaine = stoi (domaineStr);
  if (domaine < 0 || domaine == 6 || domaine > 7 && domaine < 80 || domaine > 94 && domaine < 600 || domaine > 649 && domaine < 950
      || domaine > 989 && domaine < 9900 || domaine > 9989 && domaine < 99900 || domaine > 99999)
    {
      return false;
    }

  // Supprimer les caractères non-chiffres et extraire les chiffres de l'ISBN
  std::string chiffresUniquement = "";
  for (char ch : p_isbn)
    {
      if (isdigit (ch))
        {
          chiffresUniquement += ch;
        }
    }

  // Vérifier le nombre de chiffres
  if (chiffresUniquement.length () != 13)
    {
      return false;  // Nombre de chiffres invalide
    }

  // Extraire le dernier chiffre (clé) de l'ISBN
  int cle = chiffresUniquement.back () - '0';

  // Calculer la somme de contrôle en utilisant l'algorithme spécifique à l'ISBN-13
  int sommeControle = 0;
  int multiplicateur = 1;
  for (int i = 0; i < chiffresUniquement.length () - 1; i++)
    {
      int chiffre = chiffresUniquement[i] - '0';
      sommeControle += chiffre * multiplicateur;
      multiplicateur = (multiplicateur == 1) ? 3 : 1;
    }

  // Valider la somme de contrôle
  if ((10 - (sommeControle % 10)) % 10 != cle)
    {
      return false;  // ISBN invalide
    }

  return true;  // ISBN valide
}