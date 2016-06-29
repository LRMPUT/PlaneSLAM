/*
 * edge_se3_plane.cpp
 *
 *  Created on: 27 cze 2016
 *      Author: jachu
 */

#include "edge_se3_plane.h"
#include "isometry3d_gradients.h"
#include <iostream>


namespace g2o {
	using namespace std;
	using namespace Eigen;

	EdgeSE3Plane::EdgeSE3Plane() : BaseBinaryEdge<3, Eigen::Quaterniond, VertexSE3, VertexPlaneQuat>() {
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
		VertexSE3 *from = static_cast<VertexSE3*>(_vertices[0]);
		VertexPlaneQuat *to   = static_cast<VertexPlaneQuat*>(_vertices[1]);
		Matrix<double, 4, 4> estFromInv = from->estimate().inverse().matrix();
		Vector4D estPlaneVect = estFromInv * _measurement.coeffs();
		Quaterniond estPlane(estPlaneVect[3], estPlaneVect[0], estPlaneVect[1], estPlaneVect[2]);
		estPlane.normalize();
		Quaterniond delta = estPlane.inverse() * to->estimate();
		_error = logMap(delta);
//		cout << "estPlane.inverse() = " << estPlane.inverse().coeffs() << endl;
//		cout << "to->estimate() = " << to->estimate().coeffs() << endl;
//		cout << "delta = " << delta.coeffs() << endl;
//		cout << "_error = " << _error << endl;
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

//  void EdgeSE3::linearizeOplus(){
//
//    // BaseBinaryEdge<6, Isometry3D, VertexSE3, VertexSE3>::linearizeOplus();
//    // return;
//
//    VertexSE3 *from = static_cast<VertexSE3*>(_vertices[0]);
//    VertexSE3 *to   = static_cast<VertexSE3*>(_vertices[1]);
//    Isometry3D E;
//    const Isometry3D& Xi=from->estimate();
//    const Isometry3D& Xj=to->estimate();
//    const Isometry3D& Z=_measurement;
//    internal::computeEdgeSE3Gradient(E, _jacobianOplusXi , _jacobianOplusXj, Z, Xi, Xj);
//  }

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

	Vector3D EdgeSE3Plane::logMap(Eigen::Quaterniond quat)
	{
		Vector3D res = Vector3D::Ones();

		double qvNorm = sqrt(quat.x()*quat.x() + quat.y()*quat.y() + quat.z()*quat.z());
		if(qvNorm > 1e-5){
		  res[0] *= quat.x()/qvNorm;
		  res[1] *= quat.y()/qvNorm;
		  res[2] *= quat.z()/qvNorm;
		}
		double acosQw = acos(quat.w());
		res *= 2.0*acosQw;
		return res;
  }

}
