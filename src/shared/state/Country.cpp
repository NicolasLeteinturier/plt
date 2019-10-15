#include <string>
#include <vector>
#include <Country.h>




//-----------------------------------//
/*declaration des variables publiques*/
//-----------------------------------//

public std::string id;
public std::vector <std::shared_ptr<Unit>> listUnit;
public std::vector<std::shared_ptr<Country>> neighboor;
public std::shared_ptr<Player> owner;




using namespace state;

Country::Country()
{
}

int FindTypeNumber(Type type){
   unsigned int n= listUnit.size;
   if (n==0){
      printf("there must be at least one unit on this country");
      return 0;}
   int output;
   for (unsigned int i = 0; i<n,i++){
      if(listUnit[i].type == type){
        output +=1;
      }
   }
   return output;}


void AddUnit (std::shared_ptr<Unit> unit){
   listUnit.push_back(unit);
   return;
   }


void DeleteUnit (std::shared_ptr<Unit> unit){
   unsigned int n= listUnit.size;
   if (n==1){ 
      printf("there must be at least one unit on this country you can't delete");
      return;}
   for (unsigned int i = 0; i<n,i++){
      if(listUnit[i] == unit){
          listUnit.earse(listUnit.begin()+i);
      }
   }
   return
}


void AddNeighboor (std::shared_ptr<Country> newNeighboor){
   unsigned int n= neighboor.size;
   int enable=0;
   for (unsigned int i = 0; i<n,i++){
      if(neighboor[i]==newNeighboor){
         enable=1;
      }
   }
   if (enable==0){
   neighboor.push_back(newNeighboor);}

   return;}
   




std::vector<std::shared_ptr<Country>> GetEnemiesCountry (){
   std::shared_ptr<Player> myPlayer = owner;
   std::vector<std::shared_ptr<Country>> output;
   unsigned int n= neighboor.size;
   for (unsigned int i = 0; i<n,i++){
      if (neighboor[i].owner != myPlayer){
         output.push_back(neighboor[i]);
      }
   }
   return;
}
      









