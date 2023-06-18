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
                        npc->UnequipItem(equippedWeapon);
                       
                        if (!IsIgnoredOrTestItem(equippedWeapon)) {
                            npc->RemoveFromInv(equippedWeapon, 1);
                        }

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

                                if (!IsIgnoredOrTestItem(equippedRangedItem)) {
                                    npc->RemoveFromInv(equippedRangedItem, 1);
                                }
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