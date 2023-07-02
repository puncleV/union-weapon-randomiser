#include <array>
namespace GOTHIC_ENGINE {
	zCArray<zSTRING> randomLootGiven;

	zSTRING getDeduplicatedLoot(Loot loot) {
		auto lootName = loot.pick();

		if (lootName == "") {
			return "";
		}

		if (!loot.shouldDeduplicate || randomLootGiven.Search(lootName) == Invalid) {
			randomLootGiven.Insert(lootName);

			return lootName;
		}

		for (size_t i = 0; i < 3; ++i) {
			auto name = loot.pick();

			if (name == "") {
				continue;
			}

			if (randomLootGiven.Search(name) == Invalid || randomizer.Random(0, 1000) >= 800) {
				randomLootGiven.Insert(name);
				return name;
			}
		}

		return randomizer.getRandomArrayElement(defaultLoot);
	}

	void addLootToNpc(oCNpc* npc, Loot loot, bool addToPlayer = false) {
		auto itemName = getDeduplicatedLoot(loot);

		if (itemName == "") {
			return;
		}

		oCItem* item = static_cast<oCItem*>(ogame->GetGameWorld()->CreateVob_novt(zVOB_TYPE_ITEM, itemName));

		if (item->HasFlag(ITM_FLAG_MULTI)) {
			item->amount = getRandomItemAmount(item);
		}

		if (addToPlayer) {
			player->PutInInv(item);
		}
		else {
			npc->PutInInv(item);

			auto addStrengthMultiplier = (int)(item->value / VALUE_STRENGTH_PER_LOOT_MULTIPLIER()) + BASE_STRENGTH_PER_LOOT_MULTIPLIER();
			auto extaHpBasePercent = 150 / npc->attribute[NPC_ATR_HITPOINTSMAX];
			int additionalHp = randomizer.Random(15 * addStrengthMultiplier, npc->attribute[NPC_ATR_HITPOINTSMAX] * extaHpBasePercent * addStrengthMultiplier);

			npc->attribute[NPC_ATR_HITPOINTSMAX] += additionalHp;
			npc->attribute[NPC_ATR_HITPOINTS] += additionalHp;
			npc->attribute[NPC_ATR_STRENGTH] += ENEMY_STATS_PER_MULTIPLIER() * addStrengthMultiplier;
			npc->attribute[NPC_ATR_DEXTERITY] += ENEMY_STATS_PER_MULTIPLIER() * addStrengthMultiplier;

			npc->protection[oEDamageIndex_Blunt] += ENEMY_DEFENCE_PER_MULTIPLIER() * addStrengthMultiplier;
			npc->protection[oEDamageIndex_Edge] += ENEMY_DEFENCE_PER_MULTIPLIER() * addStrengthMultiplier;
			npc->protection[oEDamageIndex_Fire] += ENEMY_DEFENCE_PER_MULTIPLIER() * addStrengthMultiplier;
			npc->protection[oEDamageIndex_Point] += ENEMY_DEFENCE_PER_MULTIPLIER() * addStrengthMultiplier;
		}

		item->Release();
	}

	void addRandomLootToNpc(oCNpc* npc, bool addToPlayer = false) {
		for (size_t i = 0; i < NPC_LOOT_TABLE.size(); ++i)
		{
			auto loot = NPC_LOOT_TABLE[i];
			addLootToNpc(npc, loot, addToPlayer);
		}
	}


	int getExtraLootComplementaryProbability(oCNpc* npc) {
		auto chance = 1000 - EXTRA_LOOT_BASE_CHANCE() - ((int)npc->attribute[NPC_ATR_HITPOINTSMAX] / EXTRA_LOOT_HP_FACTOR()) * 25;

		return max(chance, 10);
	}

	int AddRandomLoot(bool addToPlayer = false) {
		oCWorld* world = dynamic_cast<oCWorld*>(ogame->GetWorld());
		auto npcsCount = 0;

		if (world) {
			auto list = world->voblist_npcs;
			for (size_t i = 0; i < list->GetNumInList(); ++i)
			{
				oCNpc* npc = list->Get(i);

				if (npc == oCNpc::player)
					continue;

				if (RX_IsMageTrader(npc)) {
					addRandomLootToNpc(npc, addToPlayer);
					addRandomLootToNpc(npc, addToPlayer);

					addLootToNpc(npc, magicLoot);
				}
				else if (RX_IsAlchemistTrader(npc)) {
					addRandomLootToNpc(npc, addToPlayer);
					addRandomLootToNpc(npc, addToPlayer);

					addLootToNpc(npc, alchemistLoot);
				}
				else if (RX_IsTrader(npc)) {
					npcsCount += 1;

					addRandomLootToNpc(npc, addToPlayer);
					addRandomLootToNpc(npc, addToPlayer);
					addRandomLootToNpc(npc, addToPlayer);
				}
				else if (RX_IsBoss(npc)) {
					npcsCount += 1;
					addRandomLootToNpc(npc, addToPlayer);
					addRandomLootToNpc(npc, addToPlayer);
					addLootToNpc(npc, bossLoot);
				}
				else if (randomizer.Random(0, 1000) >= getExtraLootComplementaryProbability(npc)) {
					npcsCount += 1;
					addRandomLootToNpc(npc, addToPlayer);

					if (npc->attribute[NPC_ATR_HITPOINTSMAX] >= 500 && randomizer.Random(0, 1000) >= getExtraLootComplementaryProbability(npc)) {
						addRandomLootToNpc(npc, addToPlayer);
					}
				}
			}

			randomLootGiven.DeleteList();
		}

		return npcsCount;
	}
}