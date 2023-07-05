// Supported with union (c) 2020 Union team
// Union SOURCE file

namespace GOTHIC_ENGINE {
	auto const ADDITIONAL_LOOT_GIVEN_NPC_VAR_IDX = 390;
	auto const WEAPON_RANDOMIZED_NPC_VAR_IDX = 391;
	auto const RANGED_WEAPON_RANDOMIZED_NPC_VAR_IDX = 392;

	void addLootToNPC(oCNpc* npc) { 
		oCWorld* world = dynamic_cast<oCWorld*>(ogame->GetWorld());
		auto randomUpperBound = getRandomLootUpperound(world);
		auto hpFactor = world->GetObjectName().HasWordI("NEWWORLD") ? EXTRA_LOOT_HP_FACTOR_HORINIS : EXTRA_LOOT_HP_FACTOR_OTHER;

		if (RX_IsMageTrader(npc)) {
			addRandomLootToNpc(npc, magicLoot);
		}
		else if (RX_IsAlchemistTrader(npc)) {
			addRandomLootToNpc(npc, alchemistLoot);
		}
		else if (RX_IsHunterTrader(npc)) {
			addRandomLootToNpc(npc, hunterLoot);
		}
		else if (RX_IsSmithTrader(npc)) {
			addRandomLootToNpc(npc, smithLoot);
		}
		else if (RX_IsTrader(npc)) {
			addRandomLootToNpc(npc);
			addRandomLootToNpc(npc);

			addRandomLootToNpc(npc, tradersLoot);
		}
		else if (RX_IsBoss(npc)) {
			addRandomLootToNpc(npc);
			addRandomLootToNpc(npc);

			addRandomLootToNpc(npc, bossLoot);
		}
		else if (randomizer.Random(0, randomUpperBound) <= getExtraLootProbability(npc, world)) {
			addRandomLootToNpc(npc);

			if (npc->attribute[NPC_ATR_HITPOINTSMAX] >= hpFactor && randomizer.Random(0, randomUpperBound) <= getExtraLootProbability(npc, world)) {
				addRandomLootToNpc(npc);
			}
		} else if (npc->IsHuman()) {
			addRandomLootToNpc(npc, humanLoot);
		}

		npc->setNpcVar(ADDITIONAL_LOOT_GIVEN_NPC_VAR_IDX, TRUE);
	}

	void randomizeMeleeWeapon(oCNpc* npc) {
		for (;;) {
			int weaponId = meleeWeaponsList[randomizer.Random(0, meleeWeaponsList.GetNumInList() - 1)];
			oCItem* item = static_cast<oCItem*>(ogame->GetGameWorld()->CreateVob(zVOB_TYPE_ITEM, weaponId));

			if (npcCanWearWeapon(item, npc)) {
				auto equippedWeapon = npc->GetEquippedMeleeWeapon();

				if (equippedWeapon != nullptr) {
					if (IsIgnoredOrTestItem(equippedWeapon)) {
						npc->UnequipItem(equippedWeapon);
					}

					if (!IsIgnoredOrTestItem(equippedWeapon)) {
						npc->RemoveFromInv(equippedWeapon, 1);
					}

					equippedWeapon->Release();

					npc->PutInInv(item);
					npc->EquipItem(item);

					if (IsDual(item)) {
						auto anotherDual = FindRandomItemThatHasString(meleeWeaponsList, OppositDualHand(item));

						if (anotherDual != nullptr) {
							npc->PutInInv(anotherDual);
							npc->EquipItem(anotherDual);
							anotherDual->Release();
						}
					}
				}

				item->Release();

				break;
			}
		}
	}
	
