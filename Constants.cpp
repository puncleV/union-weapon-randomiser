// Supported with union (c) 2020 Union team
// Union SOURCE file

namespace GOTHIC_ENGINE {
	auto const AIV_BOSS = 90;

	auto const EXTRA_LOOT_BASE_CHANCE() {
		return zoptions->ReadInt("PUNCLEVUTILS", "ExtraLootChance", 15);
	}

	auto const EXTRA_LOOT_CHEST_BASE_CHANCE() {
		return zoptions->ReadInt("PUNCLEVUTILS", "ChestsExtraLootChance", 575);
	}
}