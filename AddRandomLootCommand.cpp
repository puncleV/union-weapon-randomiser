#include <array>
namespace GOTHIC_ENGINE {
	std::array < Loot<33>, 17> LOOT_TABLE = {
		Loot<33>(5, 1000, false, { "ITPO_PERM_DEF" }),
		Loot<33>(10, 1000, false, { "ITPO_NP_STATS" }),
		Loot<33>(15, 1000, false, { "ITPO_FIREDEFENCE", "ITPO_MAGDEFENCE" }),
		Loot<33>(15, 1000, false, { "ITMI_POTIONPERMBLANK", "ITPO_INTELLECT", "ITPO_ELIXIRSHADOW", "ITSC_TRFDRAGONSNAPPER", "ITPL_PERM_HERB", "ITPO_NP_MANAREG3", "ITPO_PERM_MANA"}),
		Loot<33>(35, 1000, true, {
			"ITRU_BELIARSRAGE",
			"ITRU_ICEEXPLOISION",
			"ITRU_SUMMONGUARDIAN",
			"ITRU_SUMGOL",
			"ITRU_SUMFIREGOL",
			"ITRU_ACID",
			"ITRU_SUMSWPGOL",
			"ITRU_CHARGEFIREBALL",
			"ITRU_LIGHTNINGFLASH",
			"ITRU_LIGHTNINGSPHERE",
			"ITRU_ELECTROWAVE",
			"ITRU_SUMICEGOL",
			"ITRU_DEATHBALL",
		}),
		Loot<33>(40, 1000, true, {
			"ITAM_DIAMOND",
			"ITAM_RUBY",
			"ITAM_EMERALD",
			"ITAM_SAPPHIRE",
			"ITAM_OPAL",
			"ITAM_PROT_EDGE_01",
			"ITAM_PROT_POINT_01",
			"ITAM_PROT_MAGE_01"
		}),
		Loot<33>(45, 1000, true, { "ITRI_ORE_DIAM", "ITRI_ORE_EMER", "ITRI_ORE_SAPP", "ITRI_ORE_OPAL", "ITRI_ORE_TOPA", "ITRI_ORE_RUBY" }),
		Loot<33>(50, 1000, false, { "ITFO_CAKE_MUSHROOM", "ITFO_CAKE_FISH", "ITFO_CAKE_APPLE", "ITFO_CAKE_MEAT", "ITFO_CAKE_HONEY", "ITFO_EALBALZAM", "ITFO_EALBALZAMTWO", "ITPL_PERM_HERB", "ITMI_JEWELERYCHEST", "ITPO_HEALTH_03", "ITPO_MANA_03", "ITPO_NP_MANAREG2", "ITPO_NP_STAMINA" }),
		Loot<33>(60, 1000, true, { "ITRI_GOLD_DIAM", "ITRI_GOLD_EMER", "ITRI_GOLD_SAPP", "ITRI_GOLD_OPAL", "ITRI_GOLD_TOPA", "ITRI_GOLD_RUBY" }),
		Loot<33>(60, 1000, true, { "ITRI_STEEL_DIAM", "ITRI_STEEL_EMER", "ITRI_STEEL_SAPP", "ITRI_STEEL_OPAL", "ITRI_STEEL_TOPA", "ITRI_STEEL_RUBY", "ITRI_NEW_OREMASTER", "ITRI_NEW_MANAREGEN", "ITRI_HP_PARLAN" }),
		Loot<33>(60, 1000, false, { "ITPO_NP_MANAREG3", "ITPO_NP_MANAREG2", "ITPO_NP_STAMINA", "ITPO_HEALTH_03", "ITPO_HEALTH_02", "ITPO_MANA_03", "ITPO_MANA_02", "ITRW_ADDON_MAGICARROW", "ITRW_ADDON_MAGICBOLT", "ITSC_RESSURECT", "ITSC_UNLOCK", "ITSC_ICECUBE" }),
		Loot<33>(65, 1000, true, {
			"ITRU_INSTANTFIREBALL",
			"ITRU_STONEFIRST",
			"ITRU_ICELANCE",
			"ITRU_SUMSHOAL",
			"ITRU_WINDFIST",
			"ITRU_FIRESTORM",
			"ITRU_ICECUBE",
			"ITRU_THUNDERBALL",
			"ITRU_MAGSPHERE",
			"ITRU_CHARM",
			"ITRU_SUMSKEL",
		}),
		Loot<33>(75, 1000, true, { "ITBE_ADDON_MIL_01", "ITBE_ADDON_SLD_01", "ITBE_ADDON_NOV_01", "ITBE_ADDON_SEK_01", "ITBE_ADDON_THIEF_01",
			"ITBE_ADDON_THIEF_02", "ITBE_ADDON_STR_10", "ITBE_ADDON_DEX_10", "ITAM_DEX_01", "ITAM_STRG_01", "ITRI_MANA_02", "ITBE_ADDON_SEK_01",
			"ITBE_ADDON_PROT_EDGE", "ITBE_ADDON_PROT_POINT", "ITBE_ADDON_PROT_MAGIC", "ITBE_ADDON_PROT_FIRE", "ITBE_ADDON_PROT_EDGPOI", "ITBE_ADDON_PROT_TOTAL",
			"ITBE_ADDON_CUSTOM_01", "ITBE_ADDON_CUSTOM_02", "ITBE_ADDON_CUSTOM_03",
			"ITBE_ADDON_CUSTOM_04",
		}),
		Loot<33>(85, 1000, true, {
			"ITRU_FIREBOLT",
			"ITRU_ZAP",
			"ITRU_ICEBOLT",
			"ITRU_SLEEP",
			"ITRU_BERZERK",
			"ITRU_DEATHBOLT",
			"ITRU_SUMGOBSKEL",
			"ITRU_SUMWOLF",
		}),
		Loot<33>(95, 1000, true, { "ITWR_ADDON_RUNEMAKING_KDW_CIRC1", "ITWR_ADDON_RUNEMAKING_KDW_CIRC2", "ITWR_ADDON_RUNEMAKING_KDW_CIRC3", "ITWR_ADDON_RUNEMAKING_KDW_CIRC4", "ITWR_ADDON_RUNEMAKING_KDW_CIRC5",
			"ITWR_ADDON_RUNEMAKING_KDF_CIRC1", "ITWR_ADDON_RUNEMAKING_KDF_CIRC2", "ITWR_ADDON_RUNEMAKING_KDF_CIRC3", "ITWR_ADDON_RUNEMAKING_KDF_CIRC4", "ITWR_ADDON_RUNEMAKING_KDF_CIRC5",
			"ITWR_ADDON_RUNEMAKING_GUR_CIRC1", "ITWR_ADDON_RUNEMAKING_GUR_CIRC2", "ITWR_ADDON_RUNEMAKING_GUR_CIRC3", "ITWR_ADDON_RUNEMAKING_GUR_CIRC4", "ITWR_ADDON_RUNEMAKING_GUR_CIRC5",
			"ITWR_ADDON_RUNEMAKING_DMT_CIRC1", "ITWR_ADDON_RUNEMAKING_DMT_CIRC2", "ITWR_ADDON_RUNEMAKING_DMT_CIRC3", "ITWR_ADDON_RUNEMAKING_DMT_CIRC4", "ITWR_ADDON_RUNEMAKING_DMT_CIRC5",
			"ITWR_ADDON_RUNEMAKING_PRM", "ITWR_ORCLANGUAGE", "ITWR_ALCHEMY_01", "ITWR_BOWBETTERSHOT", "ITWR_BLOODFLY_01", "ITWR_GOLDMAKE", "ITWR_JAGD_UND_BEUTE"
		}),
		Loot<33>(130, 1000, false, { "ITPO_SPEED_03", "ITPO_HEALTH_01", "ITPO_MANA_01", "ITRW_ADDON_MAGICARROW",
			"ITRW_EXPLOSIVEBOLT", "ITRW_BOLT", "ITRW_ARROW", "ITFO_BREAD", "ITAT_CLAW", "ITPL_BEET", "ITSC_TRFWOLF", "ITSC_TRFSCAVENGER", "ITSC_SLEEP", "ITPL_MUSHROOM_02",
			"ITSC_TRFLURKER", "ITSC_TRFSNAPPER", "ITSC_SUMGOBSKEL"
		}),
		Loot<33>(370, 1000, false, {  "ITMI_GOLD", "ITPL_BEET", "ITRW_ADDON_MAGICARROW", "ITRW_EXPLOSIVEBOLT", "ITRW_BOLT", "ITRW_ARROW", "ITFO_BEER", "ITFO_APPLE", "ITFO_BREAD", "ITFO_BOOZE", "ITFO_WATER",
			"ITFO_WINE", "ITFO_WINEBERRYS", "ITFO_SCHILDKROETESOUP_SBORKA", "ITFO_ADDON_RUM", "ITFO_ADDON_SHELLFLESH", "ITFO_SMELLYFISH", "ITMI_BRUSH", "ITAT_CLAW", "ITSC_FIREBOLT",
			"ITSC_ICEBOLT", "ITSC_LIGHT", "ITSC_ZAP", "ITSC_DEATHBOLT", "ITSC_SUMWOLF", "ITSC_SUMGOBSKEL", "ITPL_MANA_HERB_01", "ITPL_HEALTH_HERB_01", "ITPL_MUSHROOM_01", "ITPL_BLUEPLANT",
			"ITPL_FORESTBERRY", "ITPL_PLANEBERRY", "ITMI_SNUGGET"
		})
	};

