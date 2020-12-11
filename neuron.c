#include <stdio.h>
#include <stdlib.h>
#include "sigmoid.h"
#include "neuron.h"

double output(struct Neuron N)
{
	double forsig = 0;
	double *in = N.input;
	double *we = N.weight;
	for (long i = 0; i < N.size; i++){
		forsig += *in * *we;
		in++;
		we++;}
	forsig += *N.biasWeight;
	double out = sigmoid(forsig);
	return out;
}

double randfrom(double min, double max)
{
	double range = (max - min);
	double div = RAND_MAX / range;
	return min + (rand() / div);
}

void randomizeWeights(struct Neuron N)
{
	double *we = N.weight;
	double *bi = N.biasWeight;
	for (long i = 0; i < N.size; i++){
		*we = (randfrom(0.0,2.0))-1;
		we++;}
	*bi = (randfrom(0.0,2.0))-1;
}

void adjustWeights(struct Neuron N)
{
	double *in = N.input;
	double *we = N.weight;
	double *er = N.error;
	for (long i = 0; i < N.size; i++){
		*we -=  0.5 * *er * *in;
		in++;
		we++;}
}
