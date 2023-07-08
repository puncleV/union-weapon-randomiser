instance dia_mana_regen_punclev(c_info) {
    npc = 39061;
    nr = 2;
    condition = dia_mana_regen_punclev_condition;
    information = dia_mana_regen_punclev_info;
    permanent = true;
    important = false;
    description = "Manaregen (12lp, 10000 gold)";
};

func int dia_mana_regen_punclev_condition() {
    return !vatras_teachregenmana;
};

func void dia_mana_regen_punclev_info() {
   rx_teachregenmana();
};