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
void calcul_angle_initial(struct donnees*);
void calcul_vitesse_initiale(struct donnees* data);
void calcul_angle_final(struct donnees* data);
void calcul_vitesse_finale(struct donnees* data);
void calcul_formule_temps_carre(struct donnees* data);
void calcul_formule_vitesses_carrees(struct donnees* data);
void calcul_formule_vitesse_acceleration(struct donnees* data);

double calcul_pi();

int main(void) {

	double pi = calcul_pi();
	struct donnees data;

	fill_struct(&data);
	instructions();

	inserer_donnees(&data);

	calcul_angle_initial(&data);



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

	int index = 0;
	scanf("%d", &index);
	printf("\nValeur pour la %d donnee: ", index);

	for (; index = 20;) {
		scanf("%lf", &tableau_donnees[index]);
		scanf("%d", &index);
		printf("\nValeur pour la %d donnee: ", index);
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

void calcul_angle_initial(struct donnees* data) {
	if (variable_presente(data->angle_i)) {
		data->angle_i = data->angle_i * calcul_pi() / 180;
	}
}

void calcul_angle_final(struct donnees* data) {
	if (variable_presente(data->angle_f)) {
		data->angle_f = data->angle_f * calcul_pi() / 180;
	}
}


void calcul_vitesse_initiale(struct donnees* data){
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
}

void calcul_vitesse_finale(struct donnees* data) {
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


void calcul_formule_temps_carre(struct donnees* data) {
	if (variable_presente(data->acceleration.y)) {

		if (variable_presente(data->temps_i)) {

			if (variable_presente(data->position_i.y)) {

				if (variable_presente(data->position_f.y)) {
					data->vitesse_i.y = ((data->position_i.y - data->position_f.y) / data->temps_f) + (data->acceleration.y / 2) * data->temps_f;
				}

				else if (variable_presente(data->vitesse_i.y)) {
					data->position_f.y = (data->acceleration.y / 2) * pow(data->temps_f, 2) + data->vitesse_i.y * data->temps_f;
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
		data->acceleration.y = 2 * (data->position_f.y - data->position_i.y - data->vitesse_i.y * data->temps_f) / pow(data->temps_f, 2);
	}
}


	// Vf2-Vi2=2a(yf-yi)
void calcul_formule_vitesses_carrees(struct donnees* data){
	if (variable_presente(data->acceleration.y)) {

		if (variable_presente(data->vitesse_f.y)) {

			if (variable_presente(data->vitesse_i.y)) {

				if (variable_presente(data->position_f.y)) {

					data->position_i.y = data->position_f.y - (pow(data->vitesse_f.y, 2) + pow(data->vitesse_i.y, 2)) / (2 * data->acceleration.y);
				}
			}
		}	
	}
}

void calcul_formule_vitesse_acceleration(struct donnees* data) {

}