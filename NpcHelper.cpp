// Supported with union (c) 2020 Union team
// Union SOURCE file

namespace GOTHIC_ENGINE {
	bool npcCanWearWeapon(oCItem* item, oCNpc* npc) {
        for (size_t i = 0; i < ITM_COND_MAX; i++)
        {
            if (item->cond_atr[i] <= 0 && item->cond_atr[i] >= NPC_ATR_MAX) {
                return false;
            }

            if (npc->attribute[item->cond_atr[i]] < item->cond_value[i])
            {
                return false;
            }
        }

        return true;
	}
}