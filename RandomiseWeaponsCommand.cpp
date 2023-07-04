// Supported with union (c) 2020 Union team
// Union SOURCE file
namespace GOTHIC_ENGINE {
	int (*innerEvalFunc)(const zSTRING&, zSTRING&);

	int RandomiseMeleeWeapons() {
		oCWorld* world = dynamic_cast<oCWorld*>(ogame->GetWorld());
		auto npcsCount = 0;

		if (world) {
			auto list = world->voblist_npcs;
			for (size_t i = 0; i < list->GetNumInList(); ++i)
			{
				oCNpc* npc = list->Get(i);

				if (npc == oCNpc::player || !npc->IsHuman())
					continue;

				randomizeMeleeWeapon(npc);
			}
		}

		return npcsCount;
	}

	int RandomiseRangedWeapons(int extraWeaponsPercent = 0) {
		rangedWeaponsList = getRangeWeaponsList();

		oCWorld* world = dynamic_cast<oCWorld*>(ogame->GetWorld());
		auto npcsCount = 0;

		if (world) {
			auto list = world->voblist_npcs;
			for (size_t i = 0; i < list->GetNumInList(); ++i)
			{
				oCNpc* npc = list->Get(i);

				if (npc == oCNpc::player || !npc->IsHuman())
					continue;

				randomizeRangedWeapon(npc);
			}
		}

		rangedWeaponsList.DeleteList();

		return npcsCount;
	}

	bool weaponRandomizerHandler(const zSTRING& inpstr, zSTRING& msg) {
		if (inpstr.HasWordI("MELEEWPNS")) {
			auto result = RandomiseMeleeWeapons();
			msg = "Changed weapons of: " + Z result + " npcs.";

			return true;
		}

		if (inpstr.HasWordI("RANGEDWPNS")) {
			auto result = RandomiseRangedWeapons(0);
			msg = "Changed weapons of: " + Z result + " npcs.";

			return true;
		}

		if (inpstr.HasWordI("RANGEDWPNS_ADD")) {
			auto result = RandomiseRangedWeapons(20);
			msg = "Changed weapons of: " + Z result + " npcs.";

			return true;
		}

		return false;
	}

	bool lootRandomizerHandler(const zSTRING& inpstr, zSTRING& msg) {
		if (inpstr.HasWordI("IGNORE_CHECKS")) {
			SHOULD_IGNORE_CHECK_TO_ADD_LOOT = SHOULD_IGNORE_CHECK_TO_ADD_LOOT ? 0 : 1;
			return true;
		}

		if (inpstr.HasWordI("TOGGLE_PLAYER")) {
			SHOULD_ADD_LOOT_TO_PLAYER = SHOULD_ADD_LOOT_TO_PLAYER ? 0 : 1;

			msg = "Should add to player value: " + Z SHOULD_ADD_LOOT_TO_PLAYER;
			return true;
		}

		if (inpstr.HasWordI("ADD")) {
			auto result = AddRandomLoot();
			msg = "Changed drop of: " + Z result + " npcs.";

			return true;
		}

		return false;
	}

	bool chestsRandomizerHandler(const zSTRING& inpstr, zSTRING& msg) {
		if (inpstr.HasWordI("SHUFFLE")) {
			auto result = shuffleChests();
			msg = "Shuffled container for: " + Z result + " items.";

			return true;
		}

		if (inpstr.HasWordI("ADD")) {
			auto result = addChestsLoot();

			msg = "Added: " + Z result + " items.";

			return true;
		}
	}

	bool herbsRandomizerHandler(const zSTRING& inpstr, zSTRING& msg) {
		if (inpstr.HasWordI("SHUFFLE")) {
			auto result = ShuffleHerbs();
			msg = "Shuffled herbs count: " + Z result;

			return true;
		}
	}

	int ConsoleEvalFunc(const zSTRING& inpstr, zSTRING& msg) {
		if (innerEvalFunc && innerEvalFunc(inpstr, msg))
			return true;

		if (inpstr.HasWordI("weaponsrandomizer")) {
			return weaponRandomizerHandler(inpstr, msg);
		}

		if (inpstr.HasWordI("lootrandomizer")) {
			return lootRandomizerHandler(inpstr, msg);
		}

		if (inpstr.HasWordI("chestsrandomizer")) {
			return chestsRandomizerHandler(inpstr, msg);
		}

		if (inpstr.HasWordI("herbsrandomizer")) {
			return herbsRandomizerHandler(inpstr, msg);
		}

		if (inpstr.HasWordI("punclevutils")) {
			if (inpstr.HasWordI("debug")) {
				IS_DEBUG = IS_DEBUG ? 0 : 1;
				msg = "Debug: " + IS_DEBUG;
			}
			else {
				RandomiseMeleeWeapons();
				RandomiseRangedWeapons(30);
				shuffleChests();
				addChestsLoot();
				ShuffleHerbs();
				AddRandomLoot();
				msg = "Executed all commands succesfully";
			}

			return true;
		}


		return false;
	}

	void RegisterEvalFunc() {
		int evalNum = 0;

		for (int i = 1; i < zCON_MAX_EVAL; i++)
			if (zcon->evalfunc[i])
				evalNum = i;

		innerEvalFunc = zcon->evalfunc[evalNum];
		zcon->evalfunc[evalNum] = &ConsoleEvalFunc;
	}

	void RegisterCommands() {
		RegisterEvalFunc();
		zcon->Register("weaponsrandomizer MELEEWPNS", "Randomize NPCs melee weapons");
		zcon->Register("weaponsrandomizer RANGEDWPNS", "Randomize NPCs ranged weapons");
		zcon->Register("lootrandomizer ADD", "Randomize NPCs weapons");
		zcon->Register("lootrandomizer TOGGLE_PLAYER", "Randomize NPCs weapons");
		zcon->Register("lootrandomizer IGNORE_CHECKS", "Randomize NPCs weapons");
		zcon->Register("chestsrandomizer SHUFFLE", "Shuffles chests content");
		zcon->Register("chestsrandomizer ADD", "Add chests content");
		zcon->Register("herbsrandomizer SHUFFLE", "Shuffles hrebs positions");
		zcon->Register("punclevutils debug", "Toggle debug");
		zcon->Register("punclevutils all", "Execute all commands at once");
	}
}