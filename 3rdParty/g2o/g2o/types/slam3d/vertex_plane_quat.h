/*
    Copyright (c) 2017 Mobile Robots Laboratory at Poznan University of Technology:
    -Jan Wietrzykowski name.surname [at] put.poznan.pl

	This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>
*/

#ifndef G2O_VERTEX_PLANE_QUAT_H_
#define G2O_VERTEX_PLANE_QUAT_H_

#include <iostream>
#include <cmath>

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
			double w = std::sqrt(1.0 - v[0]*v[0] - v[1]*v[1] - v[2]*v[2]);
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
		virtual void oplusImpl(const double* update);

		static void normalizeAndUnify(Eigen::Quaterniond& q){
			q.normalize();
			static constexpr double eps = 1e-9;
			if(q.w() < 0.0 ||
				(fabs(q.w()) < eps && q.z() < 0.0) ||
				(fabs(q.w()) < eps && fabs(q.z()) < eps && q.y() < 0.0) ||
				(fabs(q.w()) < eps && fabs(q.z()) < eps && fabs(q.y()) < eps && q.x() < 0.0))
			{
				q.coeffs() = -q.coeffs();
			}
		}
	};

}	//end namespace



#endif /* G2O_TYPES_SLAM3D_VERTEX_PLANE_H_ */
