// EXPLIZITES VERFAHREN

#include <stdio.h>
#include <math.h>

void main()
{
	double alpha = 2.5, lambda = 0.6, u = 0.0628, L = 20;
	double c = 4200., rho = 1000.;
	double Ta = 318., Tu = 288., CFL = 0.3, a, A = 3.14e-4;

	int m = 20, m_zeit = 1000;
	double dx = L / (m - 1), *x, *T_old, *T_new;

	a = lambda / (rho*c);

	x = new double[m];
	T_new = new double[m];
	T_old = new double[m];

	for (int i = 0; i <= m - 1; i++)
	{
		x[i] = i * dx;
	}

	// Anfangsbedingung
	T_old[0] = Ta;
	for (int i = 1; i <= m - 1; i++)
	{
		T_old[i] = Tu;
	}

	// Zeitschritt
	double dt = CFL * dx*dx / a;

	FILE *james;
	fopen_s(&james, "test.dat", "w");
	// james = fopeen("temperatur.dat", "w");
	for (int j = 0; j <= m - 1; j++)
	{
		fprintf_s(james, "%20.7lf", T_old[j]);
	}

	for (int i = 1; i <= m_zeit; i++)
	{
		// Randbedingung
		T_new[0] = Ta;
		T_new[m - 1] = Tu;
		for (int j = 1; j <= m - 2; j++)
		{
			T_new[j] = a * (T_old[j + 1] - 2.*T_old[j] + T_old[j - 1]) / (dx*dx) *dt - alpha*u*dt / (rho * A * c)*(T_old[j] - Tu) + T_old[j];
		}

		for (int j = 0; j <= m - 1; j++)
		{
			T_old[j] = T_new[j];
			fprintf_s(james, "%20.7lf", T_new[j]);
		}
		fprintf_s(james, "\n");

	}
	fclose(james);

	delete[] x;
	delete[] T_new;
	delete[] T_old;

}