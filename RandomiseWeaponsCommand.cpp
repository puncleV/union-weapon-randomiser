// Supported with union (c) 2020 Union team
// Union SOURCE file

namespace GOTHIC_ENGINE {
    int (*innerEvalFunc)(const zSTRING&, zSTRING&);

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

            if (symbol->type != zPAR_TYPE_INSTANCE) {
                continue;
            }

            //  Instance isn't global scope
            if (symbol->name.HasWord(".")) {
                continue;
            }

            auto baseClass = parser->GetBaseClass(symbol);

            // Symbol isn't a item class
            if (baseClass != c_item) {
                continue;
            }

            oCItem* item = static_cast<oCItem*>(ogame->GetGameWorld()->CreateVob(zVOB_TYPE_ITEM, i));

            if (item->mainflag != ITM_CAT_NF) {
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

            if (symbol->type != zPAR_TYPE_INSTANCE) {
                continue;
            }

            //  Instance isn't global scope
            if (symbol->name.HasWord(".")) {
                continue;
            }

            auto baseClass = parser->GetBaseClass(symbol);

            // Symbol isn't a item class
            if (baseClass != c_item) {
                continue;
            }

            oCItem* item = static_cast<oCItem*>(ogame->GetGameWorld()->CreateVob(zVOB_TYPE_ITEM, i));

            if (item->mainflag != ITM_CAT_FF) {
                continue;
            }
  
            item->Release();

            weapons_list.Insert(i);
        }

        return weapons_list;
    }
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
                        npc->UnequipItem(equippedWeapon);
                        npc->RemoveFromInv(equippedWeapon, 1);

                        npc->PutInInv(item);
                        npc->EquipItem(item);

                        item->Release();

                        break;
                    }
                }

                auto equippedRangedItem = npc->GetEquippedRangedWeapon();
                if (equippedRangedItem != nullptr || randomizer.Random(0, 100) >= 70) {
                    for (;;) {
                        int weaponId = rangedWeaponsList[randomizer.Random(0, rangedWeaponsList.GetNumInList())];
                        oCItem* item = static_cast<oCItem*>(ogame->GetGameWorld()->CreateVob(zVOB_TYPE_ITEM, weaponId));

                        if (npcCanWearWeapon(item, npc)) {
                            npcsCount += 1;

                            if (equippedRangedItem != nullptr) {
                                npc->UnequipItem(equippedRangedItem);
                                npc->RemoveFromInv(equippedRangedItem, 1);
                            }

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

    int ConsoleEvalFunc(const zSTRING& inpstr, zSTRING& msg) {
        if (innerEvalFunc && innerEvalFunc(inpstr, msg))
            return true;

       
        if (inpstr.HasWord("RWPNS")) {
            auto result = RandomiseWeapons();
            msg = "Changed weapons of: " + Z result + " npcs.";

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
    }
}