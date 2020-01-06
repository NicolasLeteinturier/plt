#include <queue>
#include "DeepAI.h"

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
	printf("ici avant seg fault deep ai\n");
	treeHead = std::make_shared<TreeNode>();
	printf("ici avant seg fault deep ai2\n");
	treeHead->gameState = engine->gameState;
	printf("ici avant seg fault deep ai3\n");
	treeHead->maxNode = true;
	printf("ici avant seg fault deep ai4\n");
	treeHead->treeHead = treeHead;
	printf("ici avant seg fault deep ai5\n");
	int max_leaf_index = 0;
	BuildTree();
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

void DeepAI::BuildTree()
{
	unsigned int compteurfeuille = 0;
	treeHead->BuildLeaf();
	
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
			//treeHead->leafs[i]->leafs[j]->BuildLeaf();
			treeHead->leafs[i]->leafs[j]->treeHead = treeHead;
			if(treeHead->leafs[i]->leafs[j]->gameState->currentPlayer != treeHead->gameState->currentPlayer)
				treeHead->leafs[i]->leafs[j]->maxNode = false;
			else
				treeHead->leafs[i]->leafs[j]->maxNode = true;
			//compteurfeuille += treeHead->leafs[i]->leafs[j]->leafs.size();
			/*for(unsigned int k = 0; k < treeHead->leafs[i]->leafs[j]->leafs.size(); k++)
			{
				treeHead->leafs[i]->leafs[j]->leafs[k]->treeHead = treeHead;
				if(treeHead->leafs[i]->leafs[j]->leafs[k]->gameState->currentPlayer != treeHead->gameState->currentPlayer)
					treeHead->leafs[i]->leafs[j]->leafs[k]->maxNode = false;
				else
					treeHead->leafs[i]->leafs[j]->leafs[k]->maxNode = true;
			}*/
		}
	}
	//printf("%d\n",compteurfeuille);
	return;
}
