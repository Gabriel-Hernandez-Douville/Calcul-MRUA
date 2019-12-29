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
void valeurs_par_defaut(struct donnees* data);
void conversion_angle_initial(struct donnees*);
void calcul_vitesse_initiale(struct donnees* data);
void conversion_angle_final(struct donnees* data);
void calcul_vitesse_finale(struct donnees* data);
void calcul_formule_temps_carre(struct donnees* data);
void calcul_formule_vitesses_carrees(struct donnees* data);
void calcul_formule_vitesse_acceleration(struct donnees* data);
void solve_quadratic(struct donnees* data);
void conversion_vitesse_x(struct donnees* data);
void calcul_angle_final(struct donnees* data);



double calcul_pi();

bool variable_presente(double valeur);

int main(void) {

	double pi = calcul_pi();
	struct donnees data;

	fill_struct(&data);
	instructions();

	inserer_donnees(&data);

	conversion_angle_initial(&data);



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
// done

void fill_struct(struct donnees* data) {
	double* tableau_donnees = (double*)data;

	for (int i = 0; i < NB_DONNEES; i++) {
		tableau_donnees[i] = nan("");
	}
}
// done

void instructions() {
	printf("Voici le menu de donnees:\n"
		"Veuillez entrer votre selection:\n\n"
		"Vitesse initiale en x.........0.\n"
		"Vitesse initiale en y.........1.\n"
		"Vitesse initiale norme........2.\n\n"
		"Vitesse finale en x...........3.\n"
		"Vitesse finale en y...........4.\n"
		"Vitesse finale................5.\n\n"
		"Position x initiale...........6.\n"
		"Position y initiale...........7.\n\n"
		"Position x finale.............8.\n"
		"Position y finale.............9.\n\n"
		"Acceleration en x............10.\n"
		"Acceleration en y............11.\n\n"
		"Angle intial.................12.\n"
		"Angle final..................13.\n\n"
		"temps initial................14.\n"
		"temps final..................15.\n\n"
		"Pour quitter le menu, faites le 20.\n\n");
}
// done


void inserer_donnees(struct donnees* data) {
	double* tableau_donnees = (double*)data;

	char tableau_menu[19][50] = { "Vitesse initiale x = ", "Vitesse initiale y = ", "Vitesse initiale = ", "Vitesse finale x = " "Vitesse finale y = ", "Vitesse finale = ",
		"Position initiale x = ", "Position initiale y = ", "Position finale x = ", "Position finale y = ", "Acceleration x = ", "Acceleration y = ", "Angle initial = ",
		"Angle final = ", "Temps initial = ", "Temps final = " };

	int index;
	printf("\nEntrez votre selection: ");
	scanf("%d", &index);

	while (index != 20) {
		printf("%s", tableau_menu[index]);
		scanf("%lf", &tableau_donnees[index]);
		printf("\nEntrez votre selection: ");
		scanf("%d", &index);
	}

}


bool variable_presente(double valeur) {
	return !isnan(valeur);
}
// done

void valeurs_par_defaut(struct donnees* data) {
	// acceleration en y
	if (variable_presente(data->acceleration.y) == false) {
		data->acceleration.y = -9.8;
	}
	// acceleration en x
	if (variable_presente(data->acceleration.x) == false) {
		data->acceleration.x = 0;
	}
	// temps initial
	if (variable_presente(data->temps_i) == false) {
		data->temps_i = 0;
	}
	// angle initial
	if (variable_presente(data->angle_i) == false) {
		data->angle_i = 90;
	}
}


void conversion_angle_initial(struct donnees* data) {
	if (variable_presente(data->angle_i)) {
		data->angle_i = data->angle_i * calcul_pi() / 180;
	}
}
// done

void conversion_angle_final(struct donnees* data) {
	if (variable_presente(data->angle_f)) {
		data->angle_f = data->angle_f * calcul_pi() / 180;
	}
}
// done


void calcul_vitesse_initiale(struct donnees* data) {
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
//done

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
// done

// yf=-1/2gt2+vit+y0
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
			solve_quadratic(data);
		}
	}

	else if (variable_presente(data->position_i.y) && variable_presente(data->position_f.y) && variable_presente(data->vitesse_i.y) && variable_presente(data->temps_f)) {
		data->acceleration.y = 2 * (data->position_f.y - data->position_i.y - data->vitesse_i.y * data->temps_f) / pow(data->temps_f, 2);
	}
}
// done


