/*
 * vertex_se3_quat.cpp
 *
 *  Created on: 1 lip 2016
 *      Author: jachu
 */

#include "vertex_se3_quat.h"

namespace g2o{

	VertexSE3Quat::VertexSE3Quat() : BaseVertex<6, SE3Quat>() {
	}

	bool VertexSE3Quat::read(std::istream& is) {
	  Vector7d est;
	  for (int i=0; i<7; i++)
		is  >> est[i];
	  SE3Quat cam2world;
	  cam2world.fromVector(est);
	  setEstimate(cam2world.inverse());
	  return true;
	}

	bool VertexSE3Quat::write(std::ostream& os) const {
	  SE3Quat cam2world(estimate().inverse());
	  for (int i=0; i<7; i++)
		os << cam2world[i] << " ";
	  return os.good();
	}

}

