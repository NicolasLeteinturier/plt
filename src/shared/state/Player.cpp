#include <string>
#include <vector>
#include <Player.h>



int numberOfCountrys = 17;


using namespace state;

Player:layer()
{
}


std::vector<Country> Player::GetCountryList (){

   /*la fonction parcoure listeCountry et ajoute dans un vecteru les territoires du joueur en question*/
   std::vector<Country> output[numberOfCountrys];
   int j=0;
   for (int i = 0; i < numberOfCountrys; ++i){//psoeudo code je ne sais pas comment appeller owner et le shared pointer de player
      if (listeCountry[i].owner== *Player){
         output[j]=listeCountry[i];
         j+=1;}
      }
   return ouput;
}


int Player::ReinforcementNumbre(){//est ce qu'il ne faudrait pas en entrée l'id du joueur ??
   int nbrCountrys= Player::GetCountryList().size //je ne sais pas si j'ai le droit dappler comme ca une fonction de la meme classe
   return floor(nbrCountrys/2);}




