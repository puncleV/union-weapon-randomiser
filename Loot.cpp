// Supported with union (c) 2020 Union team
// Union SOURCE file

#include <array>
namespace GOTHIC_ENGINE {

    class Loot {
    private:
        std::vector <zSTRING> possibleLootNames;
        int chanceWeight;
        int chanceUpperbound;
    public:
        bool shouldDeduplicate;

        Loot(int _chanceWeight, int _chanceUpperbound, bool _shouldDeduplicate, std::vector <zSTRING> _possibleLootNames) {
            possibleLootNames = _possibleLootNames;
            chanceWeight = _chanceWeight;
            chanceUpperbound = _chanceUpperbound;
            shouldDeduplicate = _shouldDeduplicate;
        };

        zSTRING pick() {
            if (randomizer.Random(0, chanceUpperbound) <= chanceWeight) {
                auto element = possibleLootNames[randomizer.Random(0, possibleLootNames.size() - 1)];;

                if (element != "") {
                    return element;
                }
            }

            return "";
        };
    };
}