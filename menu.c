#include <stdio.h>

void menu(int* g, int* u)
{
	printf("\n\n");
	printf("---------------------------- \n");
    printf("Hello Player 1\n");
	printf("Gold: %d; %d units\n", *g, *u);
    printf("Choose your desired action:\n");
	printf("---------------------------- \n");
    printf("- train a Knight (type K and hit Return)\n");
	printf("- train a Swordsman (type S and hit Return)\n");
	printf("- train an Archer (type A and hit Return)\n");
	printf("- train a Pikeman (type P and hit Return)\n");
	printf("- produce a Ram (type R and hit Return)\n");
	printf("- produce a Catapult (type C and hit Return)\n");
    printf("- train a Worker (type W and hit Return)\n\n");

	printf("- move unit (type MOVE and hit Return)\n");
	printf("- attack enemy unit (type ATTACK and hit Return)\n");

    printf("- display map (type MAP and hit Return)\n");
    printf("- display list of units on the map (type LIST and hit Return)\n\n");

	printf("- end your move (type SAVE and hit Return)\n");
	printf("- display main menu (type MENU and hit Return)\n");
	printf("\n");
}