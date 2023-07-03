// Supported with union (c) 2020 Union team
// Union SOURCE file

#include <array>
#include <set>
namespace GOTHIC_ENGINE {

	class Loot {
	private:
		std::set <zSTRING> npcIgnoreList;
		int probability;
		int probabilityOutOf;
		bool shouldDeduplicate;
		int minAmount;
		int maxAmount;

		int getRandomItemAmount(oCItem* item) {
			auto itemName = item->GetObjectName();

			if (minAmount == maxAmount) {
				return minAmount;
			}

			return randomizer.Random(minAmount, maxAmount);
		}

		oCItem* getItemWithAmount(zSTRING name) {
			oCItem* item = static_cast<oCItem*>(ogame->GetGameWorld()->CreateVob_novt(zVOB_TYPE_ITEM, name));

			if (!item) {
				return nullptr;
			}

			if (item->HasFlag(ITM_FLAG_MULTI)) {
				item->amount = getRandomItemAmount(item);
			}

			return item;
		}
	public:
		std::vector <zSTRING> possibleLootNames;

		Loot(int _chanceWeight, int _chanceUpperbound, bool _shouldDeduplicate, std::vector <zSTRING> _possibleLootNames, int _minAmount = 1, int _maxAmount = 1) {
			possibleLootNames = _possibleLootNames;
			probability = _chanceWeight;
			probabilityOutOf = _chanceUpperbound;
			shouldDeduplicate = _shouldDeduplicate;
			minAmount = _minAmount;
			maxAmount = _maxAmount;
		};

		bool tryAddToNpc(oCNpc* npc, std::set <zSTRING>& alreadyGivenItemNames, bool shouldAddToPlayer = false) {
			if (!npc) {
				return FALSE;
			}

			if (randomizer.Random(0, probabilityOutOf) <= probability) {
				auto itemName = randomizer.getRandomArrayElement(possibleLootNames);
				auto found = alreadyGivenItemNames.find(itemName);
				
				alreadyGivenItemNames.insert(itemName);

				if (found != alreadyGivenItemNames.end() && shouldDeduplicate && randomizer.Random(0, 1000) <= 900) {
					itemName = randomizer.getRandomArrayElement(defaultLoot);
				}

				auto item = getItemWithAmount(itemName);

				if (shouldAddToPlayer) {
					player->PutInInv(item);
				}
				else {
					npc->PutInInv(item);
					strengthenNpc(npc, item->value * item->amount);
				}

				item->Release();

				return TRUE;
			}

			return FALSE;
		};

		void strengthenNpc(oCNpc* npc, int itemValue = 1) {
			if (npc == player) {
				return;
			}

			auto addStrengthMultiplier = (int)(itemValue / VALUE_STRENGTH_PER_LOOT_MULTIPLIER) + BASE_STRENGTH_PER_LOOT_MULTIPLIER;
			auto extaHpBasePercent = ENEMY_HP_FACTOR / npc->attribute[NPC_ATR_HITPOINTSMAX];
			int additionalHp = randomizer.Random(50 * addStrengthMultiplier, npc->attribute[NPC_ATR_HITPOINTSMAX] * extaHpBasePercent * addStrengthMultiplier);

			npc->attribute[NPC_ATR_HITPOINTSMAX] += additionalHp;
			npc->attribute[NPC_ATR_HITPOINTS] += additionalHp;
			npc->attribute[NPC_ATR_STRENGTH] += ENEMY_STATS_PER_MULTIPLIER * addStrengthMultiplier;
			npc->attribute[NPC_ATR_DEXTERITY] += ENEMY_STATS_PER_MULTIPLIER * addStrengthMultiplier;

			if (npc->protection[oEDamageIndex_Blunt] != -1) {
				npc->protection[oEDamageIndex_Blunt] += ENEMY_DEFENCE_PER_MULTIPLIER * addStrengthMultiplier;
			}

			if (npc->protection[oEDamageIndex_Edge] != -1) {
				npc->protection[oEDamageIndex_Edge] += ENEMY_DEFENCE_PER_MULTIPLIER * addStrengthMultiplier;
			}
			
			if (npc->protection[oEDamageIndex_Fire] != -1) {
				npc->protection[oEDamageIndex_Fire] += ENEMY_DEFENCE_PER_MULTIPLIER * addStrengthMultiplier;
			}

			if (npc->protection[oEDamageIndex_Point] != -1) {
				npc->protection[oEDamageIndex_Point] += ENEMY_DEFENCE_PER_MULTIPLIER * addStrengthMultiplier;
			}

			if (npc->protection[oEDamageIndex_Magic] != -1) {
				npc->protection[oEDamageIndex_Magic] += ENEMY_DEFENCE_PER_MULTIPLIER * addStrengthMultiplier;
			}
		}

		bool tryAddToChest(oCMobContainer* chest, std::set <zSTRING>& alreadyGivenItemNames, bool shouldAddToPlayer = false) {
			if (!chest) {
				return FALSE;
			}

			if (randomizer.Random(0, probabilityOutOf) <= probability) {
				auto itemName = randomizer.getRandomArrayElement(possibleLootNames);
				auto found = alreadyGivenItemNames.find(itemName);

				alreadyGivenItemNames.insert(itemName);

				if (found != alreadyGivenItemNames.end() && shouldDeduplicate) {
					itemName = randomizer.getRandomArrayElement(defaultLoot);
				}

				auto item = getItemWithAmount(itemName);

				if (shouldAddToPlayer) {
					player->PutInInv(item);
				}
				else {
					chest->Insert(item);
				}

				item->Release();

				return TRUE;
			}

			return FALSE;
		};
	};
}