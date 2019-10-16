#include "Player.h"
#include <math.h>

int numberOfCountrys = 17;

using namespace state;

Player::Player()
{
}


/*std::vector<Country> Player::GetCountryList (){

   //la fonction parcoure listeCountry et ajoute dans un vecteru les territoires du joueur en question
   std::vector<Country> output[numberOfCountrys];
   int j=0;
   for (int i = 0; i < numberOfCountrys; ++i){//psoeudo code je ne sais pas comment appeller owner et le shared pointer de player
      if (listCountry[i]->owner== *Player){
         output[j]=listeCountry[i];
         j+=1;}
      }
   return ouput;
}*/


int Player::ReinforcementNumber(){
   int nbrCountrys= Player::listOwnedCountry.size();
   return floor(nbrCountrys/2);}


void Player::AddOwnedCountry(std::shared_ptr<Country> country){
   unsigned int n = listOwnedCountry.size();
   int enable=1;
   /*for (unsigned int i = 0; i < n; i++){
      if(listOwnedCountry[i]==country){
         enable=0;
      }
   }*/
   if (enable==1){
      std::shared_ptr<Player> ennemy = country->owner;//shared pointer player
      n=ennemy->listOwnedCountry.size();
      for (unsigned int i = 0; i < n; i++){
         if(listOwnedCountry[i] == country){
            ennemy->listOwnedCountry.erase(ennemy->listOwnedCountry.begin()+i);
         }
      }
      listOwnedCountry.push_back(country);
   } 

return;}


/*void DeleteOwnedCountry (std::shared_ptr<Country> country){
   printf("fonction inutille");
   return;}*/



