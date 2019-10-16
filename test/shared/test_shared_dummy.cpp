
#include <boost/test/unit_test.hpp>

//#include "../../src/shared/state/Exemple.h"

#include "../../src/shared/state.h"
#include "../../src/shared/state/Attack.h"

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
   joueur1->id = "joueur1";
   const auto joueur2 = std::make_shared<Player>();
   joueur2->id = "joueur2";
   const auto joueur3 = std::make_shared<Player>();
   joueur3->id = "joueur3";
   
   // Ajout des joueurs à l'état de jeu
   etat.AddPlayer(joueur1);
   etat.AddPlayer(joueur2);
   etat.AddPlayer(joueur3);

   // Effacement d'un joueur de l'état de jeu
   etat.DeletePlayer(joueur3);

   // Test du nombre de joueur dans l'état de jeu
   BOOST_CHECK_EQUAL(etat.listPlayer.size(), 2);
   // Test du nombre de pays dans l'état de jeu
   BOOST_CHECK_EQUAL(etat.listCountry.size(), 17);
}

BOOST_AUTO_TEST_CASE(TestCountry)
{
   // Creation de 2 joueurs
   const auto joueur1 = std::make_shared<Player>();
   const auto joueur2 = std::make_shared<Player>();

   // Creation des 2 pays et de leurs unités
   std::shared_ptr<Country> pays1 = std::make_shared<Country>();
   pays1->owner = joueur1;
   Type type = attaquant;
   std::shared_ptr<Unit> unit1 = std::make_shared<Unit>(type);
   std::shared_ptr<Unit> unit1p = std::make_shared<Unit>();
   pays1->AddUnit(unit1);
   pays1->AddUnit(unit1p);

   std::shared_ptr<Country> pays2 = std::make_shared<Country>();
   pays2->owner = joueur2;
   std::shared_ptr<Unit> unit2 = std::make_shared<Unit>(type);
   std::shared_ptr<Unit> unit2p = std::make_shared<Unit>();
   pays2->AddUnit(unit2);
   pays2->AddUnit(unit2p);

   // Les pays sont ajoutés comme voisins l'un de l'autre
   pays1->AddNeighboor(pays2);
   pays2->AddNeighboor(pays1);

   // Test de la fonction DeleteUnit, elle doit supprimer une unité
   pays1->DeleteUnit(unit1p);

   BOOST_CHECK_EQUAL(pays1->listUnit.size(),1);
   BOOST_CHECK_EQUAL(pays2->listUnit.size(),2);

   // pays1 n'ayant qu'une dernière unité, cette dernière ne peut normalement pas être supprimer
   pays1->DeleteUnit(unit1);

   BOOST_CHECK_EQUAL(pays1->listUnit.size(),1);

   // Test de GetEnemiesCountry()
   BOOST_CHECK_EQUAL(pays1->GetEnemiesCountry().size(),1);
   // Test de FindTypeNumber()
   BOOST_CHECK_EQUAL(pays2->FindTypeNumber(type),1);

}

BOOST_AUTO_TEST_CASE(TestAttack)
{
   // Creation de 2 joueurs
   const auto joueur1 = std::make_shared<Player>();
   const auto joueur2 = std::make_shared<Player>();

   // Creation des 2 pays et de leurs unités
   std::shared_ptr<Country> pays1 = std::make_shared<Country>();
   pays1->owner = joueur1;
   Type type = attaquant;
   std::shared_ptr<Unit> unit1 = std::make_shared<Unit>(type);
   std::shared_ptr<Unit> unit1p = std::make_shared<Unit>();
   pays1->AddUnit(unit1);
   pays1->AddUnit(unit1p);

   std::shared_ptr<Country> pays2 = std::make_shared<Country>();
   pays2->owner = joueur2;
   std::shared_ptr<Unit> unit2 = std::make_shared<Unit>(type);
   std::shared_ptr<Unit> unit2p = std::make_shared<Unit>();
   pays2->AddUnit(unit2);
   pays2->AddUnit(unit2p);

   // Les pays sont ajoutés comme voisins l'un de l'autre
   pays1->AddNeighboor(pays2);
   pays2->AddNeighboor(pays1);

  // Creation de l'attaque
  Attack attack;
  BOOST_CHECK_EQUAL(attack.GetActionType(),ActionType::_ATTACK);  
  
  // Ajout des pays et unités à l'attaque

  attack.attackerCountry = pays1;
  attack.defencerCountry = pays2;

  std::shared_ptr<Unit> unit3 = std::make_shared<Unit>(type);

  attack.AddUnit(unit1);
  attack.AddUnit(unit2);
  
  // Cette unité n'appartient à aucun des pays impliqué elle ne peut pas être ajouté à l'attaque
  attack.AddUnit(unit3);

  BOOST_CHECK_EQUAL(pays1->listUnit.size(),1);
  BOOST_CHECK_EQUAL(pays2->listUnit.size(),1);
  BOOST_CHECK_EQUAL(attack.attackerUnits.size(),1);
  BOOST_CHECK_EQUAL(attack.defencerUnits.size(),1);

  attack.KillUnit(unit1);
  BOOST_CHECK_EQUAL(attack.attackerUnits.size(),0);
  
  attack.AttackIsOver();
  BOOST_CHECK_EQUAL(attack.attackerUnits.size(),0);
  BOOST_CHECK_EQUAL(attack.defencerUnits.size(),0);

  BOOST_CHECK_EQUAL(pays1->listUnit.size(),1);
  BOOST_CHECK_EQUAL(pays2->listUnit.size(),2);

}

