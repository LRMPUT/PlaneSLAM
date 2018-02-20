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

#ifndef G2O_TYPES_SLAM3D_EDGE_SE3_PLANE_H_
#define G2O_TYPES_SLAM3D_EDGE_SE3_PLANE_H_

#include "g2o/core/base_binary_edge.h"

#include "g2o_types_slam3d_api.h"
#include "vertex_se3_quat.h"
#include "vertex_plane_quat.h"

namespace g2o {

  /**
   * \brief Edge between 3D pose vertex and plane vertex
   *
   * The transformation between the two vertices is given as an Isometry3D.
   * If z denotes the measurement, then the error function is given as follows:
   * z^-1 * (x_i^-1 * x_j)
   */
  class G2O_TYPES_SLAM3D_API EdgeSE3Plane : public BaseBinaryEdge<3, Eigen::Quaterniond, VertexSE3Quat, VertexPlaneQuat> {
    public:
      EIGEN_MAKE_ALIGNED_OPERATOR_NEW;
      EdgeSE3Plane();
      virtual bool read(std::istream& is);
      virtual bool write(std::ostream& os) const;

      void computeError();

      virtual void setMeasurement(const Eigen::Quaterniond& m){
        _measurement = m;
        _inverseMeasurement = m.inverse();
      }

      virtual bool setMeasurementData(const double* d){
//  		std::cout << "EdgeSE3Plane::setMeasurementData()" << std::endl;
        Eigen::Map<const Vector3D> v(d);
        double w = sqrt(1.0 - v[0]*v[0] - v[1]*v[1] - v[2]*v[2]);
        setMeasurement(Eigen::Quaterniond(w, v[0], v[1], v[2]));
        return true;
//        std::cout << "End EdgeSE3Plane::setMeasurementData()" << std::endl;
      }

      virtual bool getMeasurementData(double* d) const{
//    	  std::cout << "EdgeSE3Plane::getMeasurementData()" << std::endl;
        Eigen::Map<Vector3D> v(d);
        v = _measurement.vec();
        return true;
//        std::cout << "End EdgeSE3Plane::getMeasurementData()" << std::endl;
      }

      void linearizeOplus();

      virtual int measurementDimension() const {return 3;}

//      virtual bool setMeasurementFromState() ;

      virtual double initialEstimatePossible(const OptimizableGraph::VertexSet& /*from*/,
          OptimizableGraph::Vertex* /*to*/) {
        return 1.;
      }

//      virtual void initialEstimate(const OptimizableGraph::VertexSet& from, OptimizableGraph::Vertex* to);

    protected:
      Eigen::Matrix<double, 4, 3> d_plOplus_d_Oplus(Eigen::Quaterniond pl);

      Eigen::Matrix<double, 16, 6> d_poOplus_d_Oplus(Eigen::Matrix<double, 4, 4> poT);

      Eigen::Matrix<double, 4, 16> d_estPlInv_d_poOplus(Eigen::Matrix<double, 4, 4> poT, Eigen::Quaterniond meas);

      Eigen::Matrix<double, 4, 4> d_qNorm_d_q(Eigen::Quaterniond q);

      Eigen::Matrix<double, 4, 4> d_quatMul_d_a(Eigen::Quaterniond a, Eigen::Quaterniond b);

      Eigen::Matrix<double, 4, 4> d_quatMul_d_b(Eigen::Quaterniond a, Eigen::Quaterniond b);

      Eigen::Matrix<double, 3, 4> d_logMap_d_d(Eigen::Quaterniond d);

      Vector3D logMap(Eigen::Quaterniond quat);

      Eigen::Quaterniond _inverseMeasurement;
  };

} //end namespace



#endif /* G2O_TYPES_SLAM3D_EDGE_SE3_PLANE_H_ */
