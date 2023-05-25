#include <stdio.h>
#include <string.h>

void art(int rand){
    switch (rand){
        case 0:
            printf("/  \\.-\"\"\"-./  \\ \n\\    -   -    / \n |   o   o   | \n \\  .-\'\'\'-.  / \n  \'-\\__Y__/-\' \n     `---`  \n");
        break;

        case 1:
            printf("   .##.                   ,==. \n .#    #.                 \\ o ', \n#        #     _     _     \\    \\ \n#        #    (_)   (_)    /    ; \n '#    #'                 /   .\'  \n   '##'                   \"==\" \n");
        break; 

        case 2: 
            printf("      ____   \n     /___/\\_        \n    _\\   \\/_/\\__     \n  __\\       \\/_/\\      \n  \\   __    __ \\ \\       \n __\\  \\_\\   \\_\\ \\ \\   __   \n/_/\\   __   __  \\ \\_/_/\\    \n\\_\\/_\\__\\/\\__\\/\\__\\/_\\_\\/      \n   \\_\\/_/\\       /_\\_\\/         \n      \\_\\/       \\_\\/          \n") ;
        break;

        case 3:
            printf("           _                         _\n       _==/          i     i          \\==\n     /XX/            |\\___/|            \\XX\\ \n   /XXXX\\            |XXXXX|            /XXXX\\ \n  |XXXXXX\\_         _XXXXXXX_         _/XXXXXX| \n XXXXXXXXXXXxxxxxxxXXXXXXXXXXXxxxxxxxXXXXXXXXXXX \n|XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX| \nXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX \n|XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX| \n XXXXXX/^^^^\"\\XXXXXXXXXXXXXXXXXXXXX/^^^^^\\XXXXXX \n  |XXX|       \\XXX/^^\\XXXXX/^^\\XXX/       |XXX| \n    \\XX\\       \\X/    \\XXX/    \\X/       /XX/ \n       \"\\       \"      \\X/      \"       /\" \n                        ! \n");
        break;

    }

}