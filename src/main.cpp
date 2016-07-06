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
#include <chrono>

#include "3rdParty/Eigen/StdVector"

#include "3rdParty/g2o/g2o/types/slam3d/se3quat.h"
#include "3rdParty/g2o/g2o/types/slam3d/edge_se3.h"
#include "3rdParty/g2o/g2o/types/slam3d/vertex_se3.h"
#include "3rdParty/g2o/g2o/types/slam3d/vertex_se3_quat.h"
#include "3rdParty/g2o/g2o/types/slam3d/vertex_plane_quat.h"
#include "3rdParty/g2o/g2o/types/slam3d/edge_se3_plane.h"
#include "3rdParty/g2o/g2o/types/sba/types_six_dof_expmap.h"
#include "3rdParty/g2o/g2o/types/slam3d/isometry3d_mappings.h"
#include "3rdParty/g2o/g2o/types/slam3d/isometry3d_gradients.h"
#include "3rdParty/g2o/g2o/types/slam3d/dquat2mat.h"
#include "3rdParty/g2o/g2o/core/block_solver.h"
#include "3rdParty/g2o/g2o/core/optimization_algorithm_levenberg.h"
#include "3rdParty/g2o/g2o/core/optimization_algorithm_gauss_newton.h"
#include "3rdParty/g2o/g2o/solvers/eigen/linear_solver_eigen.h"
#include "3rdParty/g2o/g2o/solvers/pcg/linear_solver_pcg.h"


using namespace std;

static constexpr double pi = 3.14159265359;


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

Eigen::Quaterniond normAndDToQuat(double d, Eigen::Vector3d norm){
	Eigen::Quaterniond res;
	norm.normalize();
	res.x() = norm[0];
	res.y() = norm[1];
	res.z() = norm[2];
	res.w() = -d;

	g2o::VertexPlaneQuat::normalizeAndUnify(res);
	return res;
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

//		gtPoses = vector<g2o::Vector7d>(gtPoses.begin(), gtPoses.begin() + 100);

		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
//		default_random_engine gen(seed);
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


	    g2o::SparseOptimizer optimizerSE3;
	    {
			g2o::BlockSolver_6_3::LinearSolverType * linearSolverSE3;

			linearSolverSE3 = new g2o::LinearSolverEigen<g2o::BlockSolver_6_3::PoseMatrixType>();

			g2o::BlockSolver_6_3 * solverSE3 = new g2o::BlockSolver_6_3(linearSolverSE3);

			g2o::OptimizationAlgorithmLevenberg* algorithmSE3 = new g2o::OptimizationAlgorithmLevenberg(solverSE3);
			optimizerSE3.setAlgorithm(algorithmSE3);
	    }

	    g2o::SparseOptimizer optimizerMin;
	    {
//	    	g2o::BlockSolver_6_3::LinearSolverType * linearSolverMin = new g2o::LinearSolverEigen<g2o::BlockSolver_6_3::PoseMatrixType>();
//			g2o::BlockSolver_6_3 * solverMin = new g2o::BlockSolver_6_3(linearSolverMin);
//			g2o::OptimizationAlgorithmLevenberg* algorithmMin = new g2o::OptimizationAlgorithmLevenberg(solverMin);

	    	g2o::BlockSolverX::LinearSolverType* linearSolverMin = new g2o::LinearSolverPCG<g2o::BlockSolverX::PoseMatrixType>();
	        g2o::BlockSolverX* solverMin = new g2o::BlockSolverX(linearSolverMin);
	        g2o::OptimizationAlgorithmGaussNewton* algorithmMin = new g2o::OptimizationAlgorithmGaussNewton(solverMin);
//			g2o::OptimizationAlgorithmLevenberg* algorithmMin = new g2o::OptimizationAlgorithmLevenberg(solverMin);

	        optimizerMin.setAlgorithm(algorithmMin);
	    }

	    for(int po = 0; po < odomPoses.size(); ++po){
	    	//SE3
	    	{
				g2o::VertexSE3* curV = new g2o::VertexSE3();
				g2o::SE3Quat poseSE3Quat;
				poseSE3Quat.fromVector(odomPoses[po]);
				curV->setEstimate(g2o::internal::fromSE3Quat(poseSE3Quat));
				curV->setId(po);
				if(po == 0){
					curV->setFixed(true);
				}
				optimizerSE3.addVertex(curV);
	    	}
	    	//minimal
	    	{
				g2o::VertexSE3Quat* curV = new g2o::VertexSE3Quat();
				g2o::SE3Quat poseSE3Quat;
				poseSE3Quat.fromVector(odomPoses[po]);
				curV->setEstimate(poseSE3Quat);
				curV->setId(po);
				if(po == 0){
					curV->setFixed(true);
				}
				optimizerMin.addVertex(curV);
	    	}
	    }
	    for(int pl = 0; pl < planesPoses.size(); ++pl){
	    	//SE3
	    	{
				g2o::VertexSE3* curV = new g2o::VertexSE3();
				g2o::SE3Quat planePoseSE3Quat;
				planePoseSE3Quat.fromVector(planesPoses[pl]);
				curV->setEstimate(g2o::internal::fromSE3Quat(planePoseSE3Quat));
				curV->setId(odomPoses.size() + pl);
//				if(pl == 0){
//					curV->setFixed(true);
//				}
				optimizerSE3.addVertex(curV);
	    	}
	    	//minimal
	    	{
				g2o::VertexPlaneQuat* curV = new g2o::VertexPlaneQuat();
				g2o::SE3Quat planePoseSE3Quat;
				planePoseSE3Quat.fromVector(planesPoses[pl]);
				Eigen::Vector3d norm = planePoseSE3Quat.rotation().toRotationMatrix().block<3, 1>(0, 2);
				Eigen::Vector3d P = planePoseSE3Quat.translation();
				// compute point on the plane from which normal vector intersects with the origin
				double d = P.dot(norm) / norm.dot(norm);

				curV->setEstimate(normAndDToQuat(d, norm));
				curV->setId(odomPoses.size() + pl);
//				if(pl == 0 || pl == 1 || pl == 2){
//					curV->setFixed(true);
//				}
//				curV->setMarginalized(true);
				optimizerMin.addVertex(curV);
	    	}
	    }

	    for(int po = 0; po < gtPoses.size(); ++po){
	    	g2o::SE3Quat poseSE3Quat;
	    	poseSE3Quat.fromVector(gtPoses[po]);
	    	Eigen::Vector3d poseP = poseSE3Quat.translation();
	    	for(int pl = 0; pl < planesPoses.size(); ++pl){
	    		g2o::SE3Quat rawPlanePoseSE3Quat;
	    		rawPlanePoseSE3Quat.fromVector(planesPoses[pl]);

				g2o::SE3Quat rawMeasSE3Quat = poseSE3Quat.inverse() * rawPlanePoseSE3Quat;

	    		// z axis - normal vector
	    		Eigen::Vector3d plNorm = rawMeasSE3Quat.rotation().toRotationMatrix().block<3, 1>(0, 2);
	    		Eigen::Vector3d plP = rawMeasSE3Quat.translation();
	    		// compute point on the plane from which normal vector intersects with camera position (in camera's frame of reference)
	    		double d = plP.dot(plNorm) / plNorm.dot(plNorm);

	    		normal_distribution<double> distTm(0.0, 0.01);
	    		normal_distribution<double> distRm(0.0, 0.01);
	    		//adding noise
	    		d += distTm(gen);
	    		plNorm[0] += distRm(gen);
	    		plNorm[1] += distRm(gen);
	    		plNorm[2] += distRm(gen);
	    		plNorm.normalize();

	    		//SE3 edge
	    		{
					Eigen::Vector3d plIP = d * plNorm;

					Eigen::Vector3d xAxis, yAxis;
					//if normal vector is not parallel to global x axis
					if(plNorm.cross(Eigen::Vector3d(1.0, 0.0, 0.0)).norm() > 1e-2){
						// plane x axis as a cross product - always perpendicular to normal vector
						xAxis = plNorm.cross(Eigen::Vector3d(1.0, 0.0, 0.0));
						xAxis.normalize();
						yAxis = plNorm.cross(xAxis);
					}
					else{
						xAxis = plNorm.cross(Eigen::Vector3d(0.0, 1.0, 0.0));
						xAxis.normalize();
						yAxis = plNorm.cross(xAxis);
					}
					Eigen::Matrix3d plRot;
					plRot.block<3, 1>(0, 0) = xAxis;
					plRot.block<3, 1>(0, 1) = yAxis;
					plRot.block<3, 1>(0, 2) = plNorm;

					g2o::SE3Quat planePoseOrigCamSE3Quat(plRot, plIP);

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

	//	    		Eigen::Matrix<double, 7, 7> jacob;
//					g2o::SE3Quat measSE3Quat = poseSE3Quat.inverse() * planePoseSE3Quat;
	//	    		compJacobB(measSE3Quat.inverse(), jacob);

	//	    		Eigen::Matrix<double, 7, 7> covarPose = jacob * covarPlane * jacob.transpose();
	//	    		Eigen::Matrix<double, 7, 7> infPose = covarPose.inverse();
	//	    		Eigen::Matrix<double, 6, 6> infPose66 = infPose.block<6, 6>(0, 0);
					Eigen::Matrix<double, 7, 7> infPlane = covarPlane.inverse();
					Eigen::Matrix<double, 6, 6> infPlane66 = infPlane.block<6, 6>(0, 0);
	//				Eigen::Matrix<double, 6, 6> infPose66;
	//				infPose66.setIdentity();
//					if(po == 0){
//						cout << "pl = " << pl << endl;
//						cout << "rawPlanePoseSE3Quat.rotation() = " << rawPlanePoseSE3Quat.rotation().vec() << endl;
//						cout << "rawPlanePoseSE3Quat.translation() = " << rawPlanePoseSE3Quat.translation() << endl;
////						cout << "planePoseSE3Quat.translation() = " << planePoseSE3Quat.translation() << endl;
////						cout << "measSE3Quat = " << measSE3Quat.toVector() << endl;
////						cout << "measSE3Quat.inverse() = " << measSE3Quat.inverse().toVector() << endl;
////						cout << "meas rotation = " << measSE3Quat.rotation().matrix() << endl;
//						cout << "covarPlane = " << covarPlane << endl;
//						cout << "dq_dR = " << dq_dR << endl;
//						cout << "covar rot quat = " << dq_dR * covarRotMat * dq_dR.transpose() << endl;
//	//	    			cout << "jacob = " << jacob << endl;
//	//	    			cout << "covarPose = " << covarPose << endl;
//	//	    			cout << "infPose = " << infPose << endl;
//	//	    			cout << "infPose66 = " << infPose66 << endl;
//						cout << "infPlane66 = " << infPlane66 << endl << endl << endl;
//					}
					g2o::EdgeSE3* curEdge = new g2o::EdgeSE3();
					curEdge->setVertex(0, optimizerSE3.vertex(po));
					curEdge->setVertex(1, optimizerSE3.vertex(odomPoses.size() + pl));
					curEdge->setMeasurement(g2o::internal::fromSE3Quat(planePoseOrigCamSE3Quat));
					curEdge->setInformation(infPlane66);


//					if(po == 0){
//						curEdge->computeError();
//						g2o::Vector6d error = curEdge->error();
//						cout << "error = " << error << endl;
//						cout << "cost = " << error.transpose() * infPlane66 * error << endl;
//					}

					optimizerSE3.addEdge(curEdge);
	    		}

	    		// minimal representation
	    		{
					g2o::EdgeSE3Plane* curEdge = new g2o::EdgeSE3Plane();
					curEdge->setVertex(0, optimizerMin.vertex(po));
					curEdge->setVertex(1, optimizerMin.vertex(odomPoses.size() + pl));
					curEdge->setMeasurement(normAndDToQuat(d, plNorm));
					curEdge->setInformation(Eigen::Matrix<double, 3, 3>::Identity());

//					if(po == 0){
//						curEdge->computeError();
//						Eigen::Vector3d error = curEdge->error();
//						g2o::VertexSE3Quat* from = static_cast<g2o::VertexSE3Quat*>(curEdge->vertex(0));
//						Eigen::Quaterniond meas = normAndDToQuat(d, plNorm);
//						g2o::VertexPlaneQuat* to = static_cast<g2o::VertexPlaneQuat*>(curEdge->vertex(1));
//						Eigen::Matrix<double, 4, 4> estFromInv = from->estimate().inverse().to_homogeneous_matrix().transpose();
//						Eigen::Vector4d estPlaneVect = estFromInv * meas.coeffs();
//						Eigen::Quaterniond estPlane(estPlaneVect[3], estPlaneVect[0], estPlaneVect[1], estPlaneVect[2]);
//						estPlane.normalize();
//						Eigen::Quaterniond delta = estPlane.inverse() * to->estimate();
//						cout << "pl = " << pl << endl;
//						cout << "vert 0 est = " << from->estimate().to_homogeneous_matrix() << endl;
//						cout << "vert 0 est inverse transpose = " << from->estimate().inverse().to_homogeneous_matrix().transpose() << endl;
//						cout << "vert 1 est = " << to->estimate().coeffs() << endl;
//						cout << "measurement = " << meas.coeffs() << endl;
//						cout << "estPlane = " << estPlane.coeffs() << endl;
//						cout << "error = " << error << endl << endl << endl;
//					}

//					if(pl == 3){
//						curEdge->computeError();
//						Eigen::Vector3d error = curEdge->error();
//						cout << "error = " << error.transpose() << endl;
//					}

					optimizerMin.addEdge(curEdge);
	    		}
	    	}
	    }

	    // Optimize!
	    static constexpr int maxIter = 10;

	    cout << "optimizerSE3.vertices().size() = " << optimizerSE3.vertices().size() << endl;
	    cout << "optimizerSE3.edges.size() = " << optimizerSE3.edges().size() << endl;
		optimizerSE3.initializeOptimization();
		optimizerSE3.setVerbose(true);
		optimizerSE3.optimize(maxIter);

//		for(auto it = optimizerSE3.edges().begin(); it != optimizerSE3.edges().end(); ++it){
//			g2o::EdgeSE3* curEdge = static_cast<g2o::EdgeSE3*>(*it);
//			if(curEdge->vertex(0)->id() == 0){
//				cout << "edge (" << curEdge->vertex(0)->id() << ", "
//						<< curEdge->vertex(1)->id() << ") = " << endl;
//				cout << "error = " << curEdge->error() << endl;
//				cout << "information = " << curEdge->information() << endl;
//				cout << "cost = " << curEdge->error().transpose() * curEdge->information() * curEdge->error() << endl;
//				cout << "measurement = " << curEdge->measurement().matrix() << endl;
//				cout << "vert 0 est = " << static_cast<g2o::VertexSE3*>(curEdge->vertex(0))->estimate().matrix() << endl;
//				cout << "vert 1 est = " << static_cast<g2o::VertexSE3*>(curEdge->vertex(1))->estimate().matrix() << endl;
//				g2o::Isometry3D diff = curEdge->measurement().inverse() *
//						static_cast<g2o::VertexSE3*>(curEdge->vertex(0))->estimate().inverse() *
//						static_cast<g2o::VertexSE3*>(curEdge->vertex(1))->estimate();
//				cout << "diff = " << diff.matrix() << endl;
//			}
//		}

		ofstream optTrajSE3File("../res/optTrajSE3.txt");
		for(int po = 0; po < odomPoses.size(); ++po){
			g2o::VertexSE3* curPoseVert = static_cast<g2o::VertexSE3*>(optimizerSE3.vertex(po));
			g2o::Vector7d poseVect = g2o::internal::toVectorQT(curPoseVert->estimate());

			optTrajSE3File << (po + 1);
			for(int i = 0; i < 7; ++i){
				optTrajSE3File << " " << poseVect[i];
			}
			optTrajSE3File << endl;
		}

	    cout << "optimizerMin.vertices().size() = " << optimizerMin.vertices().size() << endl;
	    cout << "optimizerMin.edges.size() = " << optimizerMin.edges().size() << endl;
		optimizerMin.initializeOptimization();
		cout << "optimization initialized" << endl;
		optimizerMin.setVerbose(true);
		optimizerMin.optimize(maxIter);
		cout << "optimized" << endl;

		Eigen::Matrix<double, 3, 6> sumJacobXi = Eigen::Matrix<double, 3, 6>::Zero();
		Eigen::Matrix<double, 3, 3> sumJacobXj = Eigen::Matrix<double, 3, 3>::Zero();

		Eigen::Matrix<double, 3, 3> Hk = Eigen::Matrix<double, 3, 3>::Zero();
		Eigen::Matrix<double, 1, 3> bk = Eigen::Matrix<double, 1, 3>::Zero();
		Eigen::Matrix<double, 1, 1> ck = Eigen::Matrix<double, 1, 1>::Zero();
		for(auto it = optimizerMin.edges().begin(); it != optimizerMin.edges().end(); ++it){
			g2o::EdgeSE3Plane* curEdge = static_cast<g2o::EdgeSE3Plane*>(*it);
//			if(curEdge->vertex(0)->id() == 0){
//				cout << "edge (" << curEdge->vertex(0)->id() << ", "
//						<< curEdge->vertex(1)->id() << ") = " << endl;
//
//				Eigen::Vector3d error = curEdge->error();
//				g2o::VertexSE3Quat* from = static_cast<g2o::VertexSE3Quat*>(curEdge->vertex(0));
//				Eigen::Quaterniond meas = curEdge->measurement();
//				g2o::VertexPlaneQuat* to = static_cast<g2o::VertexPlaneQuat*>(curEdge->vertex(1));
//				Eigen::Matrix<double, 4, 4> estFromInv = from->estimate().inverse().to_homogeneous_matrix().transpose();
//				Eigen::Vector4d estPlaneVect = estFromInv * meas.coeffs();
//				Eigen::Quaterniond estPlane(estPlaneVect[3], estPlaneVect[0], estPlaneVect[1], estPlaneVect[2]);
//				estPlane.normalize();
//				Eigen::Quaterniond delta = estPlane.inverse() * to->estimate();
//				sumJacobXi += curEdge->jacobianOplusXi();
//
//				cout << "vert 0 est = " << from->estimate().to_homogeneous_matrix() << endl;
//				cout << "vert 0 est inverse transp = " << from->estimate().inverse().to_homogeneous_matrix().transpose() << endl;
//				cout << "curEdge->jacobianOplusXi() = " << curEdge->jacobianOplusXi() << endl;
//				cout << "vert 1 est = " << to->estimate().coeffs() << endl;
//				cout << "measurement = " << meas.coeffs() << endl;
//				cout << "estPlane = " << estPlane.coeffs() << endl;
//				cout << "error = " << error << endl << endl << endl;
//
////				cout << "information = " << curEdge->information() << endl;
////				cout << "cost = " << curEdge->error().transpose() * curEdge->information() * curEdge->error() << endl;
////				cout << "measurement = " << curEdge->measurement().matrix() << endl;
////				cout << "vert 0 est = " << static_cast<g2o::VertexSE3*>(curEdge->vertex(0))->estimate().matrix() << endl;
////				cout << "vert 1 est = " << static_cast<g2o::VertexSE3*>(curEdge->vertex(1))->estimate().matrix() << endl;
////				g2o::Isometry3D diff = curEdge->measurement().inverse() *
////						static_cast<g2o::VertexSE3*>(curEdge->vertex(0))->estimate().inverse() *
////						static_cast<g2o::VertexSE3*>(curEdge->vertex(1))->estimate();
////				cout << "diff = " << diff.matrix() << endl;
//			}
			if(curEdge->vertex(1)->id() == 883){
				curEdge->computeError();
				curEdge->linearizeOplus();
				Eigen::Matrix<double, 3, 3> J = curEdge->jacobianOplusXj();
				Eigen::Matrix<double, 3, 1> e = curEdge->error();
//				cout << "J = " << J << endl;
//				cout << "e = " << e.transpose() << endl;
//				cout << "cur bk = " << e.transpose() * J << endl;
				Hk += J.transpose() * J;
				bk += e.transpose() * J;
				ck += e.transpose() * e;
			}
		}
//		cout << "sumJacobXi = " << sumJacobXi << endl;
//		cout << "sumJacobXj = " << sumJacobXj << endl;
		cout << "Hk = " << Hk << endl;
		cout << "bk = " << bk << endl;
		cout << "ck = " << ck << endl;

		ofstream optTrajMinFile("../res/optTrajMin.txt");
		for(int po = 0; po < odomPoses.size(); ++po){
			g2o::VertexSE3Quat* curPoseVert = static_cast<g2o::VertexSE3Quat*>(optimizerMin.vertex(po));
			g2o::Vector7d poseVect = curPoseVert->estimate().toVector();

			optTrajMinFile << (po + 1);
			for(int i = 0; i < 7; ++i){
				optTrajMinFile << " " << poseVect[i];
			}
			optTrajMinFile << endl;
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
