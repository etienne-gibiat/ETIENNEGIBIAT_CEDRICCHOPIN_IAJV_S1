#include "StateMachine.h"
#include "Action.h"
void StateMachine::Init() {

	Action* reload = new Action("Reload", world);
	Action* attack_player = new Action("AttackPlayer", world);
	Action* move_to_player = new Action("MoveToPlayer", world);
	Action* get_weapon = new Action("GetWeapon", world);
	AllActions.push_back(reload);
	AllActions.push_back(attack_player);
	AllActions.push_back(move_to_player);
	AllActions.push_back(get_weapon);
	
	reload->AddPrecondition("Avoir une arme",false);
	reload->AddEffect("Avoir des munitions");

	attack_player->AddEffect("Tue la cible");
	attack_player->AddPrecondition("Avoir des munitions",false);
	attack_player->AddPrecondition("Avoir une arme",false);
	attack_player->AddPrecondition("Joueur a porter",false);

	move_to_player->AddEffect("Joueur a porter");

	get_weapon->AddEffect("Avoir une arme");
	get_weapon->AddEffect("Avoir des munitions");

}

void StateMachine::DeInit()
{
	for (Action* action : AllActions)
	{
		if (action != nullptr)
		{
			delete action;
			action = nullptr;
		}
	}

}