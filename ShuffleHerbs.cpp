// Supported with union (c) 2020 Union team
// Union SOURCE file

namespace GOTHIC_ENGINE {
    int ShuffleHerbs() {

        oCWorld* world = dynamic_cast<oCWorld*>(ogame->GetWorld());
        auto itemsCounter = 0;

        if (world) {
            zCListSort<oCItem>* arrMob = world->voblist_items;
            zCArray<oCItem*> herbsArray;

            for (auto vob = arrMob->GetNextInList(); vob != nullptr; vob = arrMob->GetNextInList()) {
                if (vob->GetData()->GetObjectName().StartWith("ITPL")) {
                    herbsArray.Insert(vob->GetData());
                }
            }

            for (size_t i = 0; i < herbsArray.GetNumInList(); ++i)
            {
                auto herb = herbsArray[i];

                auto secondHerbIndex = randomizer.Random(0, i);
                if (secondHerbIndex == i) {
                    continue;
                }

                auto secondHerb = herbsArray[secondHerbIndex];
                zVEC3 firstHerbPosition = herb->GetPositionWorld();
                herb->SetPositionWorld(secondHerb->GetPositionWorld());
                secondHerb->SetPositionWorld(firstHerbPosition);
            }
        }

        return itemsCounter;
    }
}