// main.cpp

#include <string>
#include <iostream>
#include <fstream>
#include "openGA.hpp"

using std::string;
using std::cout;
using std::endl;
int numGenes = 0;

struct Chromosome
{
	std::vector<double> paramVec;
	Chromosome() : paramVec(numGenes) {};

	string to_string() const
	{
		return 
			string("{")
			+  "x:"+std::to_string(paramVec[0])
			+", y:"+std::to_string(paramVec[1])
			+"}";
	}
};

struct MyMiddleCost
{
	// This is where the results of simulation
	// is stored but not yet finalized.
	double objective1;
};

typedef EA::Genetic<Chromosome,MyMiddleCost> GA_Type;
typedef EA::GenerationType<Chromosome,MyMiddleCost> Generation_Type;

void init_genes(Chromosome& p,const std::function<double(void)> &rnd01)
{
	// rnd01() gives a random number in 0~1
	p.paramVec[0]=-1000+2000*rnd01();
	p.paramVec[1]=-1000+2000*rnd01();
}

bool eval_solution(
	const Chromosome& p,
	MyMiddleCost &c)
{
	const double& var1=p.paramVec[0];
	const double& var2=p.paramVec[1];

	c.objective1=(var1*var1 + var2 - 11)*(var1*var1 + var2 - 11) + (var1 + var2*var2 - 7)*(var1 + var2*var2 - 7);
	return true; // solution is accepted
}

Chromosome mutate(
	const Chromosome& X_base,
	const std::function<double(void)> &rnd01,
	double shrink_scale)
{
	Chromosome X_new;
	bool in_range;
	do{
		in_range=true;
		X_new=X_base;
		X_new.paramVec[0]+=0.2*(rnd01()-rnd01())*shrink_scale;
		in_range=in_range&&(X_new.paramVec[0]>=-1000 && X_new.paramVec[0]<1000);
		X_new.paramVec[1]+=0.2*(rnd01()-rnd01())*shrink_scale;
		in_range=in_range&&(X_new.paramVec[1]>=-1000 && X_new.paramVec[1]<1000);
	} while(!in_range);
	return X_new;
}

Chromosome crossover(
	const Chromosome& X1,
	const Chromosome& X2,
	const std::function<double(void)> &rnd01)
{
	Chromosome X_new;
	double r;
	r=rnd01();
	X_new.paramVec[0]=r*X1.paramVec[0]+(1.0-r)*X2.paramVec[0];
	r=rnd01();
	X_new.paramVec[1]=r*X1.paramVec[1]+(1.0-r)*X2.paramVec[1];
	return X_new;
}

double calculate_SO_total_fitness(const GA_Type::thisChromosomeType &X)
{
	// finalize the cost
	double final_cost=0.0;
	final_cost+=X.middle_costs.objective1;
	return final_cost;
}

std::ofstream output_file;

void SO_report_generation(
	int generation_number,
	const EA::GenerationType<Chromosome,MyMiddleCost> &last_generation,
	const Chromosome& best_genes)
{
	cout
		<<"Generation ["<<generation_number<<"], "
		<<"Best="<<last_generation.best_total_cost<<", "
		<<"Average="<<last_generation.average_cost<<", "
		<<"Best genes=("<<best_genes.to_string()<<")"<<", "
		<<"Exe_time="<<last_generation.exe_time
		<<endl;

	output_file
		<<generation_number<<"\t"
		<<last_generation.average_cost<<"\t"
		<<last_generation.best_total_cost<<"\t"
		<<best_genes.to_string()<<"\n";
}

int main()
{
	numGenes = 2;
	output_file.open("results.txt");
	output_file<<"step"<<"\t"<<"cost_avg"<<"\t"<<"cost_best"<<"\t"<<"solution_best"<<"\n";

	EA::Chronometer timer;
	timer.tic();

	GA_Type ga_obj;
	ga_obj.problem_mode=EA::GA_MODE::SOGA;
	ga_obj.multi_threading=false;
	ga_obj.idle_delay_us=10; // switch between threads quickly
	ga_obj.dynamic_threading=true;
	ga_obj.verbose=false;
	ga_obj.population=200;
	ga_obj.generation_max=1000;
	ga_obj.calculate_SO_total_fitness=calculate_SO_total_fitness;
	ga_obj.init_genes=init_genes;
	ga_obj.eval_solution=eval_solution;
	ga_obj.mutate=mutate;
	ga_obj.crossover=crossover;
	ga_obj.SO_report_generation=SO_report_generation;
	ga_obj.crossover_fraction=0.7;
	ga_obj.mutation_rate=0.2;
	ga_obj.best_stall_max=10;
	ga_obj.elite_count=10;
	ga_obj.solve();

	cout<<"The problem is optimized in "<<timer.toc()<<" seconds."<<endl;

	output_file.close();
	return 0;
}