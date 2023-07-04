func int rx_canlearnmagiccirclenext(var int circle) {
    if(Menu_ReadInt("PUNCLEVUTILS", "IgnoreChapterRequirementsForMagic") == 0) {
        return rx_canlearnmagiccirclenext_old(circle);
    }

    if(circle == 1) {
        return true;
    };

    if(rx_heroismage()) {
        if((kapitel >= 2) && (circle == 2)) {
            return true;
        }
        if((circle == 2) && (hero.attribute[3] >= 150)) {
            return true;
        };
        if((circle == 3) && (kapitel >= 3)) {
            return true;
        };
        if((circle == 3) && (hero.attribute[3] >= 350)) {
            return true;
        };
        if((circle == 4) && (kapitel >= 4)) {
            return true;
        };
        if((circle == 4) && (hero.attribute[3] >= 666)) {
            return true;
        };
        if((circle == 5) && (kapitel >= 5)) {
            return true;
        };
        if((circle == 5) && (hero.attribute[3] >= 850)) {
            return true;
        };
        if((circle == 6) && (kapitel >= 5)) {
             return true;
        };
        if((circle == 6) && (hero.attribute[3] >= 1100)) {
            return true;
        };
    }
    else if((circle == 1) && (kapitel >= 1)) {
        return true;
    };
    
    if((circle == 2) && (kapitel >= 2)) {
        return true;
    };
    
    if((circle == 3) && (kapitel >= 3)) {
        return true;
    };

    return false;
};
