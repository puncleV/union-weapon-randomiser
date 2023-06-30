// Supported with union (c) 2020 Union team
// Union SOURCE file

namespace GOTHIC_ENGINE {
    int ShuffleChests() {
        oCWorld* world = dynamic_cast<oCWorld*>(ogame->GetWorld());
        auto itemsCounter = 0;

        if (world) {
            zCArray<zCVob*> arrMob;

            world->SearchVobListByClass(oCMobContainer::classDef, arrMob, NULL);

            for (size_t i = 0; i < arrMob.GetNumInList(); ++i)
            {
                oCMobContainer* firstChest = dynamic_cast<oCMobContainer*> (arrMob[i]);

                auto secondChestIndex = randomizer.Random(0, i);
                
                if (secondChestIndex == i) {
                    continue;
                }

                oCMobContainer* secondChest = dynamic_cast<oCMobContainer*> (arrMob[secondChestIndex]);
                zCArray <oCItem*> firstChestItems;
                zCArray <oCItem*> secondChestItems;

                if (firstChest->containList.GetNumInList() == 0 || secondChest->containList.GetNumInList() == 0) {
                    continue;
                }

                for (size_t j = 0; j < firstChest->containList.GetNumInList(); ++j) {
                    if (IsQuestItem(firstChest->containList[j]) || IsIgnoredOrTestItem(firstChest->containList[j])) {
                        continue;
                    }

                    firstChestItems.Insert(firstChest->containList[j]);
                    firstChest->Remove(firstChest->containList[j]);
                    itemsCounter += 1;
                }

                for (size_t j = 0; j < secondChest->containList.GetNumInList(); ++j) {
                    if (IsQuestItem(secondChest->containList[j]) || IsIgnoredOrTestItem(secondChest->containList[j])) {
                        continue;
                    }

                    secondChestItems.Insert(secondChest->containList[j]);
                    secondChest->Remove(secondChest->containList[j]);
                    itemsCounter += 1;
                }

                for (size_t j = 0; j < firstChestItems.GetNumInList(); ++j) {
                    secondChest->Insert(firstChestItems[j]);
                }

                for (size_t j = 0; j < secondChestItems.GetNumInList(); ++j) {
                    firstChest->Insert(secondChestItems[j]);
                }

                firstChestItems.DeleteList();
                secondChestItems.DeleteList();
            }
        }

        return itemsCounter;
    }

    void addRandomLootToChest(oCMobContainer* chest, bool shouldAddToPlaer = false) {
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

            if (shouldAddToPlaer) {
                player->PutInInv(item);
            }
            else {
                chest->Insert(item);
            }

            item->Release();
        }
    }

    int AddChestsLoot(bool shouldAddToPlaer = false) {
        oCWorld* world = dynamic_cast<oCWorld*>(ogame->GetWorld());
        auto itemsCounter = 0;

        if (world) {
            zCArray<zCVob*> arrMob;

            world->SearchVobListByClass(oCMobContainer::classDef, arrMob, NULL);

            for (size_t i = 0; i < arrMob.GetNumInList(); ++i)
            {
                oCMobContainer* firstChest = dynamic_cast<oCMobContainer*> (arrMob[i]);

                if (randomizer.Random(0, 1000) >= 1000 - EXTRA_LOOT_CHEST_BASE_CHANCE()) {
                    addRandomLootToChest(firstChest, shouldAddToPlaer);
                    itemsCounter += 1;
                }
            }
        }

        return itemsCounter;
    }
}