/*
 * vertex_se3_quat.h
 *
 *  Created on: 1 lip 2016
 *      Author: jachu
 */

#ifndef G2O_TYPES_SLAM3D_VERTEX_SE3_QUAT_H_
#define G2O_TYPES_SLAM3D_VERTEX_SE3_QUAT_H_

#include "g2o/core/base_vertex.h"
#include "g2o/core/base_binary_edge.h"
#include "g2o/types/slam3d/se3_ops.h"
#include "g2o/types/slam3d/se3quat.h"
#include <Eigen/Geometry>
#include "g2o_types_slam3d_api.h"

namespace g2o{
	/**
	 * \brief SE3 Vertex parameterized internally with a transformation matrix
	 and externally with its exponential map
	 */
	class G2O_TYPES_SLAM3D_API VertexSE3Quat : public BaseVertex<6, SE3Quat>{
	public:
	  EIGEN_MAKE_ALIGNED_OPERATOR_NEW

	  VertexSE3Quat();

	  bool read(std::istream& is);

	  bool write(std::ostream& os) const;

	  virtual void setToOriginImpl() {
		_estimate = SE3Quat();
	  }

	  virtual void oplusImpl(const double* update_)  {
		Eigen::Map<const Vector6d> update(update_);
		Vector6d u = update;
//		u[0] = update[3];
//		u[1] = update[4];
//		u[2] = update[5];
//		u[3] = update[0];
//		u[4] = update[1];
//		u[5] = update[2];
//		if(id() == 1 && u.norm() > 1e-9){
//			using namespace std;
//			cout << "increment = " << SE3Quat::exp(u).to_homogeneous_matrix() << endl;
//			cout << "estimate = " << _estimate.to_homogeneous_matrix() << endl;
//		}
		setEstimate(SE3Quat::exp(u)*estimate());
	  }
	};

}

#endif /* G2O_TYPES_SLAM3D_VERTEX_SE3_QUAT_H_ */
