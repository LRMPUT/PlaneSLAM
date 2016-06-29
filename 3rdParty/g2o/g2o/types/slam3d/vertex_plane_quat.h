/*
 * vertex_plane_quat.h
 *
 *  Created on: 24 cze 2016
 *      Author: jachu
 */

#ifndef G2O_VERTEX_PLANE_QUAT_H_
#define G2O_VERTEX_PLANE_QUAT_H_

#include <iostream>

#include "g2o/config.h"
#include "g2o/core/base_vertex.h"
#include "g2o_types_slam3d_api.h"

namespace g2o{

	class G2O_TYPES_SLAM3D_API VertexPlaneQuat : public BaseVertex<3, Eigen::Quaterniond>
	{
	public:
		EIGEN_MAKE_ALIGNED_OPERATOR_NEW;

		VertexPlaneQuat();

		virtual void setToOriginImpl() {
			_estimate = Eigen::Quaterniond::Identity();
		}

		virtual bool read(std::istream& is);
		virtual bool write(std::ostream& os) const;

		virtual bool setEstimateDataImpl(const double* est){
//			std::cout << "VertexPlaneQuat::setEstimateDataImpl" << std::endl;
			Eigen::Map<const Vector4D> v(est);
			_estimate=Eigen::Quaterniond(v[3], v[0], v[1], v[2]);
			return true;
//			std::cout << "End VertexPlaneQuat::setEstimateDataImpl" << std::endl;
		}

		virtual bool getEstimateData(double* est) const{
//			std::cout << "VertexPlaneQuat::getEstimateData" << std::endl;
			Eigen::Map<Vector4D> v(est);
			v[0] = _estimate.x();
			v[1] = _estimate.y();
			v[2] = _estimate.z();
			v[3] = _estimate.w();
			return true;
//			std::cout << "End VertexPlaneQuat::getEstimateData" << std::endl;
		}

		virtual int estimateDimension() const {
			return 4;
		}

		virtual bool setMinimalEstimateDataImpl(const double* est){
//			std::cout << "VertexPlaneQuat::getMinimalEstimateDataImpl" << std::endl;
			Eigen::Map<const Vector3D> v(est);
			double w = sqrt(1.0 - v[0]*v[0] - v[1]*v[1] - v[2]*v[2]);
			_estimate=Eigen::Quaterniond(w, v[0], v[1], v[2]);
			return true;
//			std::cout << "End VertexPlaneQuat::getMinimalEstimateDataImpl" << std::endl;
		}

		virtual bool getMinimalEstimateData(double* est) const{
//			std::cout << "VertexPlaneQuat::getMinimalEstimateData" << std::endl;
			Eigen::Map<Vector3D> v(est);
			v[0] = _estimate.x();
			v[1] = _estimate.y();
			v[2] = _estimate.z();
			return true;
//			std::cout << "End VertexPlaneQuat::getMinimalEstimateData" << std::endl;
		}

		virtual int minimalEstimateDimension() const {
			return 3;
		}

		/**
		* update the position of this vertex. The update is using
		* exponential map from article "Simultaneous Localization
		*  and Mapping with Infinite Planes" by Michael Kaess.
		*/
		virtual void oplusImpl(const double* update)
		{
//			std::cout << "VertexPlaneQuat::oplusImpl" << std::endl;
			Eigen::Map<const Vector3D> v(update);

			double arg = 0.5 * sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
			double sincArg = 1.0;
			if(arg > 1e-5){
				sincArg = sin(arg)/arg;
			}
			double cosArg = cos(arg);
			double sign = 1.0;
			if(cosArg < 0.0){
				sign = -1.0;
			}

			Eigen::Quaterniond increment(sign*cosArg,
										sign*0.5*sincArg*v[0],
										sign*0.5*sincArg*v[1],
										sign*0.5*sincArg*v[2]);
			_estimate = increment * _estimate;
			_estimate.normalize();
			if(_estimate.w() < 0.0){
				_estimate.coeffs() = -_estimate.coeffs();
//				_estimate.x() = -_estimate.x();
//				_estimate.y() = -_estimate.y();
//				_estimate.z() = -_estimate.z();
//				_estimate.w() = -_estimate.w();
			}
//			std::cout << "End VertexPlaneQuat::oplusImpl" << std::endl;
		}

	};

}	//end namespace



#endif /* G2O_TYPES_SLAM3D_VERTEX_PLANE_H_ */
