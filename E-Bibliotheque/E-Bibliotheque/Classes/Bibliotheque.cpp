//
//  Bibliotheque.cpp
//  E-Bibliotheque
//
//  Created by Fabio Tavares Marques  on 19/10/2023.
//

#include "Bibliotheque.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>



Bibliotheque::Bibliotheque() {
    chargerBibliotheque();
}

void Bibliotheque::App(){
    
    std::cout << "BIENVENUE DANS E-BIBLIOTHEQUE" << std::endl;
    Bibliotheque biblio;
    biblio.Menu();
}


void Bibliotheque::Menu() {
    int fermer = 0;
    while(fermer == 0){
        enum MenuOption {
            AFFICHER_LIVRES = 1,
            RECHERCHER_LIVRE,
            AJOUTER_LIVRE,
            SUPPRIMER_LIVRE,
            QUITTER
        };

        std::cout << "\nAFFICHER LIVRES[1]  RECHERCHER LIVRE[2]   AJOUTER LIVRE[3]  SUPPRIMER LIVRE[4]  QUITTER[5]" << std::endl;
        std::cout << "Veuillez choisir une option en entrant un numéro : ";

        
        int choixInt;
        std::cin >> choixInt;
        
        std::cout << "\n";


        // Convertissez le choix de l'utilisateur en MenuOption
        MenuOption choix = static_cast<MenuOption>(choixInt);

        // Utilisez une instruction switch pour réagir au choix
        
        switch (choix) {
            case AFFICHER_LIVRES:
                afficherLivres();
                break;
                
            case RECHERCHER_LIVRE:
                rechercherLivre();
                break;
                
            case AJOUTER_LIVRE:
                ajouterLivre();
                break;
                
            case SUPPRIMER_LIVRE:
                supprimerLivre();
                break;
                
            case QUITTER:
                std::cout << "Au revoir !\n";
                fermer = 1;
                break;
                
            default:
                std::cout << "Choix invalide. Veuillez entrer un choix valide.\n";
        }
    }
    
}


void Bibliotheque::modifierEtat() {
    bool titreTrouve = false;
    
    std::fstream monFichier("/Users/tavares/Desktop/E-Bibliotheque/E-Bibliotheque/Classes/Bibliotheque.txt", std::ios::in | std::ios::out); // Ouvrir en mode lecture/écriture

    if (monFichier.is_open()) {
        std::string contenu;
        std::vector<Livre> livres;

        // Lire le contenu du fichier et stocker les livres dans un vecteur
        while (std::getline(monFichier, contenu)) {
            // Utilisez un flux de chaînes (stringstream) pour diviser la ligne par les virgules.
            std::stringstream ss(contenu);
            std::string titre, auteur, annee;

            // Utilisez getline pour extraire les parties de la ligne.
            std::getline(ss, titre, ',');
            std::getline(ss, auteur, ',');
            std::getline(ss, annee, ',');

            // Créez un objet Livre et mettez à jour son état.
            Livre livre(titre, auteur, std::stoi(annee));

            // Identifier et modifier le livre souhaité (par exemple, en utilisant le titre)
            if (titre == "Harry") {
                titreTrouve = true;
            }

            // Ajoutez le livre modifié au vecteur.
            livres.push_back(livre);
        }

        // Réécrire le contenu du fichier avec les livres mis à jour
        monFichier.clear();
        monFichier.seekp(0);

        for (const Livre& livre : livres) {
            monFichier << livre.getTitre() << ',' << livre.getAuteur() << ',' << livre.getAnnee() << std::endl;
        }

        monFichier.close();
    } else {
        std::cout << "Impossible d'ouvrir le fichier." << std::endl;
    }
}





void Bibliotheque::ajouterLivre() {
    std::string titre, auteur;
    int annee;

    std::cin.ignore(); // Ignorer les caractères restants dans le tampon d'entrée
    std::cout << "Entrez le titre du livre : ";
    std::getline(std::cin, titre);

    std::cout << "Entrez l'auteur du livre : ";
    std::getline(std::cin, auteur);

    std::cout << "Entrez l'année du livre : ";
    std::cin >> annee;

    Livre livre(titre, auteur, annee);

    livres.push_back(livre);
    sauvegarderBibliotheque();  // Mise à jour du fichier après l'ajout d'un livre.
    std::cout << "Livre ajouté à la bibliothèque : " << livre.getTitre() << std::endl;
}


void Bibliotheque::afficherLivres() {
    std::ifstream bibliotheque("/Users/tavares/Desktop/E-Bibliotheque/E-Bibliotheque/Classes/Bibliotheque.txt");
    std::string ligne;
    
    while (std::getline(bibliotheque, ligne)) {
                // Utilisez un flux de chaînes (stringstream) pour diviser la ligne par les virgules.
                std::stringstream ss(ligne);
                std::string titre, auteur, annee;

                // Utilisez getline pour extraire les parties de la ligne.
                std::getline(ss, titre, ',');
                std::getline(ss, auteur, ',');
                std::getline(ss, annee, ',');
    

                // Affichez l'année.
                std::cout << "===================== " << std::endl;
                std::cout << "Titre : " << titre << std::endl;
                std::cout << "Auteur : " << auteur << std::endl;
                std::cout << "Année : " << annee << std::endl;

            }
}

void Bibliotheque::rechercherLivre() {
    std::ifstream bibliotheque("/Users/tavares/Desktop/E-Bibliotheque/E-Bibliotheque/Classes/Bibliotheque.txt");
    std::string ligne;
    
    std::cin.ignore(); // Ignorer les caractères restants dans le tampon d'entrée
    std::cout << "Titre du Livre : ";
    std::string titreRecherche;
    std::getline(std::cin, titreRecherche); // Lire toute la ligne, y compris les espaces
    
    bool livreTrouve = false;

    while (std::getline(bibliotheque, ligne)) {
        std::stringstream ss(ligne);
        std::string titre, auteur, annee;

        std::getline(ss, titre, ',');
        std::getline(ss, auteur, ',');
        std::getline(ss, annee, ',');
        
        if (titre == titreRecherche) {
            std::cout << "\n=====================" << std::endl;
            std::cout << "Titre : " << titre << std::endl;
            std::cout << "Auteur : " << auteur << std::endl;
            std::cout << "Année : " << annee << std::endl;
            std::cout << "=====================\n" << std::endl;
            livreTrouve = true;
            break; // Arrêtez la recherche une fois que le livre est trouvé.
        }
    }

    if (!livreTrouve) {
        std::cout << "Livre non trouvé." << std::endl;
    }
}



void Bibliotheque::supprimerLivre() {
    std::ifstream bibliotheque("/Users/tavares/Desktop/E-Bibliotheque/E-Bibliotheque/Classes/Bibliotheque.txt");
    std::string AdresseTxt = "/Users/tavares/Desktop/E-Bibliotheque/E-Bibliotheque/Classes/Bibliotheque.txt";
    std::string AdresseTemp = "/Users/tavares/Desktop/E-Bibliotheque/E-Bibliotheque/Classes/AdresseTemp.txt";
    std::string ligne;
    std::string titreASupprimer;
    
    std::cin.ignore(); // Ignorer les caractères restants dans le tampon d'entrée
    std::cout << "Titre du Livre à supprimer : ";
    std::getline(std::cin, titreASupprimer); // Lire toute la ligne, y compris les espaces

    std::ofstream nouveauFichier(AdresseTemp, std::ios::out);

    while (std::getline(bibliotheque, ligne)) {
        std::stringstream ss(ligne);
        std::string titre, auteur, annee;
        std::getline(ss, titre, ',');
        std::getline(ss, auteur, ',');
        std::getline(ss, annee, ',');

        if (titre != titreASupprimer) {
            // Si le titre ne correspond pas, écrivez la ligne dans le nouveau fichier.
            nouveauFichier << ligne << "\n";
        }
    }

    bibliotheque.close();
    nouveauFichier.close();

    // Supprimer l'ancien fichier et renommer le nouveau fichier.
    remove(AdresseTxt.c_str());
    rename(AdresseTemp.c_str(), AdresseTxt.c_str());

    std::cout << "Livre supprimé avec succès !" << std::endl;
}

void Bibliotheque::sauvegarderBibliotheque() {
    std::fstream fichier("/Users/tavares/Desktop/E-Bibliotheque/E-Bibliotheque/Classes/Bibliotheque.txt", std::ios::out | std::ios::app);

    if (fichier.is_open()) {
        const Livre& dernierLivre = livres.back();  // Récupérez le dernier livre ajouté.
        
        fichier << dernierLivre.getTitre() << "," << dernierLivre.getAuteur() << "," << dernierLivre.getAnnee() << "\n";

        fichier.close();
        std::cout << "Livre sauvegardé avec succès." << std::endl;
    } else {
        std::cerr << "Erreur lors de la sauvegarde du livre." << std::endl;
    }
}


void Bibliotheque::chargerBibliotheque() {
    
}
