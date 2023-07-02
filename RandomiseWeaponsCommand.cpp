// Supported with union (c) 2020 Union team
// Union SOURCE file
namespace GOTHIC_ENGINE {
    int (*innerEvalFunc)(const zSTRING&, zSTRING&);

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

    int RandomiseRangedWeapons(int extraWeaponsPercent = 0) {
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

        return false;
    }

    bool lootRandomizerHandler(const zSTRING& inpstr, zSTRING& msg) {
        if (inpstr.HasWordI("ADD")) {
            auto result = AddRandomLoot(inpstr.HasWordI("ADD_TO_PLAYER"));
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

        if (inpstr.HasWordI("ADD")) {
            auto result = AddChestsLoot(inpstr.HasWordI("ADD_TO_PLAYER"));

            msg = "Added: " + Z result + " items.";

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

        if (inpstr.HasWordI("lootrandomizer")) {
            return lootRandomizerHandler(inpstr, msg);
        }
       
        if (inpstr.HasWordI("chestsrandomizer")) {
            return chestsRandomizerHandler(inpstr, msg);
        }

        if (inpstr.HasWordI("herbsrandomizer")) {
            return herbsRandomizerHandler(inpstr, msg);
        }

        if (inpstr.HasWordI("punclevutils")) {
            RandomiseMeleeWeapons();
            RandomiseRangedWeapons(30);
            ShuffleChests();
            AddChestsLoot();
            ShuffleHerbs();
            AddRandomLoot();

            msg = "Executed all commands succesfully";
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
        zcon->Register("weaponsrandomizer MELEEWPNS", "Randomize NPCs melee weapons");
        zcon->Register("weaponsrandomizer RANGEDWPNS", "Randomize NPCs ranged weapons");
        zcon->Register("lootrandomizer ADD", "Randomize NPCs weapons");
        zcon->Register("chestsrandomizer SHUFFLE", "Shuffles chests content");
        zcon->Register("chestsrandomizer ADD", "Add chests content");
        zcon->Register("herbsrandomizer SHUFFLE", "Shuffles hrebs positions");
        zcon->Register("punclevutils all", "Execute all commands at once");
    }
}