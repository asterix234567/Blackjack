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
#include <conio.h>

#define GUTHABEN 1000

int sum_of_cards(int cards[]);
void card_prints(int cards[], int i, int player_cards[]);
void Blackjack_check(int cards[]);

int guthaben = GUTHABEN;

void main()
{
	srand(time(0));

	char start_check;
	int i = 1;

	do
	{
		printf("Runde %d\n", i);
		i++;

		int player_cards[21] = { 0 };
		int dealer_cards[21] = { 0 };
		int player_choice_B_D_K[21];
		int dealer_choice_B_D_K[21];
		int einsatz;
		int zusatzlicher_einsatz;

		printf("Guthaben: %d\n", guthaben);

		printf("Einsatz setzen: ");
		scanf("%d", &einsatz);

		if (einsatz < 0)
			einsatz = 0;

		if (einsatz >= guthaben)
		{
			einsatz = guthaben;
			guthaben = 0;
		}
		else 
			guthaben -= einsatz;

		printf("Deine Karten: ");

		for (int i = 0; i < 2; i++)
		{
			player_cards[i] = rand() % 13 + 2;
			player_choice_B_D_K[i] = player_cards[i];
			if (player_cards[i] >= 12 && player_cards[i] <= 14)
				player_cards[i] = 10;

		}
	
		if (sum_of_cards(player_cards) == 21)
		{
			Blackjack_check(player_choice_B_D_K);
		}
		else
		{
			for (int i = 0; i < 2; i++)
			{
				card_prints(player_choice_B_D_K, i, player_cards);

			}
			printf("\n");
		}

		if (!(sum_of_cards(player_cards) < 21))
		{
			printf("Der Spieler hat das Spiel mit einem Blackjack gewonnen\n");
			einsatz *= 1.5;
			printf("Gewinn: %d\n", einsatz);
			guthaben += einsatz;
		}
		else
		{

			printf("Karten des Dealers: ");

			dealer_cards[0] = rand() % 13 + 2;

			dealer_choice_B_D_K[0] = dealer_cards[0];
			if (dealer_cards[0] >= 12 && dealer_cards[0] <= 14)
				dealer_cards[0] = 10;

			card_prints(dealer_choice_B_D_K, 0, dealer_cards);
			printf("\n");

			int player_counter = 2;
			int dealer_counter = 1;
			char Ja_Nein_check;

			while (sum_of_cards(player_cards) < 21 && sum_of_cards(dealer_cards) < 21)
			{
				if (guthaben != 0)
				{
					printf("Einsatz erhoehen: ");
					scanf("%d", &zusatzlicher_einsatz);

					if (zusatzlicher_einsatz < 0)
						zusatzlicher_einsatz = 0;

					if (zusatzlicher_einsatz + einsatz >= guthaben)
					{
						einsatz += guthaben;
						guthaben = 0;
					}
					else
					{
						guthaben -= zusatzlicher_einsatz;
						einsatz += zusatzlicher_einsatz;
					}

					if (guthaben == 0)
					{
						printf("All in\n");
					}
					else
						printf("Einsatz: %d\n", einsatz);
					
				}
				else
					printf("All in\n");

				printf("\nKarte ziehen?(j/n): ");
				scanf(" %c", &Ja_Nein_check);

				if (sum_of_cards(dealer_cards) > 17 && Ja_Nein_check == 'n')
					break;
				else
				{

					if (Ja_Nein_check == 'j')
					{
						player_cards[player_counter] = rand() % 13 + 2;

						player_choice_B_D_K[player_counter] = player_cards[player_counter];
						if (player_cards[player_counter] >= 12 && player_cards[player_counter] <= 14)
							player_cards[player_counter] = 10;


						printf("Deine Karten: ");
						for (int i = 0; i <= player_counter; i++)
						{
							card_prints(player_choice_B_D_K, i, player_cards);
						}
						printf("\n");
						player_counter++;
					}

					if (sum_of_cards(dealer_cards) <= 17)
					{
						dealer_cards[dealer_counter] = rand() % 13 + 2;

						dealer_choice_B_D_K[dealer_counter] = dealer_cards[dealer_counter];

						if (dealer_cards[dealer_counter] >= 12 && dealer_cards[dealer_counter] <= 14)
							dealer_cards[dealer_counter] = 10;

						printf("Karten des Dealers: ");

						for (int i = 0; i <= dealer_counter; i++)
						{
							card_prints(dealer_choice_B_D_K, i, dealer_cards);
						}
						dealer_counter++;
					}
					else
						break;

					printf("\n");
				}
			}

			int sum_of_player_cards = sum_of_cards(player_cards);
			int sum_of_dealer_cards = sum_of_cards(dealer_cards);

			if (sum_of_player_cards <= 21 && sum_of_dealer_cards <= 21)
			{
				if (sum_of_player_cards > sum_of_dealer_cards)
				{
					printf("Der Spieler hat gewonnen\n");
					printf("Gewinn: %d", einsatz);
					guthaben += einsatz * 2;
				}

				else if (sum_of_player_cards < sum_of_dealer_cards)
					printf("Die Bank hat gewonnen\n");
				
				else
				{
					printf("Stand off\n");
					guthaben += einsatz;
				}
			}
			else if (sum_of_player_cards <= 21 && sum_of_dealer_cards > 21)
			{
				printf("Der Spieler hat gewonnen\n");
				printf("Gewinn: %d\n", einsatz);
				guthaben += einsatz * 2;
			}
			else if (sum_of_player_cards > 21 && sum_of_dealer_cards <= 21)
				printf("Die Bank hat gewonnen\n");

			else
			{
				printf("Kein Gewinn fur Bank oder Spieler\n");
				guthaben += einsatz;
			}
		}
		printf("\n");

		if (guthaben == 0)
		{
			printf("Alles verloren\n");
			start_check = 'n';
		}
		else
		{
			printf("Noch eine Runde spielen? (j/n): ");
			scanf(" %c", &start_check);
			printf("\n");
		}
	}while (start_check == 'j');

	printf("Guthaben: %d\n", guthaben);

	if (guthaben - GUTHABEN >= 0)
		printf("Gesammter Gewinn: %d\n", guthaben - GUTHABEN);
	else
		printf("Gesammter Verlust: %d\n", (guthaben - GUTHABEN) * -1);
}

