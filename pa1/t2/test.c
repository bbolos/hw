#include <stdio.h>
#include "clist.h"

// Een simpele testfunctie voor map_clist: kwadrateren
int square(int x) {
    return x * x;
}

int main(void) {
    CNode *mijn_lijst = NULL;

    printf("--- Stap 1: Elementen invoegen ---\n");
    // We voegen getallen door elkaar toe om te kijken of insert_cnode ze sorteert
    insert_cnode(&mijn_lijst, 20);
    insert_cnode(&mijn_lijst, 10);
    insert_cnode(&mijn_lijst, 30);
    insert_cnode(&mijn_lijst, 15);
    
    printf("Verwachte output: 10 15 20 30 \n");
    printf("Actuele output:  ");
    print_clist(mijn_lijst);
    printf("\n");

    printf("--- Stap 2: Map functie testen (kwadrateren) ---\n");
    map_clist(mijn_lijst, square);
    
    // Na kwadrateren: 10->100, 15->225, 20->400, 30->900
    printf("Verwachte output: 100 225 400 900 \n");
    printf("Actuele output:  ");
    print_clist(mijn_lijst);
    printf("\n");

    printf("--- Stap 3: Delete functie testen (middelste element) ---\n");
    // We verwijderen 225 (zat in het midden)
    delete_cnode(&mijn_lijst, 225);
    
    printf("Verwachte output: 100 400 900 \n");
    printf("Actuele output:  ");
    print_clist(mijn_lijst);
    printf("\n");

    printf("--- Stap 4: Delete functie testen (kop/kleinste element) ---\n");
    // We verwijderen 100 (waar *clist nu naar hoort te wijzen)
    // Dit test of je clist pointer netjes doorschuift naar 400!
    delete_cnode(&mijn_lijst, 100);
    
    printf("Verwachte output: 400 900 \n");
    printf("Actuele output:  ");
    print_clist(mijn_lijst);
    printf("\n");

    printf("--- Stap 5: Geheugen vrijmaken met free_clist ---\n");
    free_clist(&mijn_lijst);
    
    if (mijn_lijst == NULL) {
        printf("Succes: De lijst is succesvol vrijgemaakt en staat op NULL!\n");
    } else {
        printf("Fout: mijn_lijst is na free_clist niet NULL gemaakt.\n");
    }

    return 0;
}
