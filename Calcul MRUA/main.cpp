#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define G -9.81
#define NB_DONNEES sizeof(struct donnees)/sizeof(double)

struct vitesse2D {
	double x;
	double y;
	double norme;
};

struct vecteur2D {
	double x;
	double y;
};

struct donnees {
	struct vitesse2D vitesse_i;
	struct vitesse2D vitesse_f;

	struct vecteur2D position_i;
	struct vecteur2D position_f;

	struct vecteur2D acceleration;

	double angle_i;
	double angle_f;

	double temps_i;
	double temps_f;
};

void inserer_donnees(struct donnees*);
void instructions();
void fill_struct(struct donnees* data);
void calcul_1(struct donnees*);
double calcul_pi();

int main(void) {
	double pi = calcul_pi();
	struct donnees data;
	fill_struct(&data);
	instructions();

	inserer_donnees(&data);
	calcul_1(&data);



	double angle = 50;
	double angle_rad;

	angle_rad = angle * pi / 180;

	double x = (10 * cos(0.87));
	double y = (10 * sin(0.87));
	double z = 5;



	return 0;
}

double calcul_pi() {
	double k = 0;
	double pi = 0;
	double value;
	double exp;

	while (k < 1000) {
		exp = pow(-3, -k);
		value = exp * sqrt(12) / (2 * k + 1);
		k++;
		pi = pi + value;
	}
	return pi;
}

void inserer_donnees(struct donnees* data) {
	double* tableau_donnees = (double*)data;

	while (true) {
		int index = 0;
		scanf("%d", &index);

		if (index < 0 || index >= NB_DONNEES)
			break;
		switch (index) {
		case '0': printf("Vitesse initiale x = ");
			break;
		case '1': printf("Vitesse initiale y = ");
			break;
		case '2': printf("Vitesse initiale norme = ");
			break;
		case '3': printf("Vitesse finale x = ");
			break;
		case '4': printf("Vitesse finale y = ");
			break;
		case '5': printf("Vitesse finale norme = ");
			break;
		case '6': printf("Position initiale x = ");
			break;
		case '7': printf("Position initiale y = ");
			break;
		case '8': printf("Position finale x = ");
			break;
		case '9': printf("Position finale y = ");
			break;
		case '10': printf("Acceleration x = ");
			break;
		case '11': printf("Acceleration y = ");
			break;
		case '12': printf("Angle intial en degres = ");
			break;
		case '13': printf("Angle final en degres = ");
			break;
		case '14': printf("Temps initial (temps de debut - surement 0) = ");
			break;
		case '15': printf("Temps final = ");
			break;
		}

		scanf("%lf", &tableau_donnees[index]);
	}
}

void instructions() {
	printf("Veuillez saisir les donnees:\n"
		"Pour saisir:\n"
		"Composante en x de la vitesse initiale, faites le 0.\n"
		"Composante en y de la vitesse initiale, faites le 1.\n"
		"Norme de la vitesse initiale, faites le 2.\n"
		"Composante en x de la vitesse finale, faites le 3.\n"
		"Composante en x de la vitesse finale, faites le 4.\n"
		"Norme de la vitesse finale, faites le 5.\n"
		"Position x initiale, faites le 6.\n"
		"Position y initiale, faites le 7.\n"
		"Position x finale, faites le 8.\n"
		"Position y finale, faites le 9.\n"
		"Acceleration en x, faites le 10.\n"
		"Acceleration en y, faites le 11.\n"
		"Angle intial, faites le 12.\n"
		"Angle final, faites le 13.\n"
		"temps initial, faites le 14.\n"
		"temps final, faites le 15.\n"
		"Pour quitter le menu, faites le 20.\n\n");
}

void fill_struct(struct donnees* data) {
	double* tableau_donnees = (double*)data;

	for (int i = 0; i < NB_DONNEES; i++) {
		tableau_donnees[i] = nan("");
	}
}


bool variable_presente(double valeur) {
	return !isnan(valeur);
}

void calcul_1(struct donnees* data) {
	//vitesse initiale et composantes
	if (variable_presente(data->angle_i)) {
		data->angle_i = data->angle_i * calcul_pi() / 180;
	}

	if (variable_presente(data->vitesse_i.norme)) {
		data->vitesse_i.x = data->vitesse_i.norme * cos(data->angle_i);
		data->vitesse_i.y = data->vitesse_i.norme * sin(data->angle_i);
	}
	else if (variable_presente(data->vitesse_i.x)) {
		data->vitesse_i.norme = data->vitesse_i.x / cos(data->angle_i);
		data->vitesse_i.y = data->vitesse_i.norme * sin(data->angle_i);
	}
	else if (variable_presente(data->vitesse_i.y)) {
		data->vitesse_i.norme = data->vitesse_i.x / sin(data->angle_i);
		data->vitesse_i.x = data->vitesse_i.norme * cos(data->angle_i);
	}

	//formulte yf=/1/2gt2+vit+yo
	if (variable_presente(data->acceleration.y)) {

		if (variable_presente(data->temps_i)) {

			if (variable_presente(data->position_i.y)) {

				if (variable_presente(data->position_f.y)) {
					data->vitesse_i.y = ((data->position_i.y - data->position_f.y) / data->temps_f) + (data->acceleration.y / 2) * data->temps_f;
				}

				else if (variable_presente(data->vitesse_i.y)) {
					data->position_f.y = (data->acceleration.y / 2) * data->temps_f * data->temps_f + data->vitesse_i.y * data->temps_f;
				}
			}

			else if (variable_presente(data->vitesse_i.y) && variable_presente(data->position_f.y)) {
				data->position_i.y = data->position_f.y - data->temps_f * ((data->acceleration.y / 2) * data->temps_f + data->vitesse_i.y);
			}
		}

		else if (variable_presente(data->position_i.y) && variable_presente(data->position_f.y) && variable_presente(data->vitesse_i.y)) {
			data->temps_f;
		}
	}

	else if (variable_presente(data->position_i.y) && variable_presente(data->position_f.y) && variable_presente(data->vitesse_i.y) && variable_presente(data->temps_f)) {
		data->acceleration.y = 2 * (data->position_f.y - data->position_i.y - data->vitesse_i.y * data->temps_f) / (data->temps_f * data->temps_f);
	}

	// Vitesse finale et composantes
	if (variable_presente(data->vitesse_f.norme)) {
		data->vitesse_f.x = data->vitesse_f.x * cos(data->angle_f);
		data->vitesse_f.y = data->vitesse_f.y * sin(data->angle_f);
	}
	else if (variable_presente(data->vitesse_f.x)) {
		data->vitesse_f.norme = data->vitesse_f.x / cos(data->angle_f);
		data->vitesse_f.y = data->vitesse_f.norme * sin(data->angle_f);
	}
	else if (variable_presente(data->vitesse_f.y)) {
		data->vitesse_f.norme = data->vitesse_f.x / sin(data->angle_f);
		data->vitesse_f.x = data->vitesse_f.norme * cos(data->angle_f);
	}


}
/*
	(if a) -
		(if t) -
			(if yf) -
				(if yi) - [viy]
				(if viy) - [yi]
			(if yi)
				(if yf) - [viy]
				(if viy) - [yf]
			(if viy)
				(if yf)	- [yi]
				(if yi) - [yf]
		(if yf)
		(if yi)
		(if viy)

		a=b*c*d
		*/