int sum_of_cards(int cards[])
{
	int sum = 0;

	for (int i = 0; i < 21; i++)
	{
		sum = sum + cards[i];
	}
	return sum;
}

void card_prints(int print_cards[], int i, int math_cards[])
{
	char ass_check;
	switch (print_cards[i]) {
	case 12:
		printf("B ");
		break;
	case 13:
		printf("D ");
		break;

	case 14:
		printf("K ");
		break;
	case 1:
		printf("A ");
		break;
	case 11:
		printf("A ");
		if (sum_of_cards(math_cards) > 21)
			math_cards[i] = 1;
		break;
	default:
		printf("%d ", print_cards[i]);
	}

}

void Blackjack_check(int player_choice_B_D_K[])
{
	if (player_choice_B_D_K[0] >= 12 && player_choice_B_D_K[0] <= 14 || player_choice_B_D_K[1] >= 12 && player_choice_B_D_K[1] <= 14)
	{
		if (player_choice_B_D_K[0] == 1 || player_choice_B_D_K[0] == 11 || player_choice_B_D_K[1] == 1 || player_choice_B_D_K[1] == 11)
		{
			if (player_choice_B_D_K[0] == 12 || player_choice_B_D_K[1] == 12)
				printf(" B A \n");
			else if (player_choice_B_D_K[0] == 13 || player_choice_B_D_K[1] == 13)
				printf(" D A \n");
			else if (player_choice_B_D_K[0] == 14 || player_choice_B_D_K[1] == 14)
				printf(" K A \n");
		}
	}


}