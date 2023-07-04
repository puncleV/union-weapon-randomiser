#include <array>
#include <set>
namespace GOTHIC_ENGINE {
	int AddRandomLoot() {
		oCWorld* world = dynamic_cast<oCWorld*>(ogame->GetWorld());
		auto npcsCount = 0;
		if (world) {
			auto randomUpperBound = getRandomLootUpperound(world);
			auto hpFactor = world->GetObjectName().HasWordI("NEWWORLD") ? EXTRA_LOOT_HP_FACTOR_HORINIS : EXTRA_LOOT_HP_FACTOR_OTHER;

			auto list = world->voblist_npcs;
			for (size_t i = 0; i < list->GetNumInList(); ++i)
			{
				oCNpc* npc = list->Get(i);

				if (npc == oCNpc::player || npc->attribute[NPC_ATR_HITPOINTS] <= 1)
					continue;

				if (RX_IsMageTrader(npc)) {
					addRandomLootToNpc(npc);
					addRandomLootToNpc(npc);

					addRandomLootToNpc(npc, magicLoot);
				}
				else if (RX_IsAlchemistTrader(npc)) {
					addRandomLootToNpc(npc);
					addRandomLootToNpc(npc);
					addRandomLootToNpc(npc, alchemistLoot);
				}
				else if (RX_IsTrader(npc)) {
					npcsCount += 1;

					addRandomLootToNpc(npc);
					addRandomLootToNpc(npc);
					addRandomLootToNpc(npc, tradersLoot);
				}
				else if (RX_IsBoss(npc)) {
					npcsCount += 1;
					addRandomLootToNpc(npc);
					addRandomLootToNpc(npc);
					addRandomLootToNpc(npc, bossLoot);
				}
				else if (randomizer.Random(0, randomUpperBound) <= getExtraLootProbability(npc, world)) {
					npcsCount += 1;
					addRandomLootToNpc(npc);

					if (npc->attribute[NPC_ATR_HITPOINTSMAX] >= hpFactor && randomizer.Random(0, randomUpperBound) <= getExtraLootProbability(npc, world)) {
						addRandomLootToNpc(npc);
					}
				}
			}
		}

		return npcsCount;
	}
}