#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


// Defines

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


// Prototypes
void inserer_donnees(struct donnees*);
void instructions();
void fill_struct(struct donnees* data);


// main
int main(void) {

	// Variables du probleme

	// Pointeurs des variables

	struct donnees data = { nan("") };

	fill_struct(&data);
	instructions();
	inserer_donnees(&data);

	return 0;
}

// Fonctions develloppees

void inserer_donnees(struct donnees* data) {
	double* tableau_donnees = (double*)data;

	while (true) {
		int index = 0;
		scanf("%d", &index);
		if (index < 0 || index >= NB_DONNEES)
			break;
		scanf("%lf", &tableau_donnees[index]);
	}



}

void fill_struct(struct donnees* data) {
	double* tableau_donnees = (double*)data;
	for (int i = 0; i < NB_DONNEES; i++) {
		tableau_donnees[i] = nan("");
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