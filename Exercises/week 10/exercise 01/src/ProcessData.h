// Exercise - Multi-Threading, Thread Class

#ifndef SENECA_PROCESSDATA_H
#define SENECA_PROCESSDATA_H

#include <string>

namespace seneca
{
	void computeAvgFactor(const int*, int, int, double&);
	void computeVarFactor(const int*, int, int, double, double&);

	class ProcessData
	{
		int total_items{};
		int* data{};
		// Following parameters are included to be used for managing multi-threaded 
		//  computation in the operator() function. 
		int num_threads{ 0 }; // to hold number of threads 
		double* averages{ nullptr }; // to hold average factors 
		double* variances{ nullptr }; // to hold variance factors
		int* p_indices{ nullptr }; // to hold partitioning indices
	public:
		ProcessData(const std::string&, int n_threads);
		ProcessData(const ProcessData&) = delete;
		ProcessData& operator=(const ProcessData&) = delete;
		~ProcessData();
		operator bool() const;
		int operator()(const std::string&, double&, double&);
	};
}

#endif