BOOST_AUTO_TEST_CASE(TestMovement)
{
  // Creation de 2 joueurs
   const auto joueur = std::make_shared<Player>();

   // Creation des 2 pays et de leurs unités
   std::shared_ptr<Country> pays1 = std::make_shared<Country>();
   pays1->owner = joueur;
   Type type = attaquant;
   std::shared_ptr<Unit> unit1 = std::make_shared<Unit>(type);
   std::shared_ptr<Unit> unit1b = std::make_shared<Unit>();
   std::shared_ptr<Unit> unit1t = std::make_shared<Unit>();
   std::shared_ptr<Unit> unit1q = std::make_shared<Unit>();
   std::shared_ptr<Unit> unit1p = std::make_shared<Unit>();
   pays1->AddUnit(unit1);
   pays1->AddUnit(unit1b);
   pays1->AddUnit(unit1t);
   pays1->AddUnit(unit1q);
   pays1->AddUnit(unit1p);

   std::shared_ptr<Country> pays2 = std::make_shared<Country>();
   pays2->owner = joueur;
   std::shared_ptr<Unit> unit2 = std::make_shared<Unit>(type);
   
   pays2->AddUnit(unit2);

   // Les pays sont ajoutés comme voisins l'un de l'autre
   pays1->AddNeighboor(pays2);
   pays2->AddNeighboor(pays1);

   // Creation de la classe movement du pays1 vers le pays2
   Movement movement;
   BOOST_CHECK_EQUAL(movement.GetActionType(),ActionType::_MOVEMENT);
   movement.origin = pays1;
   movement.destination = pays2;

   // Ajout des unités à deplacer
   movement.AddUnitToMove(unit1b);
   movement.AddUnitToMove(unit1t);
   movement.AddUnitToMove(unit1q);
   movement.AddUnitToMove(unit1p);
   // On vérifie que les unités on bien été supprimer du pays d'origine et sont bien stocké dans la classe mouvement
   BOOST_CHECK_EQUAL(pays1->listUnit.size(),1);
   BOOST_CHECK_EQUAL(movement.units.size(),4);

   // On deplace une unité et on vérifie qu'elle est bien arrivé à destination
   movement.MoveUnit(unit1b);
   BOOST_CHECK_EQUAL(pays2->listUnit.size(),2);
   BOOST_CHECK_EQUAL(movement.units.size(),3);

   /*movement.MoveAllUnit();
   BOOST_CHECK_EQUAL(pays2->listUnit.size(),5);
   BOOST_CHECK_EQUAL(movement.units.size(),0);*/

}

BOOST_AUTO_TEST_CASE(TestPlayer)
{
   /*Player player;
   std::shared_ptr<Country> pays1 = std::make_shared<Country>();
   std::shared_ptr<Country> pays2 = std::make_shared<Country>();

   player.AddOwnedCountry(pays1);
   player.AddOwnedCountry(pays2);

   BOOST_CHECK_EQUAL(player.listOwnedCountry.size(),2);*/

}



/* vim: set sw=2 sts=2 et : */
