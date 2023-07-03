#include <array>
#include <set>
namespace GOTHIC_ENGINE {
	std::set<zSTRING> randomLootGiven;

	void addRandomLootToNpc(oCNpc* npc, bool addToPlayer = false, std::vector<Loot> lootTable = NPC_LOOT_TABLE) {
		for (size_t i = 0; i < lootTable.size(); ++i)
		{
			auto loot = lootTable[i];

			if (addToPlayer) {
				loot.tryAddToNpc(player, randomLootGiven);
			}
			else {
				loot.tryAddToNpc(npc, randomLootGiven);
			}
		}
	}

	int getExtraLootProbability(oCNpc* npc, oCWorld* world) {
		auto hpFactor = world->GetObjectName().HasWordI("NEWWORLD") ? EXTRA_LOOT_HP_FACTOR_HORINIS() : EXTRA_LOOT_HP_FACTOR_OTHER();
		auto chance =  EXTRA_LOOT_BASE_CHANCE() + ((int)npc->attribute[NPC_ATR_HITPOINTSMAX] / hpFactor) * EXTRA_LOOT_HP_FACTOR_MULTIPLIER();

		return max(chance, 10);
	}

	int AddRandomLoot(bool addToPlayer = false) {
		oCWorld* world = dynamic_cast<oCWorld*>(ogame->GetWorld());
		auto npcsCount = 0;
		if (world) {
			auto randomUpperBound = getRandomLootUpperound(world);
			auto hpFactor = world->GetObjectName().HasWordI("NEWWORLD") ? EXTRA_LOOT_HP_FACTOR_HORINIS() : EXTRA_LOOT_HP_FACTOR_OTHER();

			auto list = world->voblist_npcs;
			for (size_t i = 0; i < list->GetNumInList(); ++i)
			{
				oCNpc* npc = list->Get(i);

				if (npc == oCNpc::player || npc->attribute[NPC_ATR_HITPOINTS] <= 1)
					continue;

				if (RX_IsMageTrader(npc)) {
					addRandomLootToNpc(npc, addToPlayer);
					addRandomLootToNpc(npc, addToPlayer);

					addRandomLootToNpc(npc, addToPlayer, magicLoot);
				}
				else if (RX_IsAlchemistTrader(npc)) {
					addRandomLootToNpc(npc, addToPlayer);
					addRandomLootToNpc(npc, addToPlayer);
					addRandomLootToNpc(npc, addToPlayer, alchemistLoot);
				}
				else if (RX_IsTrader(npc)) {
					npcsCount += 1;

					addRandomLootToNpc(npc, addToPlayer);
					addRandomLootToNpc(npc, addToPlayer);
					addRandomLootToNpc(npc, addToPlayer, tradersLoot);
				}
				else if (RX_IsBoss(npc)) {
					npcsCount += 1;
					addRandomLootToNpc(npc, addToPlayer);
					addRandomLootToNpc(npc, addToPlayer);
					addRandomLootToNpc(npc, addToPlayer, bossLoot);
				}
				else if (randomizer.Random(0, randomUpperBound) <= getExtraLootProbability(npc, world)) {
					npcsCount += 1;
					addRandomLootToNpc(npc, addToPlayer);

					if (npc->attribute[NPC_ATR_HITPOINTSMAX] >= hpFactor && randomizer.Random(0, randomUpperBound) <= getExtraLootProbability(npc, world)) {
						addRandomLootToNpc(npc, addToPlayer);
					}
				}
			}

			randomLootGiven.clear();
		}

		return npcsCount;
	}
}