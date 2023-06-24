// Supported with union (c) 2020 Union team
// Union SOURCE file

namespace GOTHIC_ENGINE {
    int ShuffleHerbs() {

        auto itemsCounter = 0;

        if (ogame->GetGameWorld()) {
            zCArray<zCVob*> arrMob;

            ogame->GetGameWorld()->SearchVobListByBaseClass(oCItem::classDef, arrMob, NULL);

            zCArray<zSTRING> herbNames;
            zCArray<zVEC3> herbPositions;

            for (size_t i = 0; i < arrMob.GetNumInList(); i += 1) {
                auto item = arrMob[i];
                if (item->GetObjectName().StartWith("ITPL") && !item->GetObjectName().HasWordI("BEET") && !item->GetObjectName().HasWordI("SUPER_HERB")) {
                    
                    herbNames.Insert(item->GetObjectName());
                    herbPositions.Insert(item->GetPositionWorld());

                    item->RemoveVobFromWorld();
                    item->Release();
                }
            }

            for (size_t i = 0; i < herbNames.GetNumInList(); i += 1)
            {
                itemsCounter += 1;
                auto herbName = herbNames[i];

                auto herb = ogame->GetGameWorld()->CreateVob_novt(zVOB_TYPE_ITEM, herbName);
                auto positionIndex = randomizer.Random(0, herbPositions.GetNumInList() - 1);
                auto position = herbPositions[positionIndex];

                herb->SetPositionWorld(position);
                ogame->GetGameWorld()->AddVob(herb);
                herb->Release();

                herbPositions.RemoveIndex(positionIndex);
            }
        }

        return itemsCounter;
    }
}