// Vf2-Vi2=2a(yf-yi)
void calcul_formule_vitesses_carrees(struct donnees* data) {
	if (variable_presente(data->acceleration.y)) {

		if (variable_presente(data->vitesse_f.y)) {

			if (variable_presente(data->vitesse_i.y)) {

				if (variable_presente(data->position_f.y)) {

					data->position_i.y = data->position_f.y - (pow(data->vitesse_f.y, 2) + pow(data->vitesse_i.y, 2)) / (2 * data->acceleration.y);
				}
				else if (variable_presente(data->position_i.y)) {
					data->position_f.y = data->position_i.y + (pow(data->vitesse_f.y, 2) - pow(data->vitesse_i.y, 2)) / (2 * data->acceleration.y);
				}
			}
			else if (variable_presente(data->position_f.y) && (variable_presente(data->position_i.y))) {
				data->vitesse_i.y = sqrt(pow(data->vitesse_f.y, 2) - (2 * data->acceleration.y * (data->position_f.y - data->position_i.y)));
			}
		}
		else if (variable_presente(data->vitesse_i.y) && variable_presente(data->position_f.y) && variable_presente(data->position_i.y)) {
			data->vitesse_f.y = sqrt(pow(data->vitesse_i.y, 2) + (2 * data->acceleration.y * (data->position_f.y - data->position_i.y)));
		}
	}
	else if (variable_presente(data->vitesse_f.y) && variable_presente(data->vitesse_i.y) && variable_presente(data->position_f.y) && variable_presente(data->position_i.y)) {
		data->acceleration.y = (pow(data->vitesse_f.y, 2) - pow(data->vitesse_i.y, 2)) / (2 * (data->position_f.y - data->position_i.y));
	}
}
// done

// vf=vi+at
void calcul_formule_vitesse_acceleration(struct donnees* data) {
	if (variable_presente(data->acceleration.y)) {

		if (variable_presente(data->vitesse_i.y)) {

			if (variable_presente(data->temps_f)) {
				data->vitesse_f.y = data->vitesse_i.y + data->acceleration.y * data->temps_f;
			}
			else if (variable_presente(data->vitesse_f.y)) {
				data->temps_f = data->vitesse_f.y;
			}
		}
		else if (variable_presente(data->temps_f) && variable_presente(data->vitesse_f.y)) {
			data->vitesse_i.y = data->vitesse_f.y - data->acceleration.y * data->temps_f;
		}
	}
	else if (variable_presente(data->vitesse_f.y) && variable_presente(data->vitesse_i.y) && variable_presente(data->temps_f)) {
		data->acceleration.y = (data->vitesse_f.y - data->vitesse_i.y) / data->temps_f;
	}
}
// done

// x=(-b+-sqrt(b^2-4ac))/2a
void solve_quadratic(struct donnees* data) {
	double a, b, c;
	a = (data->acceleration.y) / 2;
	b = data->vitesse_i.y;
	c = data->position_i.y - data->position_f.y;

	if (data->acceleration.y < 0) {
		data->temps_f = ((0 - b) - (sqrt(pow(b, 2) - (4 * a * c)))) / 2 * a;
	}
	else if (data->acceleration.y > 0) {
		data->temps_f = ((0 - b) + (sqrt(pow(b, 2) - (4 * a * c)))) / 2 * a;
	}
}
// done

void conversion_vitesse_x(struct donnees* data) {
	if ((variable_presente(data->vitesse_f.x) == false) && (variable_presente(data->vitesse_i.x))) {
		data->vitesse_f.x = data->vitesse_i.x;
	}
	if ((variable_presente(data->vitesse_i.x) == false) && (variable_presente(data->vitesse_f.x))) {
		data->vitesse_i.x = data->vitesse_f.x;
	}
}
// done

void calcul_angle_final(struct donnees* data) {
	if (variable_presente(data->vitesse_f.x) && variable_presente(data->vitesse_f.y)) {
		data->angle_f = (atan(data->vitesse_f.y / data->vitesse_f.x));
	}
}
