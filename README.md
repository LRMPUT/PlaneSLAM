# PlaneSLAM

An open source project on a plane parametrization in the task of Simultaneous Localization and Mapping.

Prerequesties:  
- Eigen  
- g2o

### Related publications

Please cite the appropriate paper:  

[Plane parametrization] Jan Wietrzykowski, **On the Representation of Planes for Efficient Graph-based SLAM with High-level Features**, *Journal of Automation Mobile Robotics and Intelligent Systems*, 10 (3), 2016, pp. 3-11. [PDF](http://www.jamris.org/images/ISSUES/ISSUE-2016-03/03_11_Wietrzykowski-e.pdf)  

[Global localization] Jan Wietrzykowski, Piotr Skrzypczyński, **A Probabilistic Framework for Global Localization with Segmented Planes**, *European Conference on Mobile Robotics*, 2017, pp. 1-6. [PDF](http://ecmr2017.ensta-paristech.fr/images/ECMR_2017_proceedings.pdf)  

### Building:  

Tested on Ubuntu 16.04.  
1. Install Eigen:  
    ```commandline
    sudo apt-get install libeigen3-dev
    ```
    Please ensure that your Eigen version is not beta version. Version 3.3 beta contains a bug that causes system to produce wrong results.
2. Build g2o and install it:  
    ```commandline
    cd 3rdParty/g2o
    mkdir build && cd build
    cmake ..
    make -j$(nproc)
    sudo make install
    ```
3. Build PlaneSLAM:  
    ```commandline
    mkdir build && cd build
    cmake ..
    make -j$(nproc)
    ```

### Launching:  

1. Launch demo:
    ```commandline
    ./PlaneSLAM
    ```