	std::array < zSTRING, 35 > defaultLoot = {
		"ITMI_GOLD", "ITMI_GOLD", "ITRW_EXPLOSIVEBOLT", "ITRW_ADDON_MAGICARROW", "ITFO_POTTAGE_MUSHROOM_BLACK", "ITPO_NP_MANAREG2", "ITFO_POTTAGE_MUSHROOM_BLACK", "ITFO_POTTAGE_MUSHROOM_BLACK",
		"ITFO_POTTAGE_MUSHROOM", "ITFO_COMPOTE_00", "ITFO_SCHILDKROETESOUP_SBORKA", "ITFO_SCHILDKROETESOUP_SBORKA", "ITFO_SCHILDKROETESOUP_SBORKA", "ITFO_WINE_GRITTA",
		"ITMI_ADDON_JOINT_01", "ITMI_JOINT_02", "ITMI_JOINT_03", "ITFO_SMELLYFISH", "ITFO_ADDON_RUM_SKIP", "ITPO_NP_STAMINA", "ITFOMUTTON_NICLAS",
		"ITFO_XPSTEW", "ITFO_CAKE_APPLE", "ITFO_CAKE_MEAT", "ITFO_CAKE_MUSHROOM", "ITFO_CAKE_FISH", "ITFO_CAKE_HONEY", "ITFO_HILDASTEW",
		"ITSC_FIREBOLT", "ITSC_ICEBOLT", "ITSC_LIGHT", "ITSC_ZAP", "ITSC_DEATHBOLT", "ITSC_SUMWOLF", "ITSC_SUMGOBSKEL"
	};

