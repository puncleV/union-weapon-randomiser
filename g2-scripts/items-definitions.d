instance itpo_np_stats_traders(c_item) {
    name = "Elixir of POWER";
    mainflag = item_kat_potions;
    flags = item_multi | item_mission;
    value = 15777;
    visual = "ITPO_MAGIC_02.3ds";
    material = mat_glas;
    on_state = use_itpo_np_stats;
    scemename = "POTIONFAST";
    wear = wear_effect;
    description = "Elixir of POWER";
    text[1] = name_bonus_str;
    count[1] = 2;
    text[2] = name_bonus_dex;
    count[2] = 2;
    text[3] = name_bonus_manamax;
    count[3] = 5;
    text[5] = name_value;
    count[5] = value;
    inv_animate = 1;
    setitemvartrue(itpo_np_stats, bit_item_no_hotbar);
};

instance itpo_firedefence_traders(c_item) {
    name = "Fire Elixir";
    mainflag = item_kat_potions;
    flags = item_mission | item_multi;
    value = 7000;
    visual = "ITPO_MAGIE_01_EX.3ds";
    material = mat_glas;
    on_state = use_itpo_firedefence;
    scemename = "POTIONFAST";
    wear = wear_effect;
    description = "Fire Elixir";
    text[1] = name_prot_fire;
    count[1] = 2;
    text[4] = "";
    text[5] = name_value;
    count[5] = value;
    inv_animate = 1;
    setitemvartrue(itpo_firedefence, bit_item_no_hotbar);
};

instance itpo_magdefence_traders(c_item) {
    name = "Magic protection";
    mainflag = item_kat_potions;
    flags = item_multi | item_mission;
    value = 7000;
    visual = "ITPO_MAGIE_02_EX.3ds";
    material = mat_glas;
    on_state = use_itpo_magdefence;
    scemename = "POTIONFAST";
    wear = wear_effect;
    description = "Magic protection";
    text[1] = name_prot_magic;
    count[1] = 2;
    text[4] = "";
    text[5] = name_value;
    count[5] = value;
    inv_animate = 1;
    setitemvartrue(itpo_magdefence, bit_item_no_hotbar);
};

instance itpo_amunsu_traders(c_item) {
    name = "Amun-su";
    mainflag = item_kat_potions;
    flags = item_multi | item_mission;
    value = 6500;
    visual = "ITPO_PERM_DEX_EX.3DS";
    material = mat_glas;
    on_state = useitpo_itpo_amunsu;
    scemename = "POTIONFAST";
    wear = wear_effect;
    description = "Amun-su";
    text[1] = name_bonus_manamax;
    count[1] = 8;
    text[4] = "";
    text[5] = name_value;
    count[5] = value;
    inv_animate = 1;
    setitemvartrue(itpo_amunsu, bit_item_no_hotbar);
};

instance itpo_intellect_traders(c_item) {
    name = "Elixir of intellect";
    mainflag = item_kat_potions;
    flags = item_multi | item_mission;
    value = 4000;
    visual = "ITPO_PERM_DEX_EX.3DS";
    material = mat_glas;
    on_state = use_itpo_intellect;
    scemename = "POTIONFAST";
    wear = wear_effect;
    description = "Elixir of intellect";
    text[1] = name_bonus_int;
    count[1] = 2;
    text[4] = "";
    text[5] = name_value;
    count[5] = value;
    inv_animate = 1;
    setitemvartrue(itpo_intellect, bit_item_no_hotbar);
};

