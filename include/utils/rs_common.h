/*
 * @Description: RS lidar扩展
 * @Author: wql
 * @Date: 2020-12-07 16:42:23
 * @LastEditTime: 2020-12-08 15:39:51
 * @LastEditors: wql
 */
#ifndef ROBOSENSE_CORRECTION_HPP
#define ROBOSENSE_CORRECTION_HPP

#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>
#include <pcl_ros/point_cloud.h>
#include <angles/angles.h>
#include <iostream>
#include <vector>

#include <utils/pcl_utils.h>


namespace licalib {

class RobosenseCorrection {

public:
    typedef std::shared_ptr<RobosenseCorrection> Ptr;

    enum ModelType {
        RS_128
    };

    RobosenseCorrection(ModelType modelType = RS_128) : modelType_(modelType){

    }

    void unpackScan(const sensor_msgs::PointCloud2::ConstPtr &lidarMsg, TPointCloud &outPointCloud){
        RsPointCloud rs_pc;
        pcl::fromROSMsg(*lidarMsg,rs_pc); ///

        outPointCloud.clear();
        outPointCloud.header = pcl_conversions::toPCL(lidarMsg); ///
        outPointCloud.heigth = rs_pc.height;
        outPointCloud.width = rs_pc.width;
        outPointCloud.is_dense = false;
        outPointCloud.resize(outPointCloud.height * outPointCloud.width);

        double timeBase = lidarMsg->header.stamp.toSec(); ///
        int height = rs_pc.height;
        int width = rs_pc.width;
        for(int h = 0; h < height; h++){
            for(int w = 0; w < width; w++){
                TPoint tp;
                tp.x = rs_pc.at(w,h).x;
                tp.y = rs_pc.at(w,h).y;
                tp.z = rs_pc.at(w,h).z;
                tp.intensity = rs_pc.at(w,h).intensity;
                tp.timestamp = rs_pc.at(w,h).timestamp;
                outPointCloud.at(w,h) = tp;
            }
        }

    }
    

private:
    ModelType modelType_;

};

}

#endif