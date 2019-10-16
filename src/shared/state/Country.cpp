#include "Country.h"

using namespace state;

Country::Country()
{
}

int Country::FindTypeNumber(Type type){
   unsigned int n = listUnit.size();
   if (n == 0){
      printf("there must be at least one unit on this country");
      return 0;}
   unsigned int output = 0;
   for (unsigned int i = 0; i < n; i++){
      if(listUnit[i]->type == type){
        output++;
      }
   }
   return output;}


void Country::AddUnit (std::shared_ptr<Unit> unit){
   listUnit.push_back(unit);
   return;
   }


void Country::DeleteUnit (std::shared_ptr<Unit> unit){
   unsigned int n= listUnit.size();
   if (n==1){ 
      printf("there must be at least one unit on this country you can't delete");
      return;}
   for (unsigned int i = 0; i < n; i++){
      if(listUnit[i] == unit){
          listUnit.erase(listUnit.begin()+i);
      }
   }
   return;
}


void Country::AddNeighboor (std::shared_ptr<Country> newNeighboor){
   unsigned int n= neighboor.size();
   int enable=0;
   for (unsigned int i = 0; i < n; i++){
      if(neighboor[i]==newNeighboor){
         enable=1;
      }
   }
   if (enable==0){
   neighboor.push_back(newNeighboor);}

   return;}
   




std::vector<std::shared_ptr<Country>> Country::GetEnemiesCountry (){
   std::shared_ptr<Player> myPlayer = owner;
   std::vector<std::shared_ptr<Country>> output;
   unsigned int n= neighboor.size();
   for (unsigned int i = 0; i < n; i++){
      if (neighboor[i]->owner != myPlayer){
         output.push_back(neighboor[i]);
      }
   }
   return(output);
}
      









