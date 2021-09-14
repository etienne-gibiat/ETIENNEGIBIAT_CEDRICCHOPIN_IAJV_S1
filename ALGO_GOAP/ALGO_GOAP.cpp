#include <iostream>
#include "World.h"
#include "Action.h"

int main()
{
	World world;

	Action* reload = new Action("Reload",world);
	Action* attack_player = new Action("AttackPlayer",world);
	Action* move_to_player = new Action("MoveToPlayer",world);
	Action* get_weapon = new Action("GetWeapon",world);
	reload->AddPrecondition("Avoir une arme");
	reload->AddEffect("Avoir des munitions");

	attack_player->AddEffect("Tue la cible");
	attack_player->AddPrecondition("Avoir des munitions");
	attack_player->AddPrecondition("Avoir une arme");
	attack_player->AddPrecondition("Joueur a porter");

	move_to_player->AddEffect("Joueur a porter");

	get_weapon->AddEffect("Avoir une arme");
	get_weapon->AddEffect("Avoir des munitions");

}