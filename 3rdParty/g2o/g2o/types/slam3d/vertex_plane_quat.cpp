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

}	//end namespace

