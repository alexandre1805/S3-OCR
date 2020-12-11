#ifndef NEURON_H
#define NEURON_H

struct Neuron
{
	long size;
	double *input;
	double *weight;
	double *error;
	double *biasWeight;
};

double output(struct Neuron N);
void randomizeWeights(struct Neuron N);
void adjustWeights(struct Neuron N);

#endif
