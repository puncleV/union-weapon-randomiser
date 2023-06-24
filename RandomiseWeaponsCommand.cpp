// Supported with union (c) 2020 Union team
// Union SOURCE file
#include <array>
namespace GOTHIC_ENGINE {
    int (*innerEvalFunc)(const zSTRING&, zSTRING&);
    const zSTRING ORE_JEWELRY = "ORE_JEWELRY";
    zCArray<zSTRING> randomLootGiven;

    int RandomiseMeleeWeapons() {
        auto meleeWeaponsList = getMeleeWeaponsList();

        oCWorld* world = dynamic_cast<oCWorld*>(ogame->GetWorld());
        auto npcsCount = 0;

        if (world) {
            auto list = world->voblist_npcs;
            for (size_t i = 0; i < list->GetNumInList(); ++i)
            {
                oCNpc* npc = list->Get(i);

                if (npc == oCNpc::player || !npc->IsHuman())
                    continue;

                for (;;) {
                    int weaponId = meleeWeaponsList[randomizer.Random(0, meleeWeaponsList.GetNumInList() - 1)];
                    oCItem* item = static_cast<oCItem*>(ogame->GetGameWorld()->CreateVob(zVOB_TYPE_ITEM, weaponId));

                    if (npcCanWearWeapon(item, npc)) {
                        npcsCount += 1;
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
        }

        meleeWeaponsList.DeleteList();

        return npcsCount;
    }

    int RandomiseRangedWeapons(int extraWeaponsPercent) {
        auto rangedWeaponsList = getRangeWeaponsList();

        oCWorld* world = dynamic_cast<oCWorld*>(ogame->GetWorld());
        auto npcsCount = 0;

        if (world) {
            auto list = world->voblist_npcs;
            for (size_t i = 0; i < list->GetNumInList(); ++i)
            {
                oCNpc* npc = list->Get(i);

                if (npc == oCNpc::player || !npc->IsHuman())
                    continue;

                auto equippedRangedItem = npc->GetEquippedRangedWeapon();
                if (npc->GetEquippedRangedWeapon() != nullptr || randomizer.Random(0, 100) < extraWeaponsPercent) {
                    for (;;) {
                        int weaponId = rangedWeaponsList[randomizer.Random(0, rangedWeaponsList.GetNumInList() - 1)];
                        oCItem* item = static_cast<oCItem*>(ogame->GetGameWorld()->CreateVob(zVOB_TYPE_ITEM, weaponId));

                        if (npcCanWearWeapon(item, npc)) {
                            if (npc->GetEquippedRangedWeapon() != nullptr) {
                                    npc->UnequipItem(npc->RemoveFromInv(equippedRangedItem, 1));
                                    equippedRangedItem->Release();
                            }

                            npcsCount += 1;
                            // apparantely you dont need to delete existing item 
                            npc->PutInInv(item);
                            npc->EquipItem(item);

                            item->Release();

                            break;
                        }

                    }
                }
            }
        }

        rangedWeaponsList.DeleteList();

        return npcsCount;
    }

    zSTRING getLootNameIfNotGiven(zSTRING name) {
        if (randomLootGiven.Search(name) == Invalid) {
            return name;
        }

        std::array < zSTRING, 8> itemNames = { "ITMI_GOLD", "ITRW_EXPLOSIVEBOLT", "ITRW_ADDON_MAGICARROW", "ITPO_INTELLECT", "ITPO_NP_MANAREG3", "ITPO_TROLL_STAMINA", "ITPO_HEALTH_03", "ITPO_MANA_03" };
        return itemNames[randomizer.Random(1, itemNames.size() - 1)];
    }

    zCArray<zSTRING> getRandomLootNames() {
        auto randomNumber = randomizer.Random(0, 1000);
        zCArray<zSTRING> names;

        if (randomizer.Random(0, 10000) > 9900) { // 0.01%
            names.Insert("ITPO_NP_STATS");
        }

        if (randomizer.Random(0, 1000) > 980) { // 2%
            std::array < zSTRING, 6> itemNames = { "ITRI_ORE_DIAM", "ITRI_ORE_EMER", "ITRI_ORE_SAPP", "ITRI_ORE_OPAL", "ITRI_ORE_TOPA", "ITRI_ORE_RUBY" };

            auto chosenName = getLootNameIfNotGiven(itemNames[randomizer.Random(0, itemNames.size() - 1)]);
            randomLootGiven.Insert(chosenName);

            names.Insert(chosenName);
        }
        
        if (randomizer.Random(0, 1000) > 985) { // 1.5%
            std::array < zSTRING, 6> itemNames = { "ITMI_POTIONPERMBLANK", "ITPO_INTELLECT", "ITPO_ELIXIRSHADOW", "ITSC_TRFDRAGONSNAPPER", "ITPL_PERM_HERB", "ITPO_NP_MANAREG3" };

            names.Insert(itemNames[randomizer.Random(0, itemNames.size() - 1)]);
        }
        
        if (randomizer.Random(0, 1000) > 960) { // 4%
            std::array < zSTRING, 13> itemNames = {
                "ITFO_CAKE_MUSHROOM", "ITFO_CAKE_FISH", "ITFO_CAKE_APPLE", "ITFO_CAKE_MEAT", "ITFO_CAKE_HONEY", "ITFO_EALBALZAM", "ITFO_EALBALZAMTWO", 
                "ITPL_PERM_HERB", "ITMI_JEWELERYCHEST", "ITPO_HEALTH_03", "ITPO_MANA_03", "ITPO_NP_MANAREG2", "ITPO_NP_STAMINA"
            };

            names.Insert(itemNames[randomizer.Random(0, itemNames.size() - 1)]);
        }

        if (randomizer.Random(0, 1000) > 970) { // 3%
            std::array<zSTRING, 6> itemNames = {
               "ITRI_GOLD_DIAM", "ITRI_GOLD_EMER", "ITRI_GOLD_SAPP", "ITRI_GOLD_OPAL", "ITRI_GOLD_TOPA", "ITRI_GOLD_RUBY"
            };

            auto chosenName = getLootNameIfNotGiven(itemNames[randomizer.Random(0, itemNames.size() - 1)]);
            randomLootGiven.Insert(chosenName);

            names.Insert(chosenName);
        }

        if (randomizer.Random(0, 1000) > 970) { // 3%
            std::array<zSTRING, 9> itemNames = {
              "ITRI_STEEL_DIAM", "ITRI_STEEL_EMER", "ITRI_STEEL_SAPP", "ITRI_STEEL_OPAL", "ITRI_STEEL_TOPA", "ITRI_STEEL_RUBY", "ITRI_NEW_OREMASTER", "ITRI_NEW_MANAREGEN", "ITRI_HP_PARLAN"
            };
            auto chosenName = getLootNameIfNotGiven(itemNames[randomizer.Random(0, itemNames.size() - 1)]);
            randomLootGiven.Insert(chosenName);

            names.Insert(chosenName);
        }
        
        if (randomizer.Random(0, 1000) > 950) { // 5%
            std::array<zSTRING, 12> itemNames = {
                "ITPO_NP_MANAREG2", "ITPO_NP_STAMINA", "ITPO_HEALTH_03", "ITPO_HEALTH_02", "ITPO_MANA_03", "ITPO_MANA_02", "ITRW_ADDON_MAGICARROW", "ITRW_ADDON_MAGICBOLT", "ITSC_RESSURECT", "ITSC_UNLOCK", "ITSC_ICECUBE"
            };

            names.Insert(itemNames[randomizer.Random(0, itemNames.size() - 1)]);
        }
        
        if (randomizer.Random(0, 1000) > 900) { // 10%
            std::array<zSTRING, 21> itemNames = {
                "ITWR_ADDON_RUNEMAKING_KDW_CIRC1", "ITWR_ADDON_RUNEMAKING_KDW_CIRC2", "ITWR_ADDON_RUNEMAKING_KDW_CIRC3", "ITWR_ADDON_RUNEMAKING_KDW_CIRC4", "ITWR_ADDON_RUNEMAKING_KDW_CIRC5", 
                "ITWR_ADDON_RUNEMAKING_KDF_CIRC1", "ITWR_ADDON_RUNEMAKING_KDF_CIRC2", "ITWR_ADDON_RUNEMAKING_KDF_CIRC3", "ITWR_ADDON_RUNEMAKING_KDF_CIRC4", "ITWR_ADDON_RUNEMAKING_KDF_CIRC5", 
                "ITWR_ADDON_RUNEMAKING_GUR_CIRC1", "ITWR_ADDON_RUNEMAKING_GUR_CIRC2", "ITWR_ADDON_RUNEMAKING_GUR_CIRC3", "ITWR_ADDON_RUNEMAKING_GUR_CIRC4", "ITWR_ADDON_RUNEMAKING_GUR_CIRC5",
                "ITWR_ADDON_RUNEMAKING_DMT_CIRC1", "ITWR_ADDON_RUNEMAKING_DMT_CIRC2", "ITWR_ADDON_RUNEMAKING_DMT_CIRC3", "ITWR_ADDON_RUNEMAKING_DMT_CIRC4", "ITWR_ADDON_RUNEMAKING_DMT_CIRC5", 
                "ITWR_ADDON_RUNEMAKING_PRM"
            };

            auto chosenName = getLootNameIfNotGiven(itemNames[randomizer.Random(0, itemNames.size() - 1)]);
            
            randomLootGiven.Insert(chosenName);

            names.Insert(chosenName);
        }

        if (randomizer.Random(0, 1000) > 950) { // 5%
            std::array<zSTRING, 21> itemNames = {
                "ITBE_ADDON_MIL_01", "ITBE_ADDON_SLD_01", "ITBE_ADDON_NOV_01", "ITBE_ADDON_SEK_01", "ITBE_ADDON_THIEF_01",
                "ITBE_ADDON_THIEF_02", "ITBE_ADDON_STR_10", "ITBE_ADDON_DEX_10", "ITAM_DEX_01", "ITAM_STRG_01", "ITRI_MANA_02", 
            };

            auto chosenName = getLootNameIfNotGiven(itemNames[randomizer.Random(0, itemNames.size() - 1)]);

            randomLootGiven.Insert(chosenName);

            names.Insert(chosenName);
        }

        if (randomizer.Random(0, 1000) > 850) { // 15%
            std::array<zSTRING, 18> itemNames = {
                "ITPO_SPEED_03", "ITPO_HEALTH_01", "ITPO_MANA_01", "ITRW_ADDON_MAGICARROW", 
                "ITRW_EXPLOSIVEBOLT", "ITRW_BOLT", "ITRW_ARROW", "ITFO_BREAD", "ITAT_CLAW", "ITPL_BEET", "ITSC_TRFWOLF", "ITSC_TRFSCAVENGER", "ITSC_SLEEP", "ITPL_MUSHROOM_02", 
                "ITSC_TRFLURKER", "ITSC_TRFSNAPPER"
            };
            
            names.Insert(itemNames[randomizer.Random(0, itemNames.size() - 1)]);
        }
        
        if (randomizer.Random(0, 1000) > 600) { // 40%
            std::array<zSTRING, 33> itemNames = {
                "ITMI_GOLD", "ITPL_BEET", "ITRW_ADDON_MAGICARROW", "ITRW_EXPLOSIVEBOLT", "ITRW_BOLT", "ITRW_ARROW", "ITFO_BEER", "ITFO_APPLE", "ITFO_BREAD", "ITFO_BOOZE", "ITFO_WATER",
                "ITFO_WINE", "ITFO_WINEBERRYS", "ITFO_SCHILDKROETESOUP_SBORKA", "ITFO_ADDON_RUM", "ITFO_ADDON_SHELLFLESH", "ITFO_SMELLYFISH", "ITMI_BRUSH", "ITAT_CLAW", "ITSC_FIREBOLT",
                "ITSC_ICEBOLT", "ITSC_LIGHT", "ITSC_ZAP", "ITSC_DEATHBOLT", "ITSC_SUMWOLF", "ITSC_SUMGOBSKEL", "ITPL_MANA_HERB_01", "ITPL_HEALTH_HERB_01", "ITPL_MUSHROOM_01", "ITPL_BLUEPLANT",
                "ITPL_FORESTBERRY", "ITPL_PLANEBERRY", "ITMI_SNUGGET"
            };

            names.Insert(itemNames[randomizer.Random(0, itemNames.size() - 1)]);
        }

        if (randomizer.Random(0, 1000) > 900) { // 10%
            std::array<zSTRING, 32> itemNames = {
                "ITRU_FIREBOLT",
                "ITRU_ZAP",
                "ITRU_ICEBOLT",
                "ITRU_SLEEP",
                "ITRU_BERZERK",
                "ITRU_DEATHBOLT",
                "ITRU_SUMGOBSKEL",
                "ITRU_SUMWOLF",
            };

            names.Insert(itemNames[randomizer.Random(0, itemNames.size() - 1)]);
        }

        if (randomizer.Random(0, 1000) > 930) { // 7%
            std::array<zSTRING, 11> itemNames = {
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
            };

            names.Insert(itemNames[randomizer.Random(0, itemNames.size() - 1)]);
        }

        if (randomizer.Random(0, 1000) > 960) { // 4%
            std::array<zSTRING, 13> itemNames = {
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
            };

            names.Insert(itemNames[randomizer.Random(0, itemNames.size() - 1)]);
        }

        return names;
    }

    void addRandomLootToNpc (oCNpc* npc) {
        auto lootNames = getRandomLootNames();

        for (size_t j = 0; j < lootNames.GetNumInList(); ++j)
        {
            oCItem* item = static_cast<oCItem*>(ogame->GetGameWorld()->CreateVob_novt(zVOB_TYPE_ITEM, lootNames.GetSafe(j)));

            if (item->HasFlag(ITM_FLAG_MULTI)) {
                auto maxAmount = 10;

                if (IsTooCoolLoot(item)) {
                    maxAmount = 2;
                }

                item->amount = item->GetObjectName().HasWordI("ITPO_NP_STATS") || item->GetObjectName().HasWordI("ITAM") || item->GetObjectName().HasWordI("ITWR")
                    || item->GetObjectName().HasWordI("ITRI") || item->GetObjectName().HasWordI("ITBE") ?
                   1 : randomizer.Random(1, maxAmount);
            }

            npc->PutInInv(item);

            item->Release();
        }
    }

    int AddRandomDrop() {
        oCWorld* world = dynamic_cast<oCWorld*>(ogame->GetWorld());
        auto npcsCount = 0;

        if (world) {
            auto list = world->voblist_npcs;
            for (size_t i = 0; i < list->GetNumInList(); ++i)
            {
                oCNpc* npc = list->Get(i);

                if (npc == oCNpc::player)
                    continue;

                if (RX_IsBoss(npc)) {
                    npcsCount += 1;
                    addRandomLootToNpc(npc);
                    addRandomLootToNpc(npc);
                } else if (randomizer.Random(0, 100) >= 80 ) {
                    npcsCount += 1;
                    addRandomLootToNpc(npc);
                }
            }

            randomLootGiven.DeleteList();
        }

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

        if (inpstr.HasWordI("RDRP")) {
            auto result = AddRandomDrop();
            msg = "Changed drop of: " + Z result + " npcs.";

            return true;
        }

        return false;
    }

    bool chestsRandomizerHandler(const zSTRING& inpstr, zSTRING& msg) {
        if (inpstr.HasWordI("SHUFFLE")) {
            auto result = ShuffleChests();
            msg = "Shuffled container for: " + Z result + " items.";

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
       
        if (inpstr.HasWordI("chestsrandomizer")) {
            return chestsRandomizerHandler(inpstr, msg);
        }

        if (inpstr.HasWordI("herbsrandomizer")) {
            return herbsRandomizerHandler(inpstr, msg);
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
        zcon->Register("weaponsrandomizer RDRP", "Randomize NPCs weapons");
        zcon->Register("chestsrandomizer SHUFFLE", "Shuffles chests content");
        zcon->Register("herbsrandomizer SHUFFLE", "Shuffles hrebs positions");
    }
}