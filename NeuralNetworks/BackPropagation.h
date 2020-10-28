#ifndef BACK_PROPAGATION_H
#define BACK_PROPAGATION_H

double delta(double error, double out);

void learnBackTree(Node *h, Node *z, NetworkData *data, double res[7], double v);

void learnAverage(Node *h, Node *z, NetworkData *data, double v, size_t iter);

#endif
