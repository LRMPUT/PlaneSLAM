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
#include "3rdParty/g2o/g2o/types/sba/types_six_dof_expmap.h"
#include "3rdParty/g2o/g2o/types/slam3d/isometry3d_mappings.h"
#include "3rdParty/g2o/g2o/types/slam3d/isometry3d_gradients.h"
#include "3rdParty/g2o/g2o/types/slam3d/dquat2mat.h"
#include "3rdParty/g2o/g2o/core/block_solver.h"
#include "3rdParty/g2o/g2o/core/optimization_algorithm_levenberg.h"
#include "3rdParty/g2o/g2o/solvers/eigen/linear_solver_eigen.h"


using namespace std;



//[ 1, 0, 0, 2*aqx*bx + 2*aqy*by + 2*aqz*bz, 2*aqx*by - 2*aqy*bx + 2*aqw*bz, 2*aqx*bz - 2*aqw*by - 2*aqz*bx, 2*aqw*bx - 2*aqz*by + 2*aqy*bz]
//[ 0, 1, 0, 2*aqy*bx - 2*aqx*by - 2*aqw*bz, 2*aqx*bx + 2*aqy*by + 2*aqz*bz, 2*aqw*bx - 2*aqz*by + 2*aqy*bz, 2*aqz*bx + 2*aqw*by - 2*aqx*bz]
//[ 0, 0, 1, 2*aqz*bx + 2*aqw*by - 2*aqx*bz, 2*aqz*by - 2*aqw*bx - 2*aqy*bz, 2*aqx*bx + 2*aqy*by + 2*aqz*bz, 2*aqx*by - 2*aqy*bx + 2*aqw*bz]
//[ 0, 0, 0,                            bqw,                            bqz,                           -bqy,                            bqx]
//[ 0, 0, 0,                           -bqz,                            bqw,                            bqx,                            bqy]
//[ 0, 0, 0,                            bqy,                           -bqx,                            bqw,                            bqz]
//[ 0, 0, 0,                           -bqx,                           -bqy,                           -bqz,                            bqw]
Eigen::Matrix<double, 7, 7> compJacobA(g2o::SE3Quat a, g2o::SE3Quat b){

}

