// g2o - General Graph Optimization
// Copyright (C) 2011 R. Kuemmerle, G. Grisetti, W. Burgard
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
// * Redistributions of source code must retain the above copyright notice,
//   this list of conditions and the following disclaimer.
// * Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the
//   documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
// IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
// TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
// PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
// TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

// New edge using only reprojection error - Michal Nowicki 2016


#include "edge_se3_pointxyz_reprojectionError.h"

namespace g2o {
  using namespace g2o;

  // point to camera projection, monocular
  EdgeSE3PointXYZReprojectionError::EdgeSE3PointXYZReprojectionError() : BaseBinaryEdge<2, Vector2D, VertexSE3, VertexPointXYZ>() {
    resizeParameters(1);
    installParameter(params, 0);
    information().setIdentity();
//    J.fill(0);
//    J.block<2,2>(0,0) = -Matrix3D::Identity();
  }

  bool EdgeSE3PointXYZReprojectionError::resolveCaches(){
    ParameterVector pv(1);
    pv[0]=params;
    resolveCache(cache, (OptimizableGraph::Vertex*)_vertices[0],"CACHE_CAMERA",pv);
    return cache != 0;
  }




  bool EdgeSE3PointXYZReprojectionError::read(std::istream& is) {
    int pid;
    is >> pid;
    setParameterId(0,pid);

    // measured keypoint
    Vector2D meas;
    for (int i=0; i<2; i++) is >> meas[i];
    setMeasurement(meas);
    // don't need this if we don't use it in error calculation (???)
    // information matrix is the identity for features, could be changed to allow arbitrary covariances
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
      //  we overwrite the information matrix
      information().setIdentity();
    }
    return true;
  }

  bool EdgeSE3PointXYZReprojectionError::write(std::ostream& os) const {
    os << params->id() << " ";
    for (int i=0; i<2; i++) os  << measurement()[i] << " ";
    for (int i=0; i<information().rows(); i++)
      for (int j=i; j<information().cols(); j++) {
        os <<  information()(i,j) << " ";
      }
    return os.good();
  }


  void EdgeSE3PointXYZReprojectionError::computeError() {
    // from cam to point (track)
    //VertexSE3 *cam = static_cast<VertexSE3*>(_vertices[0]);
    VertexPointXYZ *point = static_cast<VertexPointXYZ*>(_vertices[1]);

    Vector3D p = cache->w2i() * point->estimate();

    // error, which is backwards from the normal observed - calculated
    // _measurement is the measured projection
    _error = p.head<2>() - _measurement;
    //    std::cout << _error << std::endl << std::endl;
  }

//  void EdgeSE3PointXYZReprojectionError::linearizeOplus() {
//    //VertexSE3 *cam = static_cast<VertexSE3 *>(_vertices[0]);
//    VertexPointXYZ *vp = static_cast<VertexPointXYZ *>(_vertices[1]);
//
//    const Vector3D& pt = vp->estimate();
//
//    Vector3D Zcam = cache->w2l() * pt;
//
//    //  J(0,3) = -0.0;
//    J(0,4) = -2*Zcam(2);
//    J(0,5) = 2*Zcam(1);
//
//    J(1,3) = 2*Zcam(2);
//    //  J(1,4) = -0.0;
//    J(1,5) = -2*Zcam(0);
//
//    J(2,3) = -2*Zcam(1);
//    J(2,4) = 2*Zcam(0);
//    //  J(2,5) = -0.0;
//
//    J.block<3,3>(0,6) = cache->w2l().rotation();
//
//    Eigen::Matrix<double,3,9,Eigen::ColMajor> Jprime = params->Kcam_inverseOffsetR()  * J;
//    Vector3D Zprime = cache->w2i() * pt;
//
//    Eigen::Matrix<double,3,9,Eigen::ColMajor> Jhom;
//    Jhom.block<2,9>(0,0) = 1/(Zprime(2)*Zprime(2)) * (Jprime.block<2,9>(0,0)*Zprime(2) - Zprime.head<2>() * Jprime.block<1,9>(2,0));
//    Jhom.block<1,9>(2,0) = Jprime.block<1,9>(2,0);
//
//    _jacobianOplusXi = Jhom.block<3,6>(0,0);
//    _jacobianOplusXj = Jhom.block<3,3>(0,6);
//  }


  bool EdgeSE3PointXYZReprojectionError::setMeasurementFromState(){
    //VertexSE3 *cam = static_cast<VertexSE3*>(_vertices[0]);
    VertexPointXYZ *point = static_cast<VertexPointXYZ*>(_vertices[1]);

    // calculate the projection
    const Vector3D& pt = point->estimate();

    Vector3D p = cache->w2i() * pt;
    _measurement = p.head<2>();
    return true;
  }


  void EdgeSE3PointXYZReprojectionError::initialEstimate(const OptimizableGraph::VertexSet& from, OptimizableGraph::Vertex* /*to_*/)
  {
    (void) from;
    assert(from.size() == 1 && from.count(_vertices[0]) == 1 && "Can not initialize VertexDepthCam position by VertexTrackXYZ");

    VertexSE3 *cam = dynamic_cast<VertexSE3*>(_vertices[0]);
    VertexPointXYZ *point = dynamic_cast<VertexPointXYZ*>(_vertices[1]);
    const Eigen::Matrix<double, 3, 3, Eigen::ColMajor>& invKcam = params->invKcam();
    Vector3D p;
    p(2) = 3.5;
    p.head<2>() = _measurement*p(2);
    p=invKcam*p;
    point->setEstimate(cam->estimate() * (params->offset() * p));
  }

}
