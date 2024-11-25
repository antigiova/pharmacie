#ifndef MON_FICHIER_H
#define MON_FICHIER_H

#define TAILLE_MAX 100
type def struc utilisateur utilisateur;
struct utilisateur
{
    char nom[100];
    char prenom[100];
    int id;
    char MotDePasse[100];
};

int ajouterUtilisateur(const Utilisateur* utilisateur);
int modifierUtilisateur(int id, const Utilisateur* utilisateur);
int supprimerUtilisateur(int id);
void afficherUtilisateurs(void);


#endif