	zCArray<zSTRING> randomLootGiven;

	template<std::size_t SIZE>
	zSTRING getDeduplicatedLoot(Loot<SIZE> loot) {
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

	int getRandomItemAmount(oCItem* item) {
		auto itemName = item->GetObjectName();

		if (itemName.HasWordI("ITPO_NP_STATS") || itemName.HasWordI("ITAM") || itemName.HasWordI("ITWR")
			|| itemName.HasWordI("ITRI") || itemName.HasWordI("ITBE") || itemName.HasWordI("ITPO_PERM_DEF")
			|| itemName.HasWordI("ITPO_FIREDEFENCE") || itemName.HasWordI("ITPO_MAGDEFENCE")) {
			return 1;
		}

		if (itemName.HasWordI("ITRW")) {
			return randomizer.Random(10, 30);
		}

		auto maxAmount = 10;

		if (IsTooCoolLoot(item)) {
			maxAmount = 2;
		}
		else if (itemName.StartWith("ITFO"))
		{
			maxAmount = 4;
		}

		return randomizer.Random(1, maxAmount);
	}

	void addRandomLootToNpc(oCNpc* npc, bool addToPlayer = false) {
		for (size_t i = 0; i < LOOT_TABLE.size(); ++i)
		{
			auto loot = LOOT_TABLE[i];
			auto itemName = getDeduplicatedLoot(loot);

			if (itemName == "") {
				continue;
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

				auto addStrengthMultiplier = (int)(item->value / 250) + 1;
				int additionalHp = randomizer.Random(15 * addStrengthMultiplier, npc->attribute[NPC_ATR_HITPOINTSMAX] * 0.15 * addStrengthMultiplier);

				npc->attribute[NPC_ATR_HITPOINTS] += additionalHp;
				npc->attribute[NPC_ATR_HITPOINTSMAX] += additionalHp;
				npc->attribute[NPC_ATR_STRENGTH] += 25 * addStrengthMultiplier;
				npc->attribute[NPC_ATR_DEXTERITY] += 25 * addStrengthMultiplier;

				npc->protection[oEDamageIndex_Blunt] += 5 * addStrengthMultiplier;
				npc->protection[oEDamageIndex_Edge] += 5 * addStrengthMultiplier;
				npc->protection[oEDamageIndex_Fire] += 5 * addStrengthMultiplier;
				npc->protection[oEDamageIndex_Point] += 5 * addStrengthMultiplier;
			}

			item->Release();
		}
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

				auto weightNotToAddLoot = 985 - ((int)npc->attribute[NPC_ATR_HITPOINTSMAX] / 250) * 16;

				if (RX_IsBoss(npc)) {
					npcsCount += 1;
					addRandomLootToNpc(npc, addToPlayer);
					addRandomLootToNpc(npc, addToPlayer);
				}
				else if (randomizer.Random(0, 1000) >= weightNotToAddLoot) {
					npcsCount += 1;
					addRandomLootToNpc(npc, addToPlayer);

					if (npc->attribute[NPC_ATR_HITPOINTSMAX] >= 500 && randomizer.Random(0, 1000) >= weightNotToAddLoot) {
						addRandomLootToNpc(npc, addToPlayer);
					}
				}
			}

			randomLootGiven.DeleteList();
		}

		return npcsCount;
	}
}