#include "Node.h"
#include <list>

using namespace std;

void traverse(node_t* node)
{
	node_t* nextNode = node->execute();
	if (nextNode != nullptr)
	{
		//<call traverse with next node, uses recursion to descend tree until the leaf(action)>
		traverse(nextNode);
	}
}

int main()
{
	bool enemySeen = false;
	float enemyDistance = 12.0f;
	bool enemyHeard = true;
	bool onFlank = false;

	node_t* attackAction = new action_t("Attack");
	node_t* moveAction = new action_t("Move");
	node_t* sneakAction = new action_t("Sneak");
	node_t* patrollAction = new action_t("Patroll");

	node_t* root = new decision_t<bool>("Enemies Seen", enemySeen, ePredicate::Equal, true);
	node_t* enemyClose = new decision_t<float>("Distance to Enemy", enemyDistance, ePredicate::Less, 10.0f);
	node_t* enemyOnFlank = new decision_t<bool>("Enemy on Flank", onFlank, ePredicate::Equal, true);
	node_t* enemyAudible = new decision_t<bool>("Heard Enemy", enemyHeard, ePredicate::Equal, true);

	//	root (time of day)
	//	/   \
	//     /    tired
	//    /   /     \
	//   study      sleep

	root->trueNode = enemyClose;
	root->falseNode = enemyAudible;

	enemyClose->trueNode = attackAction;
	enemyClose->falseNode = enemyOnFlank;

	enemyOnFlank->trueNode = moveAction;
	enemyOnFlank->falseNode = attackAction;

	enemyAudible->trueNode = sneakAction;
	enemyAudible->falseNode = patrollAction;

	// traverse decision tree from root
	traverse(root);
}