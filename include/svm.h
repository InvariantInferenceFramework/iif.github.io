#ifndef _SVM_H_
#define _SVM_H_
#include "ml_algo.h"
#include "svm_core.h"
#include "string.h"

class SVM : public MLalgo
{
	public:
		svm_model* model;
		Equation* main_equation;
		svm_parameter param;
		svm_problem problem;
		double* training_label; // [max_items * 2];
		double** training_set; // [max_items * 2];

		SVM(void (*f) (const char*) = NULL, int size = 10000) : max_size(size) {
			problem.l = 0;
			training_set = new double*[max_size];
			training_label = new double[max_size];

			main_equation = NULL;
			model = NULL;

			prepare_linear_parameters(param);
			if (f != NULL)
				svm_set_print_string_function(f);

			for (int i = 0; i < max_size; i++)
				training_label[i] = -1;
			problem.x = (svm_node**)(training_set);
			problem.y = training_label;
		}

		virtual ~SVM() {
			if (model != NULL)
				delete model;
			//if (problem.y != NULL)
			//	delete problem.y;
			// here we should check x[i] for each.
			// be careful about whether it is imported from double trace set or int trace set.
			// these two cases should be handled separatly.
		}

		virtual int makeTrainingSet(States* gsets, int& pre_positive_size, int& pre_negative_size) {
			int cur_positive_size = gsets[POSITIVE].getSize();
			int cur_negative_size = gsets[NEGATIVE].getSize();
			if (cur_positive_size + cur_negative_size >= max_size) {
				int previous_max_size = max_size;
				while (cur_positive_size + cur_negative_size >= max_size)
					max_size *= 2;
				double** previous_training_set = training_set;
				training_set = new double*[max_size];
				memmove(training_set, previous_training_set, previous_max_size * sizeof(double**));

				double* previous_training_label = training_label;
				training_label = new double[max_size];
				memmove(training_label, previous_training_label, previous_max_size * sizeof(double*));
			}

#ifdef __PRT
			std::cout << "+[";
			std::cout << cur_positive_size - pre_positive_size << "|";
			std::cout << cur_negative_size - pre_negative_size << "";
			std::cout << "] ==> [";
			std::cout << cur_positive_size << "+|";
			std::cout << cur_negative_size << "-";
			std::cout << "]";
#endif

			// prepare new training data set
			// training set & label layout:
			// data :  0 | positive states | negative states | ...
			// label:    | 1, 1, ..., 1, . | -1, -1, ..., -1, -1, -1, ...
			// move the negative states from old OFFSET: [pre_positive_size] to new OFFSET: [cur_positive_size]
			memmove(training_set + cur_positive_size, training_set + pre_positive_size, pre_negative_size * sizeof(double*));
			// add new positive states at OFFSET: [pre_positive_size]
			for (int i = 0 ; i < cur_positive_size; i++) {
				training_set[i] = gsets[POSITIVE].values[i];
				training_label[i] = 1;
			}
			// add new negative states at OFFSET: [cur_positive_size + pre_negative_size]
			for (int i = 0 ; i < cur_negative_size; i++) {
				training_set[cur_positive_size + i] = gsets[NEGATIVE].values[i];
			}
			problem.l = cur_positive_size + cur_negative_size;
			pre_positive_size = cur_positive_size;
			pre_negative_size = cur_negative_size;
			return 0;
		}

		virtual int train() {
			if (problem.y == NULL || problem.x == NULL)
				return -1;
			const char* error_msg = svm_check_parameter(&problem, &param);
			if (error_msg) {
				std::cout << "ERROR: " << error_msg << std::endl;
				return -1;
			}
			model = svm_train(&problem, &param);
			main_equation = new Equation();
			svm_model_visualization(model, *main_equation);
			svm_free_and_destroy_model(&model);
			return 0;
		}

		virtual double checkTrainingSet() {
			if (problem.l <= 0) return 0;
			int pass = 0;
			for (int i = 0; i < problem.l; i++) {
				pass += (Equation::calc(*main_equation, (double*)problem.x[i]) * problem.y[i] > 0) ? 1 : 0;
			}
			return static_cast<double>(pass) / problem.l;
		}

		virtual int checkQuestionSet(States& qset) {
			if (main_equation == NULL) return -1;
#ifdef __PRT
			std::cout << " [" << qset.traces_num() << "]";
#endif
			for (int i = 0; i < qset.p_index; i++) {
				int pre = -1, cur = 0;
#ifdef __PRT
				std::cout << ".";
#endif
				//std::cout << "\t\t" << i << ">";
				//gsets[QUESTION].print_trace(i);
				for (int j = qset.t_index[i]; j < qset.t_index[i + 1]; j++) {
					cur = Equation::calc(*main_equation, qset.values[j]);
					//std::cout << ((cur >= 0) ? "+" : "-");
					if ((pre >= 0) && (cur < 0)) {
						// deal with wrong question trace.
						// Trace back to print out the whole trace and the predicted labels.
#ifdef __PRT
						setColor(std::cout, RED);
						std::cerr << "\t[FAIL]\n \t  Predict wrongly on Question traces." << std::endl;
						qset.dumpTrace(i);
#endif
						for (int j = qset.t_index[i]; j < qset.t_index[i + 1]; j++) {
							cur = Equation::calc(*main_equation, qset.values[j]);
#ifdef __PRT
							std::cout << ((cur >= 0) ? "+" : "-");
#endif
						}
#ifdef __PRT
						std::cout << std::endl;
						setColor(std::cout);
#endif
						return -1;
					}
					pre = cur;
				}
				//std::cout << "END" << std::endl;
			}
#ifdef __PRT
			std::cout << " [PASS]";
#endif
			return 0;
		}

		virtual int converged (Equation* previous_equation, int equation_num) {
			if (equation_num != 1) {
				std::cout << "SVM::get_converged: Unexpected equation number parameter.\n";
				return -2;
			}
			return main_equation->is_similar(*previous_equation);
		}

		friend std::ostream& operator << (std::ostream& out, const SVM& svm) {
			return svm._print(out);
		}

		virtual std::ostream& _print(std::ostream& out) const {
			out << "SVM: ";
			out << *main_equation; // << std::endl;
			return out;
		}

		virtual int getProblemSize() {
			return problem.l;
		}

		virtual Equation* roundoff(int& num) {
			num = 1;
			Equation* equs = new Equation[1];
			main_equation->roundoff(equs[0]);
			return equs;
		}

		virtual int predict(double* v) {
			if (main_equation == NULL) return -2;
			if (v == NULL) return -2;
			double res = Equation::calc(*main_equation, v);

			if (res >= 0) return 1;
			else return -1;
		}

	protected:
		int max_size;
};

#endif /* _SVM_H */
