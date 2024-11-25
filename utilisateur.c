#include <stdio.h>
#include <string.h>
#include "utilisateur.h"

// Fonction pour ajouter un utilisateur
int ajouterUtilisateur(const Utilisateur* utilisateur) {
    FILE *fichier = fopen("utilisateurs.txt", "a"); // Ouvre le fichier en mode ajout
    if (fichier == NULL) {
        printf("Erreur d'ouverture du fichier pour ajouter un utilisateur.\n");
        return -1;
    }

    // Ajoute un nouvel utilisateur dans le fichier
    fprintf(fichier, "%d;%s;%s;%s\n", utilisateur->id, utilisateur->nom, utilisateur->prenom, utilisateur->MotDePasse);

    fclose(fichier);
    return 0;
}

// Fonction pour modifier un utilisateur
int modifierUtilisateur(int id, const Utilisateur* utilisateur) {
    FILE *fichier = fopen("utilisateurs.txt", "r+");
    if (fichier == NULL) {
        printf("Erreur d'ouverture du fichier pour modifier un utilisateur.\n");
        return -1;
    }

    char ligne[200];
    int found = 0;
    while (fgets(ligne, sizeof(ligne), fichier)) {
        int fichierId;
        sscanf(ligne, "%d;%*s;%*s;%*s", &fichierId);  // Récupère l'ID depuis la ligne
        if (fichierId == id) {
            fseek(fichier, -strlen(ligne), SEEK_CUR);  // Déplace le curseur au début de la ligne à modifier
            fprintf(fichier, "%d;%s;%s;%s\n", utilisateur->id, utilisateur->nom, utilisateur->prenom, utilisateur->MotDePasse);
            found = 1;
            break;
        }
    }

    fclose(fichier);
    return found ? 0 : -1; // Retourne -1 si l'utilisateur n'a pas été trouvé
}

// Fonction pour supprimer un utilisateur
int supprimerUtilisateur(int id) {
    FILE *fichier = fopen("utilisateurs.txt", "r");
    FILE *temp = fopen("temp.txt", "w");  // Fichier temporaire pour les utilisateurs restants
    if (fichier == NULL || temp == NULL) {
        printf("Erreur lors de l'ouverture des fichiers.\n");
        return -1;
    }

    char ligne[200];
    int found = 0;
    while (fgets(ligne, sizeof(ligne), fichier)) {
        int fichierId;
        sscanf(ligne, "%d;%*s;%*s;%*s", &fichierId);
        if (fichierId != id) {
            fputs(ligne, temp);  // Copie la ligne dans le fichier temporaire
        } else {
            found = 1;
        }
    }

    fclose(fichier);
    fclose(temp);

    // Remplace l'ancien fichier par le nouveau sans l'utilisateur supprimé
    remove("utilisateurs.txt");
    rename("temp.txt", "utilisateurs.txt");

    return found ? 0 : -1; // Retourne -1 si l'utilisateur n'a pas été trouvé
}

// Fonction pour afficher tous les utilisateurs
void afficherUtilisateurs(void) {
    FILE *fichier = fopen("utilisateurs.txt", "r");
    if (fichier == NULL) {
        printf("Erreur d'ouverture du fichier.\n");
        return;
    }

    char ligne[200];
    while (fgets(ligne, sizeof(ligne), fichier)) {
        int id;
        char nom[50], prenom[50], email[100];
        sscanf(ligne, "%d;%49[^;];%49[^;];%99[^\n]", &id, nom, prenom, email);
        printf("ID: %d, Nom: %s, Prénom: %s, Email: %s\n", id, nom, prenom, email);
    }

    fclose(fichier);
}
