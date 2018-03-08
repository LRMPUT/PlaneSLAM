# PlaneSLAM

An open source project on a plane parametrization in the task of Simultaneous Localization and Mapping.

Prerequesties:  
- Eigen  
- g2o

### Related publications

If you use any part of this work, please cite the appropriate paper:  

    @article{wietrzykowski2016,
      title={{On the Representation of Planes for Efficient Graph-based SLAM with High-level Features}},
      author={J. Wietrzykowski},
      journal={Journal of Automation, Mobile Robotics and Intelligent Systems},
      year={2016},
      number={03},
      pages={3--11},
      volume={10},
      doi={10.14313/JAMRIS_3-2016/18}
    } 

    @inproceedings{wietrzykowski2017,
        author={J. Wietrzykowski and P. Skrzypczyński},
        booktitle={2017 European Conference on Mobile Robots (ECMR)},
        title={{A probabilistic framework for global localization with segmented planes}},
        year={2017},
        volume={},
        number={},
        pages={1-6},
        doi={10.1109/ECMR.2017.8098672},
        ISSN={},
        month={Sept}
    }

### Building:  

Tested on Ubuntu 16.04.  
1. Install Eigen:  
    ```commandline
    sudo apt-get install libeigen3-dev
    ```
    Please ensure that your Eigen version is <= 3.2. Versions >= 3.3 causes alignment issues with g2o.
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
