/*
 * main.cpp
 *
 *  Created on: 21 cze 2016
 *      Author: jachu
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <random>

#include "3rdParty/Eigen/StdVector"

#include "3rdParty/g2o/g2o/types/slam3d/se3quat.h"
#include "3rdParty/g2o/g2o/types/slam3d/isometry3d_mappings.h"

using namespace std;

int main(){
	try{
		ifstream trajFile("../res/groundtruth.txt");

		if(!trajFile.is_open()){
			throw "Error - groundtruth file not open";

		}

		vector<g2o::Vector7d> gtPoses;
		while(trajFile.good()){
			g2o::Vector7d curPose;
			int id;
			trajFile >> id;
			for(int v = 0; v < 7; ++v){
				double val;
				trajFile >> val;
				if(trajFile.good()){
					curPose[v] = val;
				}
			}
			if(trajFile.good()){
//				cout << "curPose = " << curPose << endl;
				gtPoses.push_back(curPose);
			}
		}

		default_random_engine gen;
		normal_distribution<double> distT(0.0, 0.005);
		normal_distribution<double> distR(0.0, 0.005);
		g2o::Vector7d initPose = gtPoses[0];
		vector<g2o::Vector7d> diffPoses{initPose};
		for(int p = 1; p < gtPoses.size(); ++p){
			g2o::Isometry3D prevPose = g2o::internal::fromVectorQT(gtPoses[p - 1]);
			g2o::Isometry3D nextPose = g2o::internal::fromVectorQT(gtPoses[p]);
			g2o::Isometry3D diff = prevPose.inverse() * nextPose;
			g2o::Vector7d diffQT = g2o::internal::toVectorQT(diff);
			for(int i = 0; i < 3; ++i){
				diffQT[i] += distT(gen);
			}
			for(int i = 3; i < 7; ++i){
				diffQT[i] += distR(gen);
			}
			// normalize quaternion
			Eigen::Quaterniond diffQuat(diffQT[6], diffQT[3], diffQT[4], diffQT[5]);
			diffQuat.normalize();
			diffQT[3] = diffQuat.x();
			diffQT[4] = diffQuat.y();
			diffQT[5] = diffQuat.z();
			diffQT[6] = diffQuat.w();

			g2o::Isometry3D diffNoise = g2o::internal::fromVectorQT(diffQT);
			g2o::Isometry3D prevDiffPose = g2o::internal::fromVectorQT(diffPoses[p - 1]);
			g2o::Isometry3D curDiffPose = prevDiffPose * diffNoise;

			diffPoses.push_back(g2o::internal::toVectorQT(curDiffPose));
		}

		ofstream diffTrajFile("../res/diffTraj.txt");
		for(int p = 0; p < diffPoses.size(); ++p){
			diffTrajFile << (p + 1);
			for(int i = 0; i < 7; ++i){
				diffTrajFile << " " << diffPoses[p][i];
			}
			diffTrajFile << endl;
		}

	}
	catch(char const *str){
		cout << "Catch const char* in main(): " << str << endl;
		return -1;
	}
	catch(std::exception& e){
		cout << "Catch std exception in main(): " << e.what() << endl;
	}
	catch(...){
		cout << "Catch ... in main()" << endl;
		return -1;
	}
}
