#include <iostream>
#include "tools.h"

using Eigen::VectorXd;
using Eigen::MatrixXd;
using std::vector;

Tools::Tools() {}

Tools::~Tools() {}

VectorXd Tools::CalculateRMSE(const vector<VectorXd> &estimations,
                              const vector<VectorXd> &ground_truth) {
  /**
  TODO:
    * Calculate the RMSE here.
  */
  VectorXd rmse(4);
	rmse << 0,0,0,0;

	if( estimations.size() == 0 || estimations.size() != ground_truth.size()){
    cout<<"Zero Estimations or ground_truth size and estimations size not equal";
    return rmse;
	}

    
	//accumulate squared residuals
	for(int i=0; i < estimations.size(); ++i){
    VectorXd diff = estimations[i] - ground_truth[i];
    diff = diff.array()*diff.array();
		rmse += diff;
	}
	
	//calculate the mean	
	rmse /= estimations.size();

	//calculate the squared root
	rmse = rmse.array().sqrt();

	//return the result
	return rmse;
}

void Tools::printNIS( const vector<double> samples ){
	
	if( samples.size() > 494 ){
		float 
			total = samples.size(),
			cat_1 = 0,
			cat_2 = 0,
			cat_3 = 0,
			cat_4 = 0;
		for( int i=0; i<total; i++){
			if( samples[i] > 0.352) cat_1++ ;
			if( samples[i] > 0.584) cat_2++ ;
			if( samples[i] > 6.251) cat_3++ ;
			if( samples[i] > 7.815) cat_4++ ;
		}
		std::cout<<"\nValues above 0.352 ( =0.95) : "<<cat_1/total<<std::endl;
		// std::cout<<"Values above 0.584 ( =0.90) : "<<cat_2/total<<std::endl;
		// std::cout<<"Values above 6.251 ( =0.10) : "<<cat_3/total<<std::endl;
		std::cout<<"Values above 7.815 ( =0.05) : "<<cat_4/total<<std::endl;
	}
	return;
}
