// Supported with union (c) 2020 Union team
// Union SOURCE file

namespace GOTHIC_ENGINE {
	auto const AIV_BOSS = 90;

	auto const EXTRA_LOOT_BASE_CHANCE() {
		return zoptions->ReadInt("PUNCLEVUTILS", "ExtraLootChance", 15);
	}

	auto const EXTRA_LOOT_HP_FACTOR_HORINIS() {
		return zoptions->ReadInt("PUNCLEVUTILS", "ExtraLootHpFactorHorinis", 400);
	}

	auto const EXTRA_LOOT_HP_FACTOR_OTHER() {
		return zoptions->ReadInt("PUNCLEVUTILS", "ExtraLootHpFactorOther", 700);
	}

	auto const EXTRA_LOOT_HP_FACTOR_MULTIPLIER() {
		return zoptions->ReadInt("PUNCLEVUTILS", "ExtraLootHpFactorMultiplier", 25);
	}

	auto const EXTRA_LOOT_HORINIS_FACTOR() {
		return zoptions->ReadInt("PUNCLEVUTILS", "ExtraLootHorinisFactor", 1000);
	}

	auto const EXTRA_LOOT_OTHER_FACTOR() {
		return zoptions->ReadInt("PUNCLEVUTILS", "ExtraLootOtherFactor", 1250);
	}

	auto const EXTRA_LOOT_CHEST_BASE_CHANCE() {
		return zoptions->ReadInt("PUNCLEVUTILS", "ChestsExtraLootChance", 450);
	}

	auto const BASE_STRENGTH_PER_LOOT_MULTIPLIER() {
		return zoptions->ReadInt("PUNCLEVUTILS", "BaseStrengthMultiplierForAddedLoot", 1);
	}

	auto const VALUE_STRENGTH_PER_LOOT_MULTIPLIER() {
		return zoptions->ReadInt("PUNCLEVUTILS", "ValueBasedStrengthMultiplier", 250);
	}

	auto const ENEMY_STATS_PER_MULTIPLIER() {
		return zoptions->ReadInt("PUNCLEVUTILS", "StrengthenEnemyStatsPerMultiplier", 25);
	}

	auto const ENEMY_DEFENCE_PER_MULTIPLIER() {
		return zoptions->ReadInt("PUNCLEVUTILS", "StrengthenEnemyDefencePerMultiplier", 3);
	}

	auto const ENEMY_HP_FACTOR() {
		return zoptions->ReadInt("PUNCLEVUTILS", "StrengthenEnemyBaseHP", 150);
	}
}