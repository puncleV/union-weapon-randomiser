// Supported with union (c) 2020 Union team
// Union SOURCE file

namespace GOTHIC_ENGINE {
	std::vector<zSTRING> alchemistsList = { "NONE_1192_FREGEAL", "VLK_498_IGNAZ", "BAU_980_SAGITTA", "VLK_409_ZURIS", "VLK_417_CONSTANTINO", "KDF_506_NEORAS", "NONE_100_XARDAS", "VLK_422_SALANDRIL" };
	std::vector<zSTRING> magicTraderList = { "VLK_6027_TALIASAN", "GUR_8003_TYON", "KDW_1401_ADDON_CRONOS_NW", "KDF_509_ISGAROTH", "KDF_508_GORAX", "KDF_506_NEORAS", "NONE_100_XARDAS" };
	std::vector<zSTRING> miscTradersList = {
		"VLK_458_RUPERT",
		"BDT_1091_ADDON_LUCIA",
		"PIR_1351_ADDON_SAMUEL",
		"PIR_50087",
		"BDT_1086_ADDON_SCATTY",
		"VLK_407_HAKON",
		"VLK_431_KARDIF",
		"VLK_412_HARAD",
		"VLK_410_BALTRAM",
		"VLK_408_JORA",
		"VLK_420_CORAGON",
		"BAU_970_ORLAN",
		"BAU_911_ELENA",
		"BAU_936_ROSI",
		"VLK_476_FENIA",
		"BDT_1097_ADDON_FISK",
		"BDT_10022_ADDON_MIGUEL",
		"VLK_416_MATTEO",
		"VLK_4301_ADDON_FARIM",
		"VLK_468_CANTHAR",
		"VLK_469_HALVOR",
		"VLK_484_LEHMAR",
	};

	void addRandomLootToNpc(oCNpc* npc, std::vector<Loot>& lootTable = NPC_LOOT_TABLE) {
		for (size_t i = 0; i < lootTable.size(); ++i)
		{
			lootTable[i].tryAddToNpc(npc);
		}
	}

	bool npcCanWearWeapon(oCItem* item, oCNpc* npc) {
		for (size_t i = 0; i < ITM_COND_MAX; i++)
		{
			if (item->cond_atr[i] <= 0 && item->cond_atr[i] >= NPC_ATR_MAX) {
				return false;
			}

			if (npc->attribute[item->cond_atr[i]] < item->cond_value[i])
			{
				return false;
			}
		}

		return true;
	}

	bool RX_IsBoss(oCNpc* npc) {
		return (npc && npc->aiscriptvars[AIV_BOSS] == TRUE);
	}

	bool RX_IsAlchemistTrader(oCNpc* npc) {
		auto npcName = npc->GetObjectName();

		for (auto i = 0; i < alchemistsList.size(); i += 1) {
			if (npcName.HasWordI(alchemistsList[i])) {
				return TRUE;
			}
		}

		return FALSE;
	}

	bool RX_IsMageTrader(oCNpc* npc) {
		auto npcName = npc->GetObjectName();

		for (auto i = 0; i < magicTraderList.size(); i += 1) {
			if (npcName.HasWordI(magicTraderList[i])) {
				return TRUE;
			}
		}

		return FALSE;
	}

	bool RX_IsTrader(oCNpc* npc) {
		auto npcName = npc->GetObjectName();

		for (auto i = 0; i < miscTradersList.size(); i += 1) {
			if (npcName.HasWordI(miscTradersList[i])) {
				return TRUE;
			}
		}

		return RX_IsMageTrader(npc) || RX_IsAlchemistTrader(npc);
	}
}