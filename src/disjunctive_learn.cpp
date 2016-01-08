#include "config.h"
#include "ml_algo.h"
#include "svm.h"
#include "color.h"
#include "equation.h"
#include "disjunctive_learn.h"

#include <iostream>
#include <float.h>
#include <string.h>
#include <assert.h>

static void print_null(const char *s) {}

DisjunctiveLearn::DisjunctiveLearn(States* gsets, int (*func)(int*), int max_iteration, int K) : LearnBase(gsets, func) { 
	svm = new SVM(print_null);
	//svm->main_equation = NULL;
	this->max_iteration = max_iteration; 
	this->K = K;
	/*
	positive_group = new int[gsets[1].size()];
	negative_group = new int[gsets[-1].size()];
	checkset = new double[gsets[-1].size() + gsets[1].size()][VARS];
	*/
}

DisjunctiveLearn::DisjunctiveLearn() : LearnBase() { 
	svm = new SVM(print_null);
	//svm->main_equation = NULL;
	this->max_iteration = max_iter; 
	this->K = 8;
	/*
	positive_group = NULL;
	negative_group = NULL;
	checkset = NULL;
	*/
}



int DisjunctiveLearn::k_means(int gset_index, int k)
{
	/*
	if (k > K)
		return -1;
	States& set = gsets[gset_index];
	int size = set.size();
	if (k >= size)
		return 0;
	double (*data)[VARS] = set.values;
	int* label;  
	if (gset_index == 1) label = positive_group;
	else if (gset_index == -1) label = negative_group;
	if (label == NULL)	label = new int [size]; 
	double** kmeans = new double*[size];

	// randomly choose points as the initial means to begin K-means algorithm
	for (int seed, i = 0; i < size; i++) {
		seed = rand() % k;
		kmeans[i] = new double[VARS];
		for (int j = 0; j < VARS; j++)
			kmeans[i][j] = data[seed][j];
	}


	double* distance = new double[k];
	int* group_members = new int[k];
	double total_distance = DBL_MAX;

	while (true) {	
		// regroup according to square distance.
		bool regrouped = false;
		for (int i = 0; i < size; i++) {
			int min_cand = 0;
			for (int j = 0; j < k; j++) {
				distance[j] = square_distance(kmeans[j], data[i], VARS);
				if (distance[j] < distance[min_cand])
					min_cand = j;
			}
			if (!regrouped && label[i] != min_cand)
				regrouped = true;
		}
		if (regrouped == false)
			break;

		// recalculate means for each group
		for (int i = 0; i < k; i++)
			group_members[i] = 0;
		for (int i = 0; i < size; i++) {
			group_members[label[i]]++;
			for (int j = 0; j < VARS; j++)
				kmeans[label[i]][j] += data[i][j];
		}
	}

	//for (int i = 0; i < s.size(); i++);

	delete []group_members;
	delete []distance;
	for (int i = 0; i < k; i++)
		delete []kmeans[i];
	delete []kmeans;
	delete []label;
	*/
	return 0;
}


bool linear_separable(int positive_label, int negative_label)
{
	/*
	int index = 0;
	// copy all the data which are labeled as given to the checkset
	int positive_size = gsets[POSITIVE].size();
	int negative_size = gsets[NEGATIVE].size();
	for(int i = 0; i < positive_size; i++)
		if (positive_group[i] == positive_label)
			checkset[index++] = gsets[POSITIVE][i];
	for(int i = 0; i < negative_size; i++)
		if (negative_group[i] == negative_label)
			checkset[index++] = gsets[POSITIVE][i];
*/
	return false;
}



int DisjunctiveLearn::learn()
{
	return 0;
}