	void randomizeRangedWeapon(oCNpc* npc) {
		auto equippedRangedItem = npc->GetEquippedRangedWeapon();
		if (npc->GetEquippedRangedWeapon() != nullptr || randomizer.Random(0, 1000) <= CHANCE_TO_ADD_RANGED_WEAPON) {
			for (;;) {
				int weaponId = rangedWeaponsList[randomizer.Random(0, rangedWeaponsList.GetNumInList() - 1)];
				oCItem* item = static_cast<oCItem*>(ogame->GetGameWorld()->CreateVob(zVOB_TYPE_ITEM, weaponId));

				if (npcCanWearWeapon(item, npc)) {
					if (npc->GetEquippedRangedWeapon() != nullptr) {
						npc->UnequipItem(npc->RemoveFromInv(equippedRangedItem, 1));
						equippedRangedItem->Release();
					}

					npc->PutInInv(item);
					npc->EquipItem(item);

					item->Release();

					break;
				}

			}
		}
	}

	void oCNpc::setNpcVar(int varIdx, int value = 1) {
		parser->SetInstance("NPCVARINST", this);
		parser->CallFunc(parser->GetIndex("SetNpcVar"), varIdx, value);
	}

	int oCNpc::getNpcVar(int varIdx) {
		parser->SetInstance("NPCVARINST", this);
		auto value = *(int*)parser->CallFunc(parser->GetIndex("GetNpcVar"), varIdx);

		return value;
	}

	void goThroughNpcHandlers(oCNpc* npc) {
		if (rangedWeaponsList.GetNumInList() == 0) {
			rangedWeaponsList = getRangeWeaponsList();
		}

		if (meleeWeaponsList.GetNumInList() == 0) {
			meleeWeaponsList = getMeleeWeaponsList();
		}

		if (!npc) {
			return;
		}

		if (!npc->IsDead() && npc != oCNpc::player) {
			if (!npc->getNpcVar(ADDITIONAL_LOOT_GIVEN_NPC_VAR_IDX) && SHOULD_ADD_LOOT_TO_NPC || SHOULD_IGNORE_CHECK_TO_ADD_LOOT) {
				addLootToNPC(npc);
			}

			if (npc->IsHuman() && !npc->getNpcVar(WEAPON_RANDOMIZED_NPC_VAR_IDX) && SHOULD_SHUFFLE_MELEE_WEAPON) {
				randomizeMeleeWeapon(npc);
				npc->setNpcVar(WEAPON_RANDOMIZED_NPC_VAR_IDX, 1);
			}

			if (npc->IsHuman() && !npc->getNpcVar(RANGED_WEAPON_RANDOMIZED_NPC_VAR_IDX) && SHOULD_SHUFFLE_RANGED_WEAPON) {
				randomizeRangedWeapon(npc);
				npc->setNpcVar(RANGED_WEAPON_RANDOMIZED_NPC_VAR_IDX, 1);
			}
		}
	}

	zCArray<oCNpc*> oCNpc::getNpcInRadius(float radius) {
		ClearVobList();
		CreateVobList(radius);

		zCArray<zCVob*> vobList = this->vobList;
		zCArray<oCNpc*> npcList;
		zCVob* pVob = NULL;
		oCNpc* npc = NULL;

		for (int i = 0; i < vobList.GetNum(); i++) {
			pVob = vobList.GetSafe(i);
			if (!pVob)
				continue;
			npc = zDYNAMIC_CAST<oCNpc>(pVob);
			if (!npc)
				continue;
			if (npc->IsDead())
				continue;

			goThroughNpcHandlers(npc);
		}

		return npcList;
	}

	void oCNpc::randomizeChestsInRadius(float radius) {
		ClearVobList();
		CreateVobList(radius);

		zCArray<zCVob*> vobList = this->vobList;
		zCArray<oCMobContainer*> chestsList;
		zCVob* pVob = NULL;
		oCMobContainer* chest = NULL;

		for (int i = 0; i < vobList.GetNum(); i++) {
			pVob = vobList.GetSafe(i);
			if (!pVob)
				continue;
			chest = zDYNAMIC_CAST<oCMobContainer>(pVob);
			if (!chest)
				continue;
			if (chest->isRandomized())
				continue;

			chest->randomize();
		}
	}
}