instance itpo_rarepotion_01_traders(c_item) {
    name = "Elixir of Magic";
    mainflag = item_kat_potions;
    flags = item_mission | item_multi;
    value = 1750;
    visual = "ITPO_BLACK_EX.3ds";
    material = mat_glas;
    on_state = use_itpo_rarepotion_01;
    scemename = "POTIONFAST";
    wear = wear_effect;
    description = name;
    text[3] = "+200 mana";
    text[4] = "For 15 minutes";
    text[5] = name_value;
    count[5] = value;
    inv_animate = 1;
    setitemvartrue(itpo_rarepotion_01, bit_item_nowisp);

};
instance itpo_rarepotion_02_traders(c_item) {
    name = "Elixir of power";
    mainflag = item_kat_potions;
    flags = item_mission | item_multi;
    value = 1750;
    visual = "ITPO_BLACK_EX.3ds";
    material = mat_glas;
    on_state = use_itpo_rarepotion_02;
    scemename = "POTIONFAST";
    wear = wear_effect;
    description = name;
    text[3] = "Physical dmg +20%.";
    text[4] = "For 15 minutes";
    text[5] = name_value;
    count[5] = value;
    inv_animate = 1;
    setitemvartrue(itpo_rarepotion_02, bit_item_nowisp);
};
instance itpo_rarepotion_03_traders(c_item) {
    name = "Elixir of protection";
    mainflag = item_kat_potions;
    flags = item_mission | item_multi;
    value = 2350;
    visual = "ITPO_BLACK_EX_2.3ds";
    material = mat_glas;
    on_state = use_itpo_rarepotion_03;
    scemename = "POTIONFAST";
    wear = wear_effect;
    description = name;
    text[3] = "Absorb 20% dmg";
    text[4] = "For 15 minutes";
    text[5] = name_value;
    count[5] = value;
    inv_animate = 1;
    setitemvartrue(itpo_rarepotion_03, bit_item_nowisp);

};
instance itpo_rarepotion_04_traders(c_item) {
    name = "Elixir of the runner";
    mainflag = item_kat_potions;
    flags = item_mission | item_multi;
    value = 750;
    visual = "ITPO_BLACK_EX.3ds";
    material = mat_glas;
    on_state = use_itpo_rarepotion_04;
    scemename = "POTIONFAST";
    wear = wear_effect;
    description = name;
    text[3] = "Endurance +15 per sec.";
    text[4] = "For 15 minutes";
    text[5] = name_value;
    count[5] = value;
    inv_animate = 1;
    setitemvartrue(itpo_rarepotion_04, bit_item_nowisp);

};
instance itpo_rarepotion_05_traders(c_item) {
    name = "Elixir of Mana Regen";
    mainflag = item_kat_potions;
    flags = item_mission | item_multi;
    value = 3350;
    visual = "ITPO_BLACK_EX.3ds";
    material = mat_glas;
    on_state = use_itpo_rarepotion_05;
    scemename = "POTIONFAST";
    wear = wear_effect;
    description = name;
    text[3] = "+50 mana per sec.";
    text[4] = "For 15 minutes";
    text[5] = name_value;
    count[5] = value;
    inv_animate = 1;
    setitemvartrue(itpo_rarepotion_05, bit_item_nowisp);
};
instance itpo_rarepotion_06_traders(c_item) {
    name = "Elixir of Dodge";
    mainflag = item_kat_potions;
    flags = item_mission | item_multi;
    value = 2350;
    visual = "ITPO_BLACK_EX.3ds";
    material = mat_glas;
    on_state = use_itpo_rarepotion_06;
    scemename = "POTIONFAST";
    wear = wear_effect;
    description = name;
    text[3] = "Dodge chance 50%.";
    text[4] = "For 15 minutes";
    text[5] = name_value;
    count[5] = value;
    inv_animate = 1;
    setitemvartrue(itpo_rarepotion_06, bit_item_nowisp);
};
instance itpo_rarepotion_07_traders(c_item) {
    name = "Elixir of HP regen";
    mainflag = item_kat_potions;
    flags = item_mission | item_multi;
    value = 3350;
    visual = "ITPO_BLACK_EX.3ds";
    material = mat_glas;
    on_state = use_itpo_rarepotion_07;
    scemename = "POTIONFAST";
    wear = wear_effect;
    description = name;
    text[3] = "3% HP per second.";
    text[4] = "For 15 minutes";
    text[5] = name_value;
    count[5] = value;
    inv_animate = 1;
    setitemvartrue(itpo_rarepotion_07, bit_item_nowisp);
};
instance itpo_rarepotion_08_traders(c_item) {
    name = "Elixir of Speed";
    mainflag = item_kat_potions;
    flags = item_mission | item_multi;
    value = 550;
    visual = "ITPO_BLACK_EX.3ds";
    material = mat_glas;
    on_state = use_itpo_rarepotion_08;
    scemename = "POTIONFAST";
    wear = wear_effect;
    description = name;
    text[3] = "Speed +50%.";
    text[4] = "For 15 minutes";
    text[5] = name_value;
    count[5] = value;
    inv_animate = 1;
    setitemvartrue(itpo_rarepotion_08, bit_item_nowisp);
};

instance itpo_megadrink_traders(c_item) {
    name = "Firgasto";
    mainflag = item_kat_potions;
    flags = item_multi | item_mission;
    value = 13500;
    visual = "ITPO_MAGIE_02_EX.3ds";
    material = mat_glas;
    on_state = useitpo_megadrink;
    scemename = "POTIONFAST";
    wear = wear_effect;
    description = "Firgasto";
    text[4] = "Dangerous drink! Or not...";
    text[5] = name_value;
    count[5] = value;
    inv_animate = 1;
    setitemvartrue(itpo_megadrink, bit_item_no_hotbar);
};

func void use_itpo_rarepotion_01() {
    use_itpo_rarepotion_01_old();
    
    if(self.id == 0) {
        rarepotion_01_numofsec += 300;
    };
};

func void use_itpo_rarepotion_02() {
    use_itpo_rarepotion_02_old();
    
    if(self.id == 0) {
        rarepotion_02_numofsec += 300;
    };
};

func void use_itpo_rarepotion_03() {
    use_itpo_rarepotion_03_old();
    
    if(self.id == 0) {
        rarepotion_03_numofsec += 300;
    };
};

func void use_itpo_rarepotion_04() {
    use_itpo_rarepotion_04_old();
    
    if(self.id == 0) {
        rarepotion_04_numofsec += 300;
    };
};

func void use_itpo_rarepotion_05() {
    use_itpo_rarepotion_05_old();
    
    if(self.id == 0) {
        rarepotion_05_numofsec += 300;
    };
};

func void use_itpo_rarepotion_06() {
    use_itpo_rarepotion_06_old();
    
    if(self.id == 0) {
        rarepotion_06_numofsec += 300;
    };
};

func void use_itpo_rarepotion_07() {
    use_itpo_rarepotion_07_old();
    
    if(self.id == 0) {
        rarepotion_07_numofsec += 300;
    };
};

func void use_itpo_rarepotion_08() {
    use_itpo_rarepotion_08_old();
    
    if(self.id == 0) {
        rarepotion_08_numofsec += 300;
    };
};