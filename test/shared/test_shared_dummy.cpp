
#include <boost/test/unit_test.hpp>

//#include "../../src/shared/state/Exemple.h"

#include "../../src/shared/state.h"

using namespace state;

BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
  BOOST_CHECK(1);
}

/*BOOST_AUTO_TEST_CASE(TestExemple)
{
  {
    Exemple ex {};
    BOOST_CHECK_EQUAL(ex.x, 0);
    ex.setX(21);
    BOOST_CHECK_EQUAL(ex.x, 21);
  }

  {
    Exemple ex {};
    ex.setX(21);
    BOOST_CHECK_LE(ex.x, 32); // Less than equal
    BOOST_CHECK_GT(ex.x, 11); // Greater than equl
  }
}*/

BOOST_AUTO_TEST_CASE(TestGamestate)
{
   GameState etat;

   // Generation des joueurs
   const auto joueur1 = std::make_shared<Player>();
//   std::shared_ptr<Player> joueur1 = new Player {};
   joueur1->id = "joueur1";
   auto joueur2 = std::make_shared<Player>();
   //std::shared_ptr<Player> joueur2;
   joueur1->id = "joueur2";

   // Generation des pays
   std::shared_ptr<Country> pays1;
   pays1->owner = joueur1;
   std::shared_ptr<Unit> unit1;
   pays1->AddUnit(unit1);

   std::shared_ptr<Country> pays2;
   pays2->owner = joueur2;
   std::shared_ptr<Unit> unit2;
   pays2->AddUnit(unit2);

   pays1->AddNeighboor(pays2);
   pays2->AddNeighboor(pays1);

   // Ajout des pays à l'état de jeu
   etat.AddCountry(pays1);
   etat.AddCountry(pays2);

}

/* vim: set sw=2 sts=2 et : */
