// Roulette.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//
/*
Einsatz plazieren
Spieler bekommt zwei zufällige Zahlen von 1 - 10 oder König, Dame, Bube, Ass
Dealer bekommt eine Karte
Spieler entscheidet wie viele Karten er ziehen will oder seinen Wert beibehalten
Zweite Karte des Dealers wird aufgedeckt
Wenn der Kartenwert des Spielers über 21 liegt verliert er seinen ganzen Gewinn
Geht er bis 21 und ist höher als der Wert des Dealers gewinnt er 2:1
Ist er unter 21 verliert der Spieler
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int sum_of_player_cards(int player_cards[]);
int sum_of_dealer_cards(int dealer_cads[]);

void main()
{
	srand(time(0));

	int player_cards[21] = { 0 };
	int dealer_cards[21] = { 0 };
	int player_random[21];
	int dealer_random[21];
	int ass_value;

	for (int i = 0; i < 21; i++)
	{
		player_random[i] = rand() % 4;
		dealer_random[i] = rand() % 4;
	}

	printf("Deine Karten: ");

	for (int i = 0; i < 2; i++)
	{
		player_cards[i] = rand() % 11 + 1;

		switch (player_cards[i]) {
		case 10:
			switch (player_random[i]) {
			case 0:
				printf("10 ");
				break;
			case 1:
				printf("B ");
				break;
			case 2:
				printf("D ");
				break;
			case 3:
				printf("K ");
				break;
			}
			break;

		case 1 || 11:
			printf("%d ", player_cards[i]);
			/*printf("(A = ");
			scanf("%d)", &ass_value);
			player_cards[i] = ass_value;
			printf(") ");*/
			break;

		default:
			printf("%d ", player_cards[i]);
		}
	}
	if (player_cards[0] + player_cards[1] < 21)
	{

		printf("\nKarten des Dealers: ");

		dealer_cards[0] = rand() % 11 + 1;

		switch (dealer_cards[0]) {
		case 10:

			switch (dealer_random[0]) {
			case 0:
				printf("10 ");
				break;
			case 1:
				printf("B ");
				break;
			case 2:
				printf("D ");
				break;
			case 3:
				printf("K ");
				break;
			}
			break;

		case 1 || 11:
			printf("%d ", dealer_cards[0]);
			break;
		default:
			printf("%d", dealer_cards[0]);
		}
		printf("\n");

		int player_counter = 2;
		int dealer_counter = 1;
		char Ja_Nein_check;

		while (sum_of_player_cards(player_cards) < 21 && sum_of_dealer_cards(dealer_cards) < 21)
		{
			printf("Karte ziehen?(J/N): ");
			scanf(" %c", &Ja_Nein_check);

			if (sum_of_dealer_cards(dealer_cards) > 17 && Ja_Nein_check == 'N')
				break;
			else
			{
				if (Ja_Nein_check == 'J')
				{
					player_cards[player_counter] = rand() % 11 + 1;

					printf("Deine Karten: ");
					for (int i = 0; i <= player_counter; i++)
					{
						switch (player_cards[i]) {
						case 10:

							switch (player_random[i]) {
							case 0:
								printf("10 ");
								break;
							case 1:
								printf("B ");
								break;
							case 2:
								printf("D ");
								break;
							case 3:
								printf("K ");
								break;
							}
							break;

						case 1 || 11:
							printf("%d ", player_cards[i]);
							/*printf("(A = ");
							scanf("%d", &ass_value);
							player_cards[i] = ass_value;
							printf(") ");*/
							break;
						default:
							printf("%d ", player_cards[i]);
						}
					}
					printf("\n");
					player_counter++;
				}

				if (sum_of_dealer_cards(dealer_cards) <= 17)
				{
					dealer_cards[dealer_counter] = rand() % 11 + 1;

					printf("Karten des Dealers: ");

					for (int i = 0; i <= dealer_counter; i++)
					{
						switch (dealer_cards[i]) {
						case 10:

							switch (dealer_random[i]) {
							case 0:
								printf("10 ");
								break;
							case 1:
								printf("B ");
								break;
							case 2:
								printf("D ");
								break;
							case 3:
								printf("K ");
								break;
							}
							break;

						case (1 || 11):
							printf("%d ", dealer_cards[i]);
							break;
						default:
							printf("%d ", dealer_cards[i]);
						}
					}
					printf("\n");
					dealer_counter++;
				}
				else
					break;

				printf("\n");
			}
		}

		if (sum_of_player_cards(player_cards) <= 21 && sum_of_dealer_cards(dealer_cards) <= 21)
		{
			if (sum_of_player_cards > sum_of_dealer_cards)
				printf("Der Spieler hat gewonnen\n");

			else if (sum_of_player_cards < sum_of_dealer_cards)
				printf("Die Bank hat gewonnen\n");

			else
				printf("Gleichstand\n");
		}
		else if (sum_of_player_cards(player_cards) <= 21 && sum_of_dealer_cards(dealer_cards) > 21)
			printf("Der Spieler hat gewonnen\n");

		else if (sum_of_player_cards(player_cards) > 21 && sum_of_dealer_cards(dealer_cards) <= 21)
			printf("Die Bank hat gewonnen\n");

		else
			printf("Kein Gewinn für Bank oder Spieler\n");
	}
	else
		printf("Der Spieler hat das Spiel mit einem Blackjack gewonnen\n");
}

int sum_of_player_cards(int player_cards[])
{
	int sum = 0;

	for (int i = 0; i < 21; i++)
	{
		sum = sum + player_cards[i];
	}
	return sum;
}

int sum_of_dealer_cards(int dealer_cards[])
{
	int sum = 0;

	for (int i = 0; i < 21; i++)
	{
		sum = sum + dealer_cards[i];
	}
	return sum;

}