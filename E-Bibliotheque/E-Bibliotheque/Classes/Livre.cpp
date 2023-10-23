//
//  Livre.cpp
//  E-Bibliotheque
//
//  Created by Fabio Tavares Marques  on 19/10/2023.
//

#include "Livre.hpp"

std::string Livre::getTitre() const{ return this->titre;}
std::string Livre::getAuteur() const{ return this->auteur;}
int Livre::getAnnee() const{ return this->annee;}