//[ aqw^2 + aqx^2 - aqy^2 - aqz^2,         2*aqx*aqy - 2*aqw*aqz,         2*aqw*aqy + 2*aqx*aqz,    0,    0,    0,   0]
//[         2*aqw*aqz + 2*aqx*aqy, aqw^2 - aqx^2 + aqy^2 - aqz^2,         2*aqy*aqz - 2*aqw*aqx,    0,    0,    0,   0]
//[         2*aqx*aqz - 2*aqw*aqy,         2*aqw*aqx + 2*aqy*aqz, aqw^2 - aqx^2 - aqy^2 + aqz^2,    0,    0,    0,   0]
//[                             0,                             0,                             0,  aqw, -aqz,  aqy, aqx]
//[                             0,                             0,                             0,  aqz,  aqw, -aqx, aqy]
//[                             0,                             0,                             0, -aqy,  aqx,  aqw, aqz]
//[                             0,                             0,                             0, -aqx, -aqy, -aqz, aqw]
void compJacobB(const g2o::SE3Quat& a, Eigen::Matrix<double, 7, 7>& jacob){

	g2o::Vector7d av = a.toVector();
//	g2o::Vector7d bv = b.toVector();
	double ax = av[0];
	double ay = av[1];
	double az = av[2];
	double aqx = av[3];
	double aqy = av[4];
	double aqz = av[5];
	double aqw = av[6];

//	double bx = bv[0];
//	double by = bv[1];
//	double bz = bv[2];
//	double bqx = bv[3];
//	double bqy = bv[4];
//	double bqz = bv[5];
//	double bqw = bv[6];

	jacob << aqw*aqw + aqx*aqx - aqy*aqy - aqz*aqz,         2*aqx*aqy - 2*aqw*aqz,         2*aqw*aqy + 2*aqx*aqz,    0,    0,    0,   0,
			       2*aqw*aqz + 2*aqx*aqy, aqw*aqw - aqx*aqx + aqy*aqy - aqz*aqz,         2*aqy*aqz - 2*aqw*aqx,    0,    0,    0,   0,
			       2*aqx*aqz - 2*aqw*aqy,         2*aqw*aqx + 2*aqy*aqz, aqw*aqw - aqx*aqx - aqy*aqy + aqz*aqz,    0,    0,    0,   0,
			                           0,                             0,                             0,  aqw, -aqz,  aqy, aqx,
			                           0,                             0,                             0,  aqz,  aqw, -aqx, aqy,
			                           0,                             0,                             0, -aqy,  aqx,  aqw, aqz,
			                           0,                             0,                             0, -aqx, -aqy, -aqz, aqw;
}

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
		vector<g2o::Vector7d> odomPoses{initPose};
		for(int po = 1; po < gtPoses.size(); ++po){
			g2o::Isometry3D prevPose = g2o::internal::fromVectorQT(gtPoses[po - 1]);
			g2o::Isometry3D nextPose = g2o::internal::fromVectorQT(gtPoses[po]);
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
			g2o::Isometry3D prevOdomPose = g2o::internal::fromVectorQT(odomPoses[po - 1]);
			g2o::Isometry3D curDiffPose = prevOdomPose * diffNoise;

			odomPoses.push_back(g2o::internal::toVectorQT(curDiffPose));
		}

		ofstream diffTrajFile("../res/odomTraj.txt");
		for(int po = 0; po < odomPoses.size(); ++po){
			diffTrajFile << (po + 1);
			for(int i = 0; i < 7; ++i){
				diffTrajFile << " " << odomPoses[po][i];
			}
			diffTrajFile << endl;
		}

		std::vector<std::vector<Eigen::Vector3d>> planesPoints;

		ifstream planesFile("../res/planes.txt");

		if(!planesFile.is_open()){
			throw "Error - planes file not open";

		}

		while(planesFile.good()){
			vector<Eigen::Vector3d> curPlane;
			int id;
			planesFile >> id;
			for(int v = 0; v < 4; ++v){
				Eigen::Vector3d curPoint;
				for(int c = 0; c < 3; ++c){
					double val;
					planesFile >> val;
					if(planesFile.good()){
						curPoint[c] = val;
					}
				}
				if(planesFile.good()){
//					cout << "curPoint = " << curPoint << endl;
					curPlane.push_back(curPoint);
				}
			}
			if(planesFile.good()){
//				cout << "curPlane.size() = " << curPlane.size() << endl;
				planesPoints.push_back(curPlane);
			}
		}

		// x, y axis on the plane, z normal, position in the middle of the plane
		vector<g2o::Vector7d> planesPoses;
		for(int pl = 0; pl < planesPoints.size(); ++pl){

			Eigen::Vector3d center = planesPoints[pl][0];
			center += (planesPoints[pl][1] - planesPoints[pl][0]) / 2;
			center += (planesPoints[pl][2] - planesPoints[pl][1]) / 2;

			Eigen::Vector3d xAxis = planesPoints[pl][1] - planesPoints[pl][0];
			xAxis.normalize();
			Eigen::Vector3d yAxis = planesPoints[pl][2] - planesPoints[pl][1];
			yAxis.normalize();
			Eigen::Vector3d zAxis = xAxis.cross(yAxis);

			Eigen::Matrix3d curPlaneRot;
			curPlaneRot.block<3, 1>(0, 0) = xAxis;
			curPlaneRot.block<3, 1>(0, 1) = yAxis;
			curPlaneRot.block<3, 1>(0, 2) = zAxis;

			g2o::Isometry3D curPlanePosM;
			curPlanePosM = curPlaneRot;
			curPlanePosM.translation() = center;
			g2o::Vector7d curPlanePosQT = g2o::internal::toVectorQT(curPlanePosM);

			planesPoses.push_back(curPlanePosQT);

//			cout << "planesPoses[" << pl << "] rotation = " << g2o::internal::fromVectorQT(planesPoses[pl]).rotation() << endl;
//			cout << "planesPoses[" << pl << "] translation = " << g2o::internal::fromVectorQT(planesPoses[pl]).translation() << endl;
		}


	    g2o::SparseOptimizer optimizer;
	    g2o::BlockSolver_6_3::LinearSolverType * linearSolver;

	    linearSolver = new g2o::LinearSolverEigen<g2o::BlockSolver_6_3::PoseMatrixType>();

	    g2o::BlockSolver_6_3 * solver_ptr = new g2o::BlockSolver_6_3(linearSolver);

	    g2o::OptimizationAlgorithmLevenberg* solver = new g2o::OptimizationAlgorithmLevenberg(solver_ptr);
	    optimizer.setAlgorithm(solver);

	    for(int po = 0; po < odomPoses.size(); ++po){
	    	g2o::VertexSE3Expmap* curV = new g2o::VertexSE3Expmap();
	    	g2o::SE3Quat poseSE3Quat;
			poseSE3Quat.fromVector(odomPoses[po]);
	    	curV->setEstimate(poseSE3Quat);
	    	curV->setId(po);
	    	if(po == 0){
	    		curV->setFixed(true);
	    	}
	    	optimizer.addVertex(curV);
	    }
	    for(int pl = 0; pl < planesPoses.size(); ++pl){
	    	g2o::VertexSE3Expmap* curV = new g2o::VertexSE3Expmap();
	    	g2o::SE3Quat planePoseSE3Quat;
	    	planePoseSE3Quat.fromVector(planesPoses[pl]);
	    	curV->setEstimate(planePoseSE3Quat);
	    	curV->setId(odomPoses.size() + pl);
//    		curV->setFixed(true);
	    	optimizer.addVertex(curV);
	    }

	    for(int po = 0; po < gtPoses.size(); ++po){
	    	g2o::SE3Quat poseSE3Quat;
	    	poseSE3Quat.fromVector(gtPoses[po]);
	    	Eigen::Vector3d poseP = poseSE3Quat.translation();
	    	for(int pl = 0; pl < planesPoses.size(); ++pl){
	    		g2o::SE3Quat rawPlanePoseSE3Quat;
	    		rawPlanePoseSE3Quat.fromVector(planesPoses[pl]);

	    		// z axis - normal vector
	    		Eigen::Vector3d plNorm = rawPlanePoseSE3Quat.rotation().toRotationMatrix().block<3, 1>(0, 2);
	    		Eigen::Vector3d plP = rawPlanePoseSE3Quat.translation();
	    		// compute point on the plane from which normal vector intersects with camera position
	    		double d = (plP - poseP).dot(plNorm) / plNorm.dot(plNorm);
	    		Eigen::Vector3d plIP = poseP + d * plNorm;

	    		g2o::SE3Quat planePoseSE3Quat(rawPlanePoseSE3Quat.rotation(), plIP);

	    		Eigen::Matrix<double, 9, 9> covarRotMat;
	    		covarRotMat << 	1000.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
								0.0, 1000.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
								0.0, 0.0, 0.01, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
								0.0, 0.0, 0.0, 1000.0, 0.0, 0.0, 0.0, 0.0, 0.0,
								0.0, 0.0, 0.0, 0.0, 1000.0, 0.0, 0.0, 0.0, 0.0,
								0.0, 0.0, 0.0, 0.0, 0.0, 0.01, 0.0, 0.0, 0.0,
								0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.01, 0.0, 0.0,
								0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.01, 0.0,
								0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.01;

	    		Eigen::Matrix<double, 7, 7> covarPlane;
	    		covarPlane << 	1000.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
								0.0, 1000.0, 0.0, 0.0, 0.0, 0.0, 0.0,
								0.0, 0.0, 0.01, 0.0, 0.0, 0.0, 0.0,
								0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
								0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
								0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
								0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0;

	    		Eigen::Matrix<double, 4, 9> dq_dR;
	    		dq_dR << 0,         0,         0,         0,         0,    0.2500,         0,   -0.2500,         0,
	    		         0,         0,   -0.2500,         0,         0,         0,    0.2500,         0,         0,
	    		         0,    0.2500,         0,   -0.2500,         0,         0,         0,         0,         0,
	    		    0.1250,         0,         0,         0,    0.1250,         0,         0,         0,    0.1250;

	    		covarPlane.block<4, 4>(3, 3) = dq_dR * covarRotMat * dq_dR.transpose();

	    		Eigen::Matrix<double, 7, 7> jacob;
	    		g2o::SE3Quat measSE3Quat = planePoseSE3Quat * poseSE3Quat.inverse();
	    		//translation noise
	    		Eigen::Vector3d measTrans = measSE3Quat.translation();
	    		for(int c = 0; c < 3; ++c){
//	    			measTrans[c] += distT(gen);
	    		}
	    		Eigen::Quaterniond measRot = measSE3Quat.rotation();
//	    		measRot.x() += distR(gen);
//				measRot.y() += distR(gen);
//				measRot.z() += distR(gen);
//				measRot.w() += distR(gen);
				measSE3Quat = g2o::SE3Quat(measRot.normalized(), measTrans);
	    		compJacobB(measSE3Quat, jacob);

	    		Eigen::Matrix<double, 7, 7> covarPose = jacob * covarPlane * jacob.transpose();
	    		Eigen::Matrix<double, 7, 7> infPose = covarPose.inverse();
	    		Eigen::Matrix<double, 6, 6> infPose66 = infPose.block<6, 6>(0, 0);
//				Eigen::Matrix<double, 6, 6> infPose66;
//				infPose66.setIdentity();
	    		if(po == 0){
	    			cout << "pl = " << pl << endl;
	    			cout << "rawPlanePoseSE3Quat.rotation() = " << rawPlanePoseSE3Quat.rotation().vec() << endl;
	    			cout << "rawPlanePoseSE3Quat.translation() = " << rawPlanePoseSE3Quat.translation() << endl;
	    			cout << "planePoseSE3Quat.translation() = " << planePoseSE3Quat.translation() << endl;
	    			cout << "measSE3Quat = " << measSE3Quat.toVector() << endl;
	    			cout << "measSE3Quat.inverse() = " << measSE3Quat.inverse().toVector() << endl;
	    			cout << "meas rotation = " << measSE3Quat.rotation().matrix() << endl;
	    			cout << "covarPlane = " << covarPlane << endl;
	    			cout << "dq_dR = " << dq_dR << endl;
	    			cout << "covar rot quat = " << dq_dR * covarRotMat * dq_dR.transpose() << endl;
	    			cout << "jacob = " << jacob << endl;
	    			cout << "covarPose = " << covarPose << endl;
	    			cout << "infPose = " << infPose << endl;
	    			cout << "infPose66 = " << infPose66 << endl << endl << endl;
	    		}
	    		g2o::EdgeSE3* curEdge = new g2o::EdgeSE3();
	    		curEdge->setVertex(0, optimizer.vertex(po));
	    		curEdge->setVertex(1, optimizer.vertex(odomPoses.size() + pl));
	    		curEdge->setMeasurement(measSE3Quat);
	    		curEdge->setInformation(infPose66);

	    		optimizer.addEdge(curEdge);
	    	}
	    }

	    // Optimize!
	    static constexpr int maxIter = 1000;

	    cout << "optimizer.vertices().size() = " << optimizer.vertices().size() << endl;
	    cout << "optimizer.edges.size() = " << optimizer.edges().size() << endl;
		optimizer.initializeOptimization();
		optimizer.optimize(maxIter);

		for(auto it = optimizer.edges().begin(); it != optimizer.edges().end(); ++it){
			g2o::EdgeSE3* curEdge = static_cast<g2o::EdgeSE3*>(*it);
			if(curEdge->vertex(0)->id() == 0){
				cout << "edge (" << curEdge->vertex(0)->id() << ", "
						<< curEdge->vertex(1)->id() << ") = " << endl;
				cout << "error = " << curEdge->error() << endl;
				cout << "measurement = " << curEdge->measurement() << endl;
				cout << "vert 0 est = " << static_cast<g2o::VertexSE3*>(curEdge->vertex(0))->estimate() << endl;
				cout << "vert 1 est = " << static_cast<g2o::VertexSE3*>(curEdge->vertex(1))->estimate() << endl;
				g2o::SE3Quat diff = static_cast<g2o::VertexSE3*>(curEdge->vertex(1))->estimate().inverse() *
						curEdge->measurement() *
						static_cast<g2o::VertexSE3Expmap*>(curEdge->vertex(0))->estimate();
				cout << "diff = " << diff << endl;
			}
		}

		ofstream optTrajFile("../res/optTraj.txt");
		for(int po = 0; po < odomPoses.size(); ++po){
			g2o::VertexSE3Expmap* curPoseVert = static_cast<g2o::VertexSE3Expmap*>(optimizer.vertex(po));
			g2o::SE3Quat poseSE3Quat = curPoseVert->estimate();
			g2o::Vector7d poseVect = poseSE3Quat.toVector();

			optTrajFile << (po + 1);
			for(int i = 0; i < 7; ++i){
				optTrajFile << " " << poseVect[i];
			}
			optTrajFile << endl;
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