#include <queue>
#include "DeepAI.h"
#include <thread>

using namespace ai;
using namespace state;
using namespace engine;

DeepAI::DeepAI(){}

void DeepAI::play()
{

	printf("Deep AI playing\n");
	if(engine->gameState->currentPlayer->isAnIA != IAType::DEEP)
	{
		return;
	}
	treeHead = std::make_shared<TreeNode>();
	treeHead->gameState = engine->gameState;
	treeHead->maxNode = true;
	treeHead->treeHead = treeHead;
	BuildTreeFromNode(2,treeHead);
	int max = 0;
	int index = 0;
	for(unsigned int i = 0; i < treeHead->leafs.size(); i++)
	{
		int temp = treeHead->leafs[i]->GetLeafScore();
		if(temp >= max)
		{
			max = temp;
			index = i;
		}
	}
	engine->gameState = treeHead->leafs[index]->gameState;
	return;
}

void DeepAI::BuildTreeFromNode(unsigned int profondeur, std::shared_ptr<TreeNode> treeHeadp)
{
	treeHeadp->BuildLeaf();
	for(unsigned int i = 0; i < treeHeadp->leafs.size(); i++)
	{
		treeHeadp->leafs[i]->treeHead = treeHead;
		if(treeHeadp->leafs[i]->gameState->currentPlayer != treeHead->gameState->currentPlayer)
			treeHeadp->leafs[i]->maxNode = false;
		else
			treeHeadp->leafs[i]->maxNode = true;
	}

	if(profondeur == 0)
		return;	

	std::vector<std::thread> threads;

	for(unsigned int i = 0; i < treeHeadp->leafs.size(); i++)
	{
		threads.emplace_back(([&,i,profondeur,treeHeadp](){
			BuildTreeFromNode(profondeur-1,treeHeadp->leafs[i]);
		}));
	}
	for(unsigned int i = 0; i < treeHeadp->leafs.size(); i++)
	{
		threads[i].join();
	}

	/*unsigned int compteurfeuille = 0;
	treeHeadp->BuildLeaf();
	
	for(unsigned int i = 0; i < treeHead->leafs.size(); i++)
	{
		treeHead->leafs[i]->BuildLeaf();
		treeHead->leafs[i]->treeHead = treeHead;
		if(treeHead->leafs[i]->gameState->currentPlayer != treeHead->gameState->currentPlayer)
			treeHead->leafs[i]->maxNode = false;
		else
			treeHead->leafs[i]->maxNode = true;
		for(unsigned int j = 0; j < treeHead->leafs[i]->leafs.size(); j++)
		{
			treeHead->leafs[i]->leafs[j]->BuildLeaf();
			treeHead->leafs[i]->leafs[j]->treeHead = treeHead;
			if(treeHead->leafs[i]->leafs[j]->gameState->currentPlayer != treeHead->gameState->currentPlayer)
				treeHead->leafs[i]->leafs[j]->maxNode = false;
			else
				treeHead->leafs[i]->leafs[j]->maxNode = true;
			compteurfeuille += treeHead->leafs[i]->leafs[j]->leafs.size();
			for(unsigned int k = 0; k < treeHead->leafs[i]->leafs[j]->leafs.size(); k++)
			{
				treeHead->leafs[i]->leafs[j]->leafs[k]->treeHead = treeHead;
				if(treeHead->leafs[i]->leafs[j]->leafs[k]->gameState->currentPlayer != treeHead->gameState->currentPlayer)
					treeHead->leafs[i]->leafs[j]->leafs[k]->maxNode = false;
				else
					treeHead->leafs[i]->leafs[j]->leafs[k]->maxNode = true;
			}
		}
	}
	printf("%d\n",compteurfeuille);*/
	return;
}
