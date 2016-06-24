/*
 * vertex_plane_quat.h
 *
 *  Created on: 24 cze 2016
 *      Author: jachu
 */

#ifndef G2O_VERTEX_PLANE_QUAT_H_
#define G2O_VERTEX_PLANE_QUAT_H_

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
			Eigen::Map<const Vector4D> v(est);
			_estimate=Eigen::Quaterniond(est[3], est[0], est[1], est[2]);
			return true;
		}

		virtual bool getEstimateData(double* est) const{
			Eigen::Map<Vector4D> v(est);
			v[0] = _estimate.x();
			v[1] = _estimate.y();
			v[2] = _estimate.z();
			v[3] = _estimate.w();
			return true;
		}

		virtual int estimateDimension() const {
			return 4;
		}

		virtual bool setMinimalEstimateDataImpl(const double* est){
			Eigen::Map<const Vector3D> v(est);
			double w = sqrt(1.0 - est[0]*est[0] - est[1]*est[1] - est[2]*est[2]);
			_estimate=Eigen::Quaterniond(w, est[0], est[1], est[2]);
			return true;
		}

		virtual bool getMinimalEstimateData(double* est) const{
			Eigen::Map<Vector6d> v(est);
			v[0] = _estimate.x();
			v[1] = _estimate.y();
			v[2] = _estimate.z();
			return true;
		}

		virtual int minimalEstimateDimension() const {
			return 3;
		}

		/**
		* update the position of this vertex. The update is using
		* exponential map from article "Simultaneous Localization
		*  and Mapping with Infinite Planes by Michael Kaess.
		*/
		virtual void oplusImpl(const double* update)
		{
			Eigen::Map<const Vector3D> v(update);
			double arg = 0.5 * sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
			double sinc =
			Isometry3D increment = internal::fromVectorMQT(v);
			_estimate = _estimate * increment;
			if (++_numOplusCalls > orthogonalizeAfter) {
			  _numOplusCalls = 0;
			  internal::approximateNearestOrthogonalMatrix(_estimate.matrix().topLeftCorner<3,3>());
			}
		}

	};

}	//end namespace



#endif /* 3RDPARTY_G2O_G2O_TYPES_SLAM3D_VERTEX_PLANE_H_ */
