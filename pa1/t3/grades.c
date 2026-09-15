#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
    //geen input
    if (argc < 2){
        printf("Usage: ./grades [grade1 grade2 ...] OR ./grades --interactive\n");
        return 0;
    }

    //wel input
    //interactive
    if (strcmp(argv[1], "--interactive") == 0){
        printf("Enter grades (enter -1 to stop): ");

        //lees alle input tot -1
        double cijfer;
        double som = 0;
        int aantal = 0;

        while (scanf("%lf", &cijfer) == 1 && cijfer != -1){
            som += cijfer;
            aantal++;
        }

        //bekijk en bereken uitkomst
        if (aantal == 0){
            printf("No grades entered.\n");
            return 0;
        }

        printf("Average grade: %.2f\n", som / aantal);
    }
    //commandline
    else{
        //sommeer alles en deel door lengte aantal cijfers
        double som = 0;
        for (int i = 1; i < argc; i++){
            som += atof(argv[i]);
        }
        printf("Average grade: %f\n", som / (argc - 1));
    }

    return 0;
}
