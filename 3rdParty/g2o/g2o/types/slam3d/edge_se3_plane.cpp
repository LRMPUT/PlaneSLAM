/*
 * edge_se3_plane.cpp
 *
 *  Created on: 27 cze 2016
 *      Author: jachu
 */

#include "edge_se3_plane.h"
#include "isometry3d_gradients.h"
#include <iostream>
#include <iomanip>


namespace g2o {
	using namespace std;
	using namespace Eigen;

	EdgeSE3Plane::EdgeSE3Plane() : BaseBinaryEdge<3, Eigen::Quaterniond, VertexSE3Quat, VertexPlaneQuat>() {
		information().setIdentity();
	}

	bool EdgeSE3Plane::read(std::istream& is) {
		Vector4D meas;
		for (int i=0; i<4; i++)
		  is >> meas[i];
		// normalize the quaternion to recover numerical precision lost by storing as human readable text
		meas.normalize();
		setMeasurement(Quaterniond(meas[3], meas[0], meas[1], meas[2]));

		if (is.bad()) {
		  return false;
		}
		for ( int i=0; i<information().rows() && is.good(); i++)
		  for (int j=i; j<information().cols() && is.good(); j++){
			is >> information()(i,j);
			if (i!=j)
			  information()(j,i)=information()(i,j);
		  }
		if (is.bad()) {
		  //  we overwrite the information matrix with the Identity
		  information().setIdentity();
		}
		return true;
	}

	bool EdgeSE3Plane::write(std::ostream& os) const {
		Vector4D meas;
		meas[0] = _measurement.x();
		meas[1] = _measurement.y();
		meas[2] = _measurement.z();
		meas[3] = _measurement.w();
		for (int i=0; i<4; i++) os  << meas[i] << " ";
		for (int i=0; i<information().rows(); i++)
		  for (int j=i; j<information().cols(); j++) {
			os <<  information()(i,j) << " ";
		  }
		return os.good();
	}

	void EdgeSE3Plane::computeError() {
//		cout << "EdgeSE3Plane::computeError() a" << endl;
		VertexSE3Quat *from = static_cast<VertexSE3Quat*>(_vertices[0]);
		VertexPlaneQuat *to   = static_cast<VertexPlaneQuat*>(_vertices[1]);
		Matrix<double, 4, 4> estFromInvTrans = from->estimate().to_homogeneous_matrix().transpose();
		Vector4D estPlaneVect = estFromInvTrans * to->estimate().coeffs();

		Quaterniond estPlaneInv(estPlaneVect[3], -estPlaneVect[0], -estPlaneVect[1], -estPlaneVect[2]);
//		VertexPlaneQuat::normalizeAndUnify(estPlane);
		estPlaneInv.normalize();
		Quaterniond delta = estPlaneInv * _measurement;
		delta.normalize();
		_error = logMap(delta);

//		if(std::isnan(_error(0)) || std::isnan(_error(1)) || std::isnan(_error(2))){
//			cout << "estPlane.inverse() = " << estPlaneInv.coeffs() << endl;
//			cout << "to->estimate() = " << to->estimate().coeffs() << endl;
//			cout << "delta = " << delta.coeffs() << endl;
//			cout << "_error = " << _error << endl << endl;
//			cout << "acos(delta.w()) = " << acos(min(delta.w(), 1.0)) << endl;
//			char a;
//			cin >> a;
//		}
//		if(to->id() == 883){
//			cout << "estPlane.inverse() = " << estPlaneInv.coeffs() << endl;
//			cout << "to->estimate() = " << to->estimate().coeffs() << endl;
//			cout << "delta = " << delta.coeffs() << endl;
//			cout << "_error = " << std::setprecision(16) << _error << endl << endl << endl;
////			char a;
////			cin >> a;
//		}
//		if(_vertices[0]->id() == 1){
//			cout << "estPlane.inverse() = " << estPlane.inverse().coeffs() << endl;
//			cout << "to->estimate() = " << to->estimate().coeffs() << endl;
//			cout << "delta = " << delta.coeffs() << endl;
//			cout << "_error = " << _error << endl << endl;
//		}
//		cout << "End EdgeSE3Plane::computeError() a" << endl;
	}

//  bool EdgeSE3Plane::setMeasurementFromState(){
//    VertexSE3 *from = static_cast<VertexSE3*>(_vertices[0]);
//    VertexPlane *to   = static_cast<VertexPlane*>(_vertices[1]);
//    Matrix<double, 4, 4> estFromInv = from->estimate().inverse().matrix();
//    Vector4D estPlaneVect = estFromInv;
//    Quaterniond estPlane(estPlaneVect[3], estPlaneVect[0], estPlaneVect[1], estPlaneVect[2]);
//    Quaterniond delta = estPlane.inverse() * to->estimate();
//    setMeasurement(delta);
//    return true;
//  }

	void EdgeSE3Plane::linearizeOplus(){

		BaseBinaryEdge<3, Eigen::Quaterniond, VertexSE3Quat, VertexPlaneQuat>::linearizeOplus();
//		Eigen::Matrix<double, 3, 6> jacobXiComp = _jacobianOplusXi;
//		Eigen::Matrix<double, 3, 3> jacobXjComp = _jacobianOplusXj;
//		if(_vertices[0]->id() == 0 && _vertices[1]->id() == 883){
//			cout << _jacobianOplusXj << endl;
//			char a;
//			cin >> a;
//		}
		return;

		VertexSE3Quat *from = static_cast<VertexSE3Quat*>(_vertices[0]);
		VertexPlaneQuat *to   = static_cast<VertexPlaneQuat*>(_vertices[1]);
		Matrix<double, 4, 4> estFromInv = from->estimate().inverse().to_homogeneous_matrix().transpose();
		Vector4D estPlaneVect = estFromInv * _measurement.coeffs();
		Quaterniond estPlaneInv(estPlaneVect[3], -estPlaneVect[0], -estPlaneVect[1], -estPlaneVect[2]);
		Eigen::Quaterniond estPlaneInvNorm = estPlaneInv.normalized();
		Quaterniond delta = estPlaneInvNorm * to->estimate();
		Vector3D error = logMap(delta);

		Eigen::Matrix<double, 3, 4> d_logMap_d_d_val = d_logMap_d_d(delta);

		if(!from->fixed()){
			Eigen::Matrix<double, 16, 6> d_poOplus_d_Oplus_val = d_poOplus_d_Oplus(from->estimate().to_homogeneous_matrix());
			Eigen::Matrix<double, 16, 6> tmp;
			tmp.block<16, 3>(0, 0) = d_poOplus_d_Oplus_val.block<16, 3>(0, 3);
			tmp.block<16, 3>(0, 3) = d_poOplus_d_Oplus_val.block<16, 3>(0, 0);
			d_poOplus_d_Oplus_val.swap(tmp);
			Eigen::Matrix<double, 4, 16> d_estPlInv_d_poOplus_val = d_estPlInv_d_poOplus(from->estimate().to_homogeneous_matrix(), _measurement);
			Eigen::Matrix<double, 4, 4> d_qNorm_d_q_val = d_qNorm_d_q(estPlaneInv);
			Eigen::Matrix<double, 4, 4> d_quatMul_d_a_val = d_quatMul_d_a(estPlaneInvNorm, to->estimate());

			_jacobianOplusXi = d_logMap_d_d_val * d_quatMul_d_a_val * d_qNorm_d_q_val * d_estPlInv_d_poOplus_val * d_poOplus_d_Oplus_val;

//			cout << "po = " << from->estimate().toVector() << endl;
//			cout << "poT = " << from->estimate().to_homogeneous_matrix() << endl;
//			cout << "poInv = " << from->estimate().inverse().to_homogeneous_matrix() << endl;
//			cout << "poInvTrans = " << from->estimate().inverse().to_homogeneous_matrix().transpose() << endl;
//			cout << "pl = " << to->estimate().coeffs() << endl;
//			cout << "meas = " << _measurement.coeffs() << endl;
//			cout << "estPlaneInv = " << estPlaneInv.coeffs() << endl;
//			cout << "estPlaneInvNorm = " << estPlaneInvNorm.coeffs() << endl;
//			cout << "delta = " << delta.coeffs() << endl;
//			cout << "error = " << error << endl;
//			cout << "d_logMap_d_d_val = " << d_logMap_d_d_val << endl;
//			cout << "d_quatMul_d_a_val = " << d_quatMul_d_a_val << endl;
//			cout << "d_qNorm_d_q_val = " << d_qNorm_d_q_val << endl;
//			cout << "d_estPlInv_d_poOplus_val = " << d_estPlInv_d_poOplus_val << endl;
//			cout << "d_poOplus_d_po = " << d_poOplus_d_Oplus_val << endl;
//			cout << "_jacobianOplusXi = " << _jacobianOplusXi << endl;
//			cout << "jacobXiComp = " << jacobXiComp << endl;
//
//			char a;
//			cin >> a;
		}
		else{
			_jacobianOplusXi = Eigen::Matrix<double, 3, 6>::Zero();
		}

		if(!to->fixed()){
			Eigen::Matrix<double, 4, 3> d_plOplus_d_Oplus_val = d_plOplus_d_Oplus(to->estimate());
			Eigen::Matrix<double, 4, 4> d_quatMul_d_b_val = d_quatMul_d_b(estPlaneInvNorm, to->estimate());
			_jacobianOplusXj = d_logMap_d_d_val * d_quatMul_d_b_val * d_plOplus_d_Oplus_val;

//			if(!from->fixed()){
//				cout << "pl = " << to->estimate().coeffs() << endl;
//				cout << "estPlaneInvNorm = " << estPlaneInvNorm.coeffs() << endl;
//				cout << "d_plOplus_d_Oplus_val = " << d_plOplus_d_Oplus_val << endl;
//				cout << "d_quatMul_d_b_val = " << d_quatMul_d_b_val << endl;
//				cout << "_jacobianOplusXi = " << _jacobianOplusXj << endl;
//				cout << "jacobXiComp = " << jacobXjComp << endl;
//
//				char a;
//				cin >> a;
//			}
		}
		else{
			_jacobianOplusXj = Eigen::Matrix<double, 3, 3>::Zero();
		}

//		if(from->id() != 0){
//			cout << "_jacobianOplusXi = " << _jacobianOplusXi << endl;
//			cout << "jacobXiComp = " << jacobXiComp << endl;
//			cout << "_jacobianOplusXj = " << _jacobianOplusXj << endl;
//			cout << "jacobXjComp = " << jacobXjComp << endl;
//			char a;
//			cin >> a;
//		}
	}

//  void EdgeSE3Plane::initialEstimate(const OptimizableGraph::VertexSet& from_, OptimizableGraph::Vertex* /*to_*/) {
//    VertexSE3 *from = static_cast<VertexSE3*>(_vertices[0]);
//    VertexSE3 *to   = static_cast<VertexSE3*>(_vertices[1]);
//
//    if (from_.count(from) > 0) {
//      to->setEstimate(from->estimate() * _measurement);
//    } else
//      from->setEstimate(to->estimate() * _measurement.inverse());
//    //cerr << "IE" << endl;
//  }


//	[  plqw/2,  plqz/2, -plqy/2]
//	[ -plqz/2,  plqw/2,  plqx/2]
//	[  plqy/2, -plqx/2,  plqw/2]
//	[ -plqx/2, -plqy/2, -plqz/2]
	  Eigen::Matrix<double, 4, 3> EdgeSE3Plane::d_plOplus_d_Oplus(Eigen::Quaterniond pl)
	  {
		  double plqx = pl.x();
		  double plqy = pl.y();
		  double plqz = pl.z();
		  double plqw = pl.w();
		  Eigen::Matrix<double, 4, 3> res;
		  res <<   plqw/2,  plqz/2, -plqy/2,
				  -plqz/2,  plqw/2,  plqx/2,
				   plqy/2, -plqx/2,  plqw/2,
				  -plqx/2, -plqy/2, -plqz/2;

		  return res;
	  }

//	[ p41,   0,   0,    0,  p31, -p21]
//	[ p42,   0,   0,    0,  p32, -p22]
//	[ p43,   0,   0,    0,  p33, -p23]
//	[ p44,   0,   0,    0,  p34, -p24]
//	[   0, p41,   0, -p31,    0,  p11]
//	[   0, p42,   0, -p32,    0,  p12]
//	[   0, p43,   0, -p33,    0,  p13]
//	[   0, p44,   0, -p34,    0,  p14]
//	[   0,   0, p41,  p21, -p11,    0]
//	[   0,   0, p42,  p22, -p12,    0]
//	[   0,   0, p43,  p23, -p13,    0]
//	[   0,   0, p44,  p24, -p14,    0]
//	[   0,   0,   0,    0,    0,    0]
//	[   0,   0,   0,    0,    0,    0]
//	[   0,   0,   0,    0,    0,    0]
//	[   0,   0,   0,    0,    0,    0]
	Eigen::Matrix<double, 16, 6> EdgeSE3Plane::d_poOplus_d_Oplus(Eigen::Matrix<double, 4, 4> poT)
	{
		Eigen::Matrix<double, 16, 6> res;
		double p11 = poT(0, 0);
		double p12 = poT(0, 1);
		double p13 = poT(0, 2);
		double p14 = poT(0, 3);
		double p21 = poT(1, 0);
		double p22 = poT(1, 1);
		double p23 = poT(1, 2);
		double p24 = poT(1, 3);
		double p31 = poT(2, 0);
		double p32 = poT(2, 1);
		double p33 = poT(2, 2);
		double p34 = poT(2, 3);
		double p41 = poT(3, 0);
		double p42 = poT(3, 1);
		double p43 = poT(3, 2);
		double p44 = poT(3, 3);
		res <<  p41,   0,   0,    0,  p31, -p21,
			    p42,   0,   0,    0,  p32, -p22,
				p43,   0,   0,    0,  p33, -p23,
				p44,   0,   0,    0,  p34, -p24,
				  0, p41,   0, -p31,    0,  p11,
				  0, p42,   0, -p32,    0,  p12,
				  0, p43,   0, -p33,    0,  p13,
				  0, p44,   0, -p34,    0,  p14,
				  0,   0, p41,  p21, -p11,    0,
				  0,   0, p42,  p22, -p12,    0,
				  0,   0, p43,  p23, -p13,    0,
				  0,   0, p44,  p24, -p14,    0,
				  0,   0,   0,    0,    0,    0,
				  0,   0,   0,    0,    0,    0,
				  0,   0,   0,    0,    0,    0,
				  0,   0,   0,    0,    0,    0;

		return res;
	}

//	[     -mqx,     -mqy,     -mqz,                             0,        0,        0,        0,                             0,        0,        0,        0,                             0, 0, 0, 0, 0]
//	[        0,        0,        0,                             0,     -mqx,     -mqy,     -mqz,                             0,        0,        0,        0,                             0, 0, 0, 0, 0]
//	[        0,        0,        0,                             0,        0,        0,        0,                             0,     -mqx,     -mqy,     -mqz,                             0, 0, 0, 0, 0]
//	[ -mqx*p14, -mqy*p14, -mqz*p14, - mqx*p11 - mqy*p12 - mqz*p13, -mqx*p24, -mqy*p24, -mqz*p24, - mqx*p21 - mqy*p22 - mqz*p23, -mqx*p34, -mqy*p34, -mqz*p34, - mqx*p31 - mqy*p32 - mqz*p33, 0, 0, 0, 0]
    Eigen::Matrix<double, 4, 16> EdgeSE3Plane::d_estPlInv_d_poOplus(Eigen::Matrix<double, 4, 4> poT, Eigen::Quaterniond meas)
    {
		double p11 = poT(0, 0);
		double p12 = poT(0, 1);
		double p13 = poT(0, 2);
		double p14 = poT(0, 3);
		double p21 = poT(1, 0);
		double p22 = poT(1, 1);
		double p23 = poT(1, 2);
		double p24 = poT(1, 3);
		double p31 = poT(2, 0);
		double p32 = poT(2, 1);
		double p33 = poT(2, 2);
		double p34 = poT(2, 3);
		double p41 = poT(3, 0);
		double p42 = poT(3, 1);
		double p43 = poT(3, 2);
		double p44 = poT(3, 3);
    	double mqx = meas.x();
    	double mqy = meas.y();
    	double mqz = meas.z();
    	double mqw = meas.w();

    	Eigen::Matrix<double, 4, 16> res;
    	res <<      -mqx,     -mqy,     -mqz,                             0,        0,        0,        0,                             0,        0,        0,        0,                             0, 0, 0, 0, 0,
				       0,        0,        0,                             0,     -mqx,     -mqy,     -mqz,                             0,        0,        0,        0,                             0, 0, 0, 0, 0,
				       0,        0,        0,                             0,        0,        0,        0,                             0,     -mqx,     -mqy,     -mqz,                             0, 0, 0, 0, 0,
				 -mqx*p14, -mqy*p14, -mqz*p14, - mqx*p11 - mqy*p12 - mqz*p13, -mqx*p24, -mqy*p24, -mqz*p24, - mqx*p21 - mqy*p22 - mqz*p23, -mqx*p34, -mqy*p34, -mqz*p34, - mqx*p31 - mqy*p32 - mqz*p33, 0, 0, 0, 0;

    	return res;

    }


//    [ (qw^2 + qy^2 + qz^2)/(qw^2 + qx^2 + qy^2 + qz^2)^(3/2),                -(qx*qy)/(qw^2 + qx^2 + qy^2 + qz^2)^(3/2),                -(qx*qz)/(qw^2 + qx^2 + qy^2 + qz^2)^(3/2),                -(qw*qx)/(qw^2 + qx^2 + qy^2 + qz^2)^(3/2)]
//    [                -(qx*qy)/(qw^2 + qx^2 + qy^2 + qz^2)^(3/2), (qw^2 + qx^2 + qz^2)/(qw^2 + qx^2 + qy^2 + qz^2)^(3/2),                -(qy*qz)/(qw^2 + qx^2 + qy^2 + qz^2)^(3/2),                -(qw*qy)/(qw^2 + qx^2 + qy^2 + qz^2)^(3/2)]
//    [                -(qx*qz)/(qw^2 + qx^2 + qy^2 + qz^2)^(3/2),                -(qy*qz)/(qw^2 + qx^2 + qy^2 + qz^2)^(3/2), (qw^2 + qx^2 + qy^2)/(qw^2 + qx^2 + qy^2 + qz^2)^(3/2),                -(qw*qz)/(qw^2 + qx^2 + qy^2 + qz^2)^(3/2)]
//    [                -(qw*qx)/(qw^2 + qx^2 + qy^2 + qz^2)^(3/2),                -(qw*qy)/(qw^2 + qx^2 + qy^2 + qz^2)^(3/2),                -(qw*qz)/(qw^2 + qx^2 + qy^2 + qz^2)^(3/2), (qx^2 + qy^2 + qz^2)/(qw^2 + qx^2 + qy^2 + qz^2)^(3/2)]

    Eigen::Matrix<double, 4, 4> EdgeSE3Plane::d_qNorm_d_q(Eigen::Quaterniond q)
    {
    	double qx = q.x();
    	double qy = q.y();
    	double qz = q.z();
    	double qw = q.w();
    	double denom = pow(qx*qx + qy*qy + qz*qz + qw*qw, (double)3/2);

    	Matrix<double, 4, 4> res;
    	res <<  (qw*qw + qy*qy + qz*qz)/denom,                -(qx*qy)/denom,                -(qx*qz)/denom,                -(qw*qx)/denom,
    			               -(qx*qy)/denom, (qw*qw + qx*qx + qz*qz)/denom,                -(qy*qz)/denom,                -(qw*qy)/denom,
    			               -(qx*qz)/denom,                -(qy*qz)/denom, (qw*qw + qx*qx + qy*qy)/denom,                -(qw*qz)/denom,
    			               -(qw*qx)/denom,                -(qw*qy)/denom,                -(qw*qz)/denom, (qx*qx + qy*qy + qz*qz)/denom;

    	return res;
    }


//    [  bqw,  bqz, -bqy, bqx]
//    [ -bqz,  bqw,  bqx, bqy]
//    [  bqy, -bqx,  bqw, bqz]
//    [ -bqx, -bqy, -bqz, bqw]
    Eigen::Matrix<double, 4, 4> EdgeSE3Plane::d_quatMul_d_a(Eigen::Quaterniond a, Eigen::Quaterniond b)
    {
    	double bqx = b.x();
    	double bqy = b.y();
    	double bqz = b.z();
    	double bqw = b.w();

    	Eigen::Matrix<double, 4, 4> res;
    	res <<   bqw,  bqz, -bqy, bqx,
			    -bqz,  bqw,  bqx, bqy,
			     bqy, -bqx,  bqw, bqz,
			    -bqx, -bqy, -bqz, bqw;

    	return res;
    }

//    [  aqw, -aqz,  aqy, aqx]
//    [  aqz,  aqw, -aqx, aqy]
//    [ -aqy,  aqx,  aqw, aqz]
//    [ -aqx, -aqy, -aqz, aqw]
	Eigen::Matrix<double, 4, 4> EdgeSE3Plane::d_quatMul_d_b(Eigen::Quaterniond a, Eigen::Quaterniond b)
	{
		double aqx = a.x();
		double aqy = a.y();
		double aqz = a.z();
		double aqw = a.w();

		Eigen::Matrix<double, 4, 4> res;
		res <<   aqw, -aqz,  aqy, aqx,
			     aqz,  aqw, -aqx, aqy,
			    -aqy,  aqx,  aqw, aqz,
			    -aqx, -aqy, -aqz, aqw;

		return res;
	}

//    [ (2*acos(dqw)*(dqy^2 + dqz^2))/(dqx^2 + dqy^2 + dqz^2)^(3/2),        -(2*dqx*dqy*acos(dqw))/(dqx^2 + dqy^2 + dqz^2)^(3/2),        -(2*dqx*dqz*acos(dqw))/(dqx^2 + dqy^2 + dqz^2)^(3/2), -(2*dqx)/((1 - dqw^2)^(1/2)*(dqx^2 + dqy^2 + dqz^2)^(1/2))]
//    [        -(2*dqx*dqy*acos(dqw))/(dqx^2 + dqy^2 + dqz^2)^(3/2), (2*acos(dqw)*(dqx^2 + dqz^2))/(dqx^2 + dqy^2 + dqz^2)^(3/2),        -(2*dqy*dqz*acos(dqw))/(dqx^2 + dqy^2 + dqz^2)^(3/2), -(2*dqy)/((1 - dqw^2)^(1/2)*(dqx^2 + dqy^2 + dqz^2)^(1/2))]
//    [        -(2*dqx*dqz*acos(dqw))/(dqx^2 + dqy^2 + dqz^2)^(3/2),        -(2*dqy*dqz*acos(dqw))/(dqx^2 + dqy^2 + dqz^2)^(3/2), (2*acos(dqw)*(dqx^2 + dqy^2))/(dqx^2 + dqy^2 + dqz^2)^(3/2), -(2*dqz)/((1 - dqw^2)^(1/2)*(dqx^2 + dqy^2 + dqz^2)^(1/2))]

    Eigen::Matrix<double, 3, 4> EdgeSE3Plane::d_logMap_d_d(Eigen::Quaterniond d)
    {
    	double dqx = d.x();
		double dqy = d.y();
		double dqz = d.z();
		double dqw = d.w();
		double normSq = dqx*dqx + dqy*dqy + dqz*dqz;
		double denom1 = pow(normSq, (double)3/2);
		double denom2 = pow(normSq, (double)1/2);

		Eigen::Matrix<double, 3, 4> res;
		if(sqrt(normSq) > 1e-9){
			res <<  (2*acos(dqw)*(dqy*dqy + dqz*dqz))/denom1,        -(2*dqx*dqy*acos(dqw))/denom1,        -(2*dqx*dqz*acos(dqw))/denom1, -(2*dqx)/(sqrt(1 - dqw*dqw)*denom2),
						   -(2*dqx*dqy*acos(dqw))/denom1, (2*acos(dqw)*(dqx*dqx + dqz*dqz))/denom1,        -(2*dqy*dqz*acos(dqw))/denom1, -(2*dqy)/(sqrt(1 - dqw*dqw)*denom2),
						   -(2*dqx*dqz*acos(dqw))/denom1,        -(2*dqy*dqz*acos(dqw))/denom1, (2*acos(dqw)*(dqx*dqx + dqy*dqy))/denom1, -(2*dqz)/(sqrt(1 - dqw*dqw)*denom2);
		}
		else{
			res <<  0,	0, 	0, -1.0/1e-9,
					0,	0, 	0, -1.0/1e-9,
					0,	0, 	0, -1.0/1e-9;
		}

		return res;
    }

	Vector3D EdgeSE3Plane::logMap(Eigen::Quaterniond quat)
	{
		Vector3D res;

		double qvNorm = sqrt(quat.x()*quat.x() + quat.y()*quat.y() + quat.z()*quat.z());
		if(qvNorm > 1e-6){
			res[0] = quat.x()/qvNorm;
			res[1] = quat.y()/qvNorm;
			res[2] = quat.z()/qvNorm;
		}
		else{
			// 1/sqrt(3), so norm = 1
			res[0] = 0.57735026919;
			res[1] = 0.57735026919;
			res[2] = 0.57735026919;;
		}
		double acosQw = acos(quat.w());
		res *= 2.0*acosQw;
//		cout << "2.0*acosQw = " << 2.0*acosQw << endl;
		return res;
  }

}
