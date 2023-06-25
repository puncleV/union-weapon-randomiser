// Supported with union (c) 2020 Union team
// Union SOURCE file

#include <array>
namespace GOTHIC_ENGINE {

    template<std::size_t SIZE> class Loot {
    private:
        std::array <zSTRING, SIZE> possibleLootNames;
        int chanceWeight;
        int chanceUpperbound;
    public:
        bool shouldDeduplicate;

        Loot(int _chanceWeight, int _chanceUpperbound, bool _shouldDeduplicate, std::array <zSTRING, SIZE> _possibleLootNames) {
            possibleLootNames = _possibleLootNames;
            chanceWeight = _chanceWeight;
            chanceUpperbound = _chanceUpperbound;
            shouldDeduplicate = _shouldDeduplicate;
        };

        zSTRING pick() {
            if (randomizer.Random(0, chanceUpperbound) <= chanceWeight) {
                for (;;) {
                    // i am too lazy to find a way to work with different sized arrays in loot table so here we are.
                    auto element = randomizer.getRandomArrayElement<SIZE>(possibleLootNames);

                    if (element != "") {
                        return element;
                    }
                }
            }

            return "";
        };
    };
}