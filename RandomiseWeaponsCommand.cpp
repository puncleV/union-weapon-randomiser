// Supported with union (c) 2020 Union team
// Union SOURCE file

namespace GOTHIC_ENGINE {
    int (*innerEvalFunc)(const zSTRING&, zSTRING&);
  

    int RandomiseWeapons() {
        auto meleeWeaponsList = getMeleeWeaponsList();
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

                for (;;) {
                    int weaponId = meleeWeaponsList[randomizer.Random(0, meleeWeaponsList.GetNumInList())];
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

                            item->Release();
                        }

                       

                        break;
                    }
                }

                auto equippedRangedItem = npc->GetEquippedRangedWeapon();
                if (equippedRangedItem != nullptr || randomizer.Random(0, 100) >= 50) {
                    for (;;) {
                        int weaponId = rangedWeaponsList[randomizer.Random(0, rangedWeaponsList.GetNumInList())];
                        oCItem* item = static_cast<oCItem*>(ogame->GetGameWorld()->CreateVob(zVOB_TYPE_ITEM, weaponId));

                        if (npcCanWearWeapon(item, npc)) {
                            npcsCount += 1;
                            // apparantely you dont need to delete existing item :D
                            npc->PutInInv(item);
                            npc->EquipItem(item);

                            item->Release();

                            break;
                        }
                    }
                }
            }
        }

        meleeWeaponsList.DeleteList();
        rangedWeaponsList.DeleteList();

        return npcsCount;
    }

    zSTRING getRandomLootName() {
        auto randomNumber = randomizer.Random(0, 1000);
        zCArray<zSTRING> names;

        if (randomNumber > 950) { // 5%
            names.Insert("ITMI_POTIONPERMBLANK");
            names.Insert("ITPO_INTELLECT");
            names.Insert("ITRI_ORE_DIAM");
            names.Insert("ITRI_ORE_EMER");
            names.Insert("ITRI_ORE_SAPP");
            names.Insert("ITRI_ORE_OPAL");
            names.Insert("ITRI_ORE_TOPA");
            names.Insert("ITRI_ORE_RUBY");
            names.Insert("ITPO_ELIXIRSHADOW");
            names.Insert("ITPO_HEALTH_03");
            names.Insert("ITPO_HEALTH_03");
            names.Insert("ITPO_MANA_03");
            names.Insert("ITPO_MANA_03");
            names.Insert("ITMI_GOLD"); 
            names.Insert("ITRW_ADDON_MAGICARROW");
            names.Insert("ITRW_EXPLOSIVEBOLT");
            names.Insert("ITRW_BOLT");
            names.Insert("ITRW_ARROW");
            names.Insert("ITSC_TRFDRAGONSNAPPER");
        }
        else if (randomNumber > 860) { // 9%
            names.Insert("ITFO_CAKE_MUSHROOM");
            names.Insert("ITFO_CAKE_FISH");
            names.Insert("ITFO_CAKE_APPLE");
            names.Insert("ITFO_CAKE_MEAT");
            names.Insert("ITFO_CAKE_HONEY");
            names.Insert("ITFO_EALBALZAM");
            names.Insert("ITFO_EALBALZAMTWO");
            names.Insert("ITMI_TOPAZ");
            names.Insert("ITMI_OPAL");
            names.Insert("ITMI_EMERALD");
            names.Insert("ITMI_SAPPHIRE");
            names.Insert("ITMI_RUBY");
            names.Insert("ITMI_DIAMOND");
            names.Insert("ITMI_GOLD");
            names.Insert("ITPL_PERM_HERB");
            names.Insert("ITMI_JEWELERYCHEST");
            names.Insert("ITPO_HEALTH_02");
            names.Insert("ITPO_MANA_02");
            names.Insert("ITRW_ADDON_MAGICARROW");
            names.Insert("itrw_addon_magicbolt");
            names.Insert("ITMI_GOLD");
            names.Insert("ITMI_GOLD");
            names.Insert("ITMI_GOLD");
        }
        else if (randomNumber > 750) { // 11%
            names.Insert("ITRI_GOLD_DIAM");
            names.Insert("ITRI_GOLD_EMER");
            names.Insert("ITRI_GOLD_SAPP");
            names.Insert("ITRI_GOLD_OPAL");
            names.Insert("ITRI_GOLD_TOPA");
            names.Insert("ITRI_GOLD_RUBY");
            names.Insert("ITRI_STEEL_DIAM");
            names.Insert("ITRI_STEEL_EMER");
            names.Insert("ITRI_STEEL_SAPP");
            names.Insert("ITRI_STEEL_OPAL");
            names.Insert("ITRI_STEEL_TOPA");
            names.Insert("ITRI_STEEL_RUBY");
            names.Insert("ITRI_NEW_OREMASTER");
            names.Insert("ITRI_NEW_MANAREGEN");
            names.Insert("ITRI_HP_PARLAN");
            names.Insert("ITPO_NP_MANAREG2");
            names.Insert("ITPO_NP_MANAREG2");
            names.Insert("ITPO_NP_STAMINA");
            names.Insert("ITPO_NP_STAMINA");
            names.Insert("ITPO_HEALTH_02");
            names.Insert("ITPO_MANA_02");
            names.Insert("ITMI_GOLD");
            names.Insert("ITMI_GOLD");
            names.Insert("ITMI_GOLD");
            names.Insert("ITRW_ADDON_MAGICARROW");
            names.Insert("itrw_addon_magicbolt");
            names.Insert("ITSC_UNLOCK");
            names.Insert("ITSC_UNLOCK");
            names.Insert("ITSC_ICECUBE");
            names.Insert("ITSC_ICECUBE");
        }
        else if (randomNumber > 550) { // 20%
            names.Insert("ITPO_HEALTH_01");
            names.Insert("ITPO_MANA_01");
            names.Insert("ITBE_ADDON_THIEF_02");
            names.Insert("ITBE_ADDON_STR_10");
            names.Insert("ITMI_GOLD");
            names.Insert("ITFO_FISH");
            names.Insert("ITMI_GOLD");
            names.Insert("ITMI_GOLD");
            names.Insert("ITMI_GOLD");
            names.Insert("ITPO_SPEED_03");
            names.Insert("ITPO_SPEED_02");
            names.Insert("ITPO_SPEED_01");
            names.Insert("ITMI_JEWELERYCHEST");
            names.Insert("ITAT_CLAW");
            names.Insert("ITPL_BEET");
            names.Insert("ITSC_TRFLURKER");
            names.Insert("ITSC_TRFSNAPPER");
        }
        else if (randomNumber > 300) { //25%
            names.Insert("ITPO_SPEED_03");
            names.Insert("ITMI_JEWELERYCHEST");
            names.Insert("ITBE_ADDON_THIEF_01");
            names.Insert("ITWR_ADDON_RUNEMAKING_KDW_CIRC1");
            names.Insert("ITWR_ADDON_RUNEMAKING_KDW_CIRC2");
            names.Insert("ITWR_ADDON_RUNEMAKING_KDW_CIRC3");
            names.Insert("ITWR_ADDON_RUNEMAKING_KDW_CIRC4");
            names.Insert("ITWR_ADDON_RUNEMAKING_KDW_CIRC5");
            names.Insert("ITWR_ADDON_RUNEMAKING_KDF_CIRC1");
            names.Insert("ITWR_ADDON_RUNEMAKING_KDF_CIRC2");
            names.Insert("ITWR_ADDON_RUNEMAKING_KDF_CIRC3");
            names.Insert("ITWR_ADDON_RUNEMAKING_KDF_CIRC4");
            names.Insert("ITWR_ADDON_RUNEMAKING_KDF_CIRC5");
            names.Insert("ITWR_ADDON_RUNEMAKING_GUR_CIRC1");
            names.Insert("ITWR_ADDON_RUNEMAKING_GUR_CIRC2");
            names.Insert("ITWR_ADDON_RUNEMAKING_GUR_CIRC3");
            names.Insert("ITWR_ADDON_RUNEMAKING_GUR_CIRC4");
            names.Insert("ITWR_ADDON_RUNEMAKING_GUR_CIRC5");
            names.Insert("ITWR_ADDON_RUNEMAKING_DMT_CIRC1");
            names.Insert("ITWR_ADDON_RUNEMAKING_DMT_CIRC2");
            names.Insert("ITWR_ADDON_RUNEMAKING_DMT_CIRC3");
            names.Insert("ITWR_ADDON_RUNEMAKING_DMT_CIRC4");
            names.Insert("ITWR_ADDON_RUNEMAKING_DMT_CIRC5");
            names.Insert("ITPO_HEALTH_01");
            names.Insert("ITPO_MANA_01");
            names.Insert("ITMI_GOLD");
            names.Insert("ITRW_ADDON_MAGICARROW");
            names.Insert("ITRW_EXPLOSIVEBOLT");
            names.Insert("ITRW_BOLT");
            names.Insert("ITRW_ARROW");
            names.Insert("ITFO_BREAD");
            names.Insert("ITAT_CLAW");
            names.Insert("ITPL_BEET");
            names.Insert("ITSC_TRFWOLF");
            names.Insert("ITSC_TRFSCAVENGER");
        }
        else { // 30%
            names.Insert("ITMI_GOLD");
            names.Insert("ITPL_BEET");
            names.Insert("ITRW_ADDON_MAGICARROW");
            names.Insert("ITRW_EXPLOSIVEBOLT");
            names.Insert("ITRW_BOLT");
            names.Insert("ITRW_ARROW");
            names.Insert("ITFO_BEER");
            names.Insert("ITFO_WATER");
            names.Insert("ITMI_BRUSH");
            names.Insert("ITAT_CLAW");
        }

        auto name = names[randomizer.Random(0, names.GetNumInList())];

        names.DeleteList();

        return name;
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

                auto shouldAddSomething = randomizer.Random(0, 100) >= 90;

                if (shouldAddSomething) {
                    npcsCount += 1;

                    do {
                        oCItem* item = static_cast<oCItem*>(ogame->GetGameWorld()->CreateVob_novt(zVOB_TYPE_ITEM, getRandomLootName()));

                        if (item->HasFlag(ITM_FLAG_MULTI)) {
                            auto maxAmount = 10;

                            if (IsTooCoolLoot(item)) {
                                maxAmount = item->GetObjectName().HasWordI("ITRI") || item->GetObjectName().HasWordI("ITBE") ? 1 : 2;
                            }

                            item->amount = randomizer.Random(1, maxAmount);
                        }

                        npc->PutInInv(item);
                        item->Release();
                    } while (randomizer.Random(0, 100) >= 70);
                }
            }
        }

        return npcsCount;
    }

    int ConsoleEvalFunc(const zSTRING& inpstr, zSTRING& msg) {
        if (innerEvalFunc && innerEvalFunc(inpstr, msg))
            return true;

       
        if (inpstr.HasWord("RWPNS")) {
            auto result = RandomiseWeapons();
            msg = "Changed weapons of: " + Z result + " npcs.";

            return true;
        }

        if (inpstr.HasWord("RDRP")) {
            auto result = AddRandomDrop();
            msg = "Changed drop of: " + Z result + " npcs.";

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
        zcon->Register("weaponsrandomizer RWPNS", "Randomize NPCs weapons");
        zcon->Register("weaponsrandomizer RDRP", "Randomize NPCs weapons");
    }
}