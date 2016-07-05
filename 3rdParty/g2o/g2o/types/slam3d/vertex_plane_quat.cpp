/*
 * vertex_plane_quat.cpp
 *
 *  Created on: 24 cze 2016
 *      Author: jachu
 */


#include "vertex_plane_quat.h"

namespace g2o{

	VertexPlaneQuat::VertexPlaneQuat() :
	  BaseVertex<3, Eigen::Quaterniond>()
	{
	  setToOriginImpl();
	  updateCache();
	}

	bool VertexPlaneQuat::read(std::istream& is)
	{
	  Vector4D est;
	  for (int i=0; i<4; i++)
		is  >> est[i];
	  setEstimate(Eigen::Quaterniond(est[3], est[0], est[1], est[2]));
	  return true;
	}

	bool VertexPlaneQuat::write(std::ostream& os) const
	{
	  Vector4D est;
	  est[0]=_estimate.x();
	  est[1]=_estimate.y();
	  est[2]=_estimate.z();
	  est[3]=_estimate.w();
	  for (int i=0; i<4; i++)
		os << est[i] << " ";
	  return os.good();
	}

	/**
	* update the position of this vertex. The update is using
	* exponential map from article "Simultaneous Localization
	*  and Mapping with Infinite Planes" by Michael Kaess.
	*/
	void VertexPlaneQuat::oplusImpl(const double* update)
	{
//			std::cout << "VertexPlaneQuat::oplusImpl" << std::endl;
		Eigen::Map<const Vector3D> u(update);
		Vector3D v;

		static constexpr double pi = 3.14159265359;
		v[0] = std::fmod(u[0], pi);
		v[1] = std::fmod(u[1], pi);
		v[2] = std::fmod(u[2], pi);
		double arg = 0.5 * std::sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
		double sincArg = 1.0;
		if(arg > 1e-6){
			sincArg = sin(arg)/arg;
		}
		else{
			//taylor expansion
			sincArg = 1 - arg*arg/6 + pow(arg, 4)/120;
		}
		double cosArg = cos(arg);

		Eigen::Quaterniond increment(cosArg,
									0.5*sincArg*v[0],
									0.5*sincArg*v[1],
									0.5*sincArg*v[2]);

//		normalizeAndUnify(increment);
		_estimate = increment * _estimate;
		_estimate.normalize();

//		if(id() == 881 && arg > 1e-9){
//			using namespace std;
//			cout << "u = " << u << endl;
//			cout << "v = " << v << endl;
//			cout << "increment = " << increment.coeffs() << endl;
//			cout << "_estimate = " << _estimate.coeffs() << endl;
////			char a;
////			cin  >> a;
//		}
//			if(_estimate.w() < 0.0){
//				_estimate.coeffs() = -_estimate.coeffs();
//				_estimate.x() = -_estimate.x();
//				_estimate.y() = -_estimate.y();
//				_estimate.z() = -_estimate.z();
//				_estimate.w() = -_estimate.w();
//			}
//			std::cout << "End VertexPlaneQuat::oplusImpl" << std::endl;
	}

}	//end namespace

