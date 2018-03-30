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

void Tools::printNIS( const vector<double> samples, string msg, bool is_radar ){
	
	if( samples.size() > 247 ){
		std::cout<<msg<<std::endl;
		float 
			total = samples.size(),
			cat_1 = 0,
			cat_2 = 0,
			low = is_radar ? 0.352 : 0.103,
			high = is_radar ? 7.815 : 5.991;
		for( int i=0; i<total; i++){
			if( samples[i] > low) cat_1++ ;
			if( samples[i] > high) cat_2++ ;
		}
		std::cout<<"Values above "<<low<<" ( =0.95) : "<<cat_1/total<<std::endl;
		std::cout<<"Values above "<<high<<" ( =0.05) : "<<cat_2/total<<std::endl;
	}
	return;
}
