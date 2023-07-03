// Supported with union (c) 2020 Union team
// Union SOURCE file

namespace GOTHIC_ENGINE {
	const int BIT_ITEM_QUESTITEM = (1 << 19);

	bool IsQuestItem(oCItem* item) {
		if ((item->hitp & BIT_ITEM_QUESTITEM) != 0) {
			return true;
		}
		return false;
	}

	bool IsIgnoredOrTestItem(oCItem* item) {
		return item == nullptr || item->GetObjectName().HasWordI("ITMW_TEST") || item->GetObjectName().HasWordI("BELIAR") || item->GetObjectName().HasWordI("URIZEL") || item->GetObjectName().HasWordI("FERROSSWORD") ||
			item->GetObjectName().HasWordI("ABIGEILSPAGE") || item->GetObjectName().HasWordI("TRIBUTEDAGGER") || item->GetObjectName().HasWordI("ITNW_2H_KATANA") || item->GetObjectName().HasWordI("TARACOT") ||
			item->GetObjectName().HasWordI("ADANOSMOLOT") || item->GetObjectName().HasWordI("ASSBLADE") || item->GetObjectName().HasWordI("HOLY_HAMMER") || item->GetObjectName().HasWordI("ALRIKSSWORD") ||
			item->GetObjectName().HasWordI("ITMW_2H_ROD") || item->GetObjectName().HasWordI("DS_MONWEAPON_HALLOWEEN") || item->GetObjectName().HasWordI("GREATARBALET") || item->GetObjectName().HasWordI("MAGICCOSSBOW") ||
			item->GetObjectName().HasWordI("FAKESWORD") || item->GetObjectName().HasWordI("PAL_CLOACK") || item->GetObjectName().HasWordI("SENYAK") || item->GetObjectName().HasWordI("HALLEBERDE_CLAW") || item->GetObjectName().HasWordI("ITMW_STAFF_CLAW") ||
			item->GetObjectName().HasWordI("ITMW_1H_THIEF_01_RIGHT") || item->GetObjectName().StartWith("ITKE_") || item->GetObjectName().StartWith("LUTERO");
	}

	bool IsItemSymbol(zCPar_Symbol* symbol) {
		if (symbol->type != zPAR_TYPE_INSTANCE) {
			return false;
		}

		//  Instance isn't global scope
		if (symbol->name.HasWord(".")) {
			return false;
		}

		auto baseClass = parser->GetBaseClass(symbol);

		// Symbol isn't a item class
		if (baseClass != parser->GetIndex(oCItem::classDef->scriptClassName)) {
			return false;
		}

		return true;
	}

	// duals - LEFT RIGHT
	zCArray<int> getMeleeWeaponsList() {
		zCArray<int> weapons_list;

		auto c_item = parser->GetIndex(oCItem::classDef->scriptClassName);
		if (c_item == -1) {
			return 0;
		}

		int itemsCreated = 0;
		for (int i = 0; i < parser->symtab.GetNumInList(); i++) {
			zCPar_Symbol* symbol = parser->symtab.table[i];

			if (i == parser->instance_help) {
				continue;
			}

			if (!IsItemSymbol(symbol)) {
				continue;
			}

			oCItem* item = static_cast<oCItem*>(ogame->GetGameWorld()->CreateVob(zVOB_TYPE_ITEM, i));

			if (item == nullptr || item->mainflag != ITM_CAT_NF || item->HasFlag(ITM_FLAG_SHIELD) || IsIgnoredOrTestItem(item)) {
				continue;
			}

			item->Release();

			weapons_list.Insert(i);
		}

		return weapons_list;
	}

	zCArray<int> getRangeWeaponsList() {
		zCArray<int> weapons_list;
		auto c_item = parser->GetIndex(oCItem::classDef->scriptClassName);
		if (c_item == -1) {
			return 0;
		}

		int itemsCreated = 0;
		for (int i = 0; i < parser->symtab.GetNumInList(); i++) {
			zCPar_Symbol* symbol = parser->symtab.table[i];

			if (i == parser->instance_help) {
				continue;
			}

			if (!IsItemSymbol(symbol)) {
				continue;
			}

			oCItem* item = static_cast<oCItem*>(ogame->GetGameWorld()->CreateVob(zVOB_TYPE_ITEM, i));

			if (item == nullptr || item->mainflag != ITM_CAT_FF || IsIgnoredOrTestItem(item)) {
				continue;
			}
			item->Release();

			weapons_list.Insert(i);
		}

		return weapons_list;
	}

	oCItem* FindRandomItemThatHasString(zCArray<int> itemsList, zSTRING string) {

		for (auto iterator = 0;iterator < itemsList.GetNumInList();iterator += 1)
		{
			int itemId = itemsList[iterator];

			oCItem* item = static_cast<oCItem*>(ogame->GetGameWorld()->CreateVob(zVOB_TYPE_ITEM, itemId));

			if (item->GetObjectName().HasWordI(string)) {
				return item;
			}

			item->Release();
		}

		return nullptr;
	}

	bool IsDual(oCItem* item) {
		return item->GetObjectName().HasWordI("right") || item->GetObjectName().HasWordI("left");
	}

	zSTRING OppositDualHand(oCItem* item) {
		if (item->GetObjectName().HasWordI("right")) {
			return "left";
		}

		return "right";
	}

	int getRandomLootUpperound(oCWorld* world) {
		return world->m_strlevelName.HasWordI("NEWWORLD") ? EXTRA_LOOT_HORINIS_FACTOR() : EXTRA_LOOT_OTHER_FACTOR();
	}

	std::vector < Loot > NPC_LOOT_TABLE = {
		Loot(2, 1000, false, { "ITPO_PERM_DEF" }),
		Loot(2, 1000, false, { "ITPO_FIREDEFENCE" }),
		Loot(2, 1000, false, { "ITPO_MAGDEFENCE" }),
		Loot(7, 1000, false, { "ITPO_PERM_STRD", "ITPO_PERM_DEXD", "ITPO_PERM_MANAD", "ITPO_ANCIENTPOTION" }),
		Loot(15, 1000, false, { "ITMI_POTIONPERMBLANK", "ITPO_INTELLECT", "ITPL_PERM_HERB"}), // permanent potions
		Loot(5, 1000, false, { "ITPO_ELIXIRSHADOW" }), // invisibility
		Loot(10, 1000, false, { "ITPO_NP_STATS" }), // super perm potion
		Loot(35, 1000, true, { // cool runes
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
		Loot(35, 1000, false, { "ITPO_RAREPOTION_01", "ITPO_RAREPOTION_02", "ITPO_RAREPOTION_03", "ITPO_RAREPOTION_04", "ITPO_RAREPOTION_05", "ITPO_RAREPOTION_06", "ITPO_RAREPOTION_07", "ITPO_RAREPOTION_08" }),
		Loot(40, 1000, true, { // amulets
			"ITAM_DIAMOND",
			"ITAM_RUBY",
			"ITAM_EMERALD",
			"ITAM_SAPPHIRE",
			"ITAM_OPAL",
			"ITAM_PROT_EDGE_01",
			"ITAM_PROT_POINT_01",
			"ITAM_PROT_MAGE_01"
		}),
		Loot(45, 1000, false, { "ITPO_NP_MANAREG3", "ITPO_NP_STAMINA2", "ITPO_HITPOTION" }),
		Loot(45, 1000, true, { "ITRI_ORE_DIAM", "ITRI_ORE_EMER", "ITRI_ORE_SAPP", "ITRI_ORE_OPAL", "ITRI_ORE_TOPA", "ITRI_ORE_RUBY" }), // ore rings
		Loot(45, 1000, true, {  // wisp skills
			"ITMI_STEINKOHLE",
			"ITMI_POLLEN",
			"ITAT_ICELESSICE",
			"ITAT_GIANTMANDIBLES",
			"ITMI_MAGICSIGNET",
			"ITUT_SHINYCLAW",
			"ITMI_DEMONICQUARTZ",
			"ITMI_INDESTRUCTIBLESAPPHIRE",
			"ITMI_MARSHESSENCE",
			"ITMI_PARTOFTHEABYSS"
		}),
		Loot(50, 1000, false, { "ITSC_CHARGEFIREBALL", "ITSC_SHRINK", "ITSC_HARMUNDEAD", "ITSC_THUNDERSTORM", "ITSC_WHIRLWIND", "ITSC_ARMYOFDARKNESS", "ITSC_SKULL", "ITSC_TRFDRAGONSNAPPER" }), // scrolls
		Loot(50, 1000, false, { "ITFO_CAKE_MUSHROOM", "ITFO_CAKE_FISH", "ITFO_CAKE_APPLE", "ITFO_CAKE_MEAT", "ITFO_CAKE_HONEY", "ITFO_EALBALZAM", "ITFO_EALBALZAMTWO", "ITPL_PERM_HERB", "ITMI_JEWELERYCHEST" }),
		Loot(50, 1000, false, { "ITPO_NP_MANAREG2", "ITPO_NP_STAMINA" }),
		Loot(60, 1000, true, { "ITRI_GOLD_DIAM", "ITRI_GOLD_EMER", "ITRI_GOLD_SAPP", "ITRI_GOLD_OPAL", "ITRI_GOLD_TOPA", "ITRI_GOLD_RUBY" }),
		Loot(60, 1000, true, { "ITRI_STEEL_DIAM", "ITRI_STEEL_EMER", "ITRI_STEEL_SAPP", "ITRI_STEEL_OPAL", "ITRI_STEEL_TOPA", "ITRI_STEEL_RUBY", "ITRI_NEW_OREMASTER", "ITRI_NEW_MANAREGEN", "ITRI_HP_PARLAN" }),
		Loot(60, 1000, false, { "ITPO_NP_MANAREG3", "ITPO_NP_MANAREG2", "ITPO_NP_STAMINA", "ITPO_HEALTH_03", "ITPO_HEALTH_02", "ITPO_MANA_03", "ITPO_MANA_02", "ITRW_ADDON_MAGICARROW", "ITRW_ADDON_MAGICBOLT", "ITSC_RESSURECT", "ITSC_UNLOCK", "ITSC_ICECUBE" }),
		Loot(65, 1000, true, {
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
		Loot(75, 1000, true, { "ITBE_ADDON_MIL_01", "ITBE_ADDON_SLD_01", "ITBE_ADDON_NOV_01", "ITBE_ADDON_SEK_01", "ITBE_ADDON_THIEF_01",
			"ITBE_ADDON_THIEF_02", "ITBE_ADDON_STR_10", "ITBE_ADDON_DEX_10", "ITAM_DEX_01", "ITAM_STRG_01", "ITRI_MANA_02", "ITBE_ADDON_SEK_01",
			"ITBE_ADDON_PROT_EDGE", "ITBE_ADDON_PROT_POINT", "ITBE_ADDON_PROT_MAGIC", "ITBE_ADDON_PROT_FIRE", "ITBE_ADDON_PROT_EDGPOI", "ITBE_ADDON_PROT_TOTAL",
			"ITBE_ADDON_CUSTOM_01", "ITBE_ADDON_CUSTOM_02", "ITBE_ADDON_CUSTOM_03",
			"ITBE_ADDON_CUSTOM_04",
		}),
		Loot(85, 1000, true, {
			"ITRU_FIREBOLT",
			"ITRU_ZAP",
			"ITRU_ICEBOLT",
			"ITRU_SLEEP",
			"ITRU_BERZERK",
			"ITRU_DEATHBOLT",
			"ITRU_SUMGOBSKEL",
			"ITRU_SUMWOLF",
		}),
		Loot(95, 1000, true, { "ITWR_ADDON_RUNEMAKING_KDW_CIRC1", "ITWR_ADDON_RUNEMAKING_KDW_CIRC2", "ITWR_ADDON_RUNEMAKING_KDW_CIRC3", "ITWR_ADDON_RUNEMAKING_KDW_CIRC4", "ITWR_ADDON_RUNEMAKING_KDW_CIRC5",
			"ITWR_ADDON_RUNEMAKING_KDF_CIRC1", "ITWR_ADDON_RUNEMAKING_KDF_CIRC2", "ITWR_ADDON_RUNEMAKING_KDF_CIRC3", "ITWR_ADDON_RUNEMAKING_KDF_CIRC4", "ITWR_ADDON_RUNEMAKING_KDF_CIRC5",
			"ITWR_ADDON_RUNEMAKING_GUR_CIRC1", "ITWR_ADDON_RUNEMAKING_GUR_CIRC2", "ITWR_ADDON_RUNEMAKING_GUR_CIRC3", "ITWR_ADDON_RUNEMAKING_GUR_CIRC4", "ITWR_ADDON_RUNEMAKING_GUR_CIRC5",
			"ITWR_ADDON_RUNEMAKING_DMT_CIRC1", "ITWR_ADDON_RUNEMAKING_DMT_CIRC2", "ITWR_ADDON_RUNEMAKING_DMT_CIRC3", "ITWR_ADDON_RUNEMAKING_DMT_CIRC4", "ITWR_ADDON_RUNEMAKING_DMT_CIRC5",
			"ITWR_ADDON_RUNEMAKING_PRM", "ITWR_ORCLANGUAGE", "ITWR_ALCHEMY_01", "ITWR_BOWBETTERSHOT", "ITWR_BLOODFLY_01", "ITWR_GOLDMAKE", "ITWR_JAGD_UND_BEUTE"
		}),
		Loot(150, 1000, false, { "ITPO_SPEED_03", "ITPO_HEALTH_01", "ITPO_MANA_01", "ITRW_ADDON_MAGICARROW",
			"ITRW_EXPLOSIVEBOLT", "ITRW_BOLT", "ITRW_ARROW", "ITFO_BREAD", "ITAT_CLAW", "ITPL_BEET", "ITSC_TRFWOLF", "ITSC_TRFSCAVENGER", "ITSC_SLEEP", "ITPL_MUSHROOM_02",
			"ITSC_TRFLURKER", "ITSC_TRFSNAPPER", "ITSC_SUMGOBSKEL", "ITFO_HONEY"
		}),
		Loot(370, 1000, false, {  "ITMI_GOLD", "ITPL_BEET", "ITRW_ADDON_MAGICARROW", "ITRW_EXPLOSIVEBOLT", "ITRW_BOLT", "ITRW_ARROW", "ITFO_BEER", "ITFO_APPLE", "ITFO_BREAD", "ITFO_BOOZE", "ITFO_WATER",
			"ITFO_WINE", "ITFO_WINEBERRYS", "ITFO_SCHILDKROETESOUP_SBORKA", "ITFO_ADDON_RUM", "ITFO_ADDON_SHELLFLESH", "ITFO_SMELLYFISH", "ITWR_STONEPLATECOMMON_ADDON", "ITAT_CLAW", "ITSC_FIREBOLT",
			"ITSC_ICEBOLT", "ITSC_LIGHT", "ITSC_ZAP", "ITSC_DEATHBOLT", "ITSC_SUMWOLF", "ITSC_SUMGOBSKEL", "ITPL_MANA_HERB_01", "ITPL_HEALTH_HERB_01", "ITPL_MUSHROOM_01", "ITPL_BLUEPLANT",
			"ITPL_FORESTBERRY", "ITPL_PLANEBERRY", "ITMI_SNUGGET", "ITFO_HONEY"
		})
	};


	auto bossLoot = std::vector<Loot>{ 
		Loot(875, 1000, false, { "ITPO_RAREPOTION_01", "ITPO_RAREPOTION_02", "ITPO_RAREPOTION_03", "ITPO_RAREPOTION_04", "ITPO_RAREPOTION_05", "ITPO_RAREPOTION_06", "ITPO_RAREPOTION_07", "ITPO_RAREPOTION_08" }),
		Loot(350, 1000, false, { "ITPO_FIREDEFENCE", "ITPO_MAGDEFENCE", "ITPO_AMUNSU", "ITPO_MAGDEFENCE", "ITPO_INTELLECT", "ITPL_PERM_HERB" }),
	};

	auto alchemistLoot = std::vector<Loot>{ Loot(800, 1000, false, { "ITPO_FIREDEFENCE", "ITPO_MAGDEFENCE", "ITPO_AMUNSU", "ITPO_MAGDEFENCE", "ITPO_INTELLECT", "ITPO_NP_STATS", "ITPL_PERM_HERB" }) };
	auto magicLoot = std::vector<Loot>{ Loot(850, 1000, false, { "ITSC_CHARGEFIREBALL", "ITSC_SHRINK", "ITSC_HARMUNDEAD", "ITSC_THUNDERSTORM", "ITSC_WHIRLWIND", "ITSC_ARMYOFDARKNESS", "ITSC_SKULL", "ITSC_TRFDRAGONSNAPPER" }) };
	auto tradersLoot = std::vector<Loot>{};
}