/**
 * Copyright (c) 2017, California Institute of Technology.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * The views and conclusions contained in the software and documentation are
 * those of the authors and should not be interpreted as representing official
 * policies, either expressed or implied, of the California Institute of
 * Technology.
 *
 ** continuous_detector.h ******************************************************
 *
 * Wrapper class of TagDetector class which calls TagDetector::detectTags on
 * each newly arrived image published by a camera.
 *
 * $Revision: 1.0 $
 * $Date: 2017/12/17 13:25:52 $
 * $Author: dmalyuta $
 *
 * Originator:        Danylo Malyuta, JPL
 ******************************************************************************/

#ifndef APRILTAGS2_ROS_CONTINUOUS_DETECTOR_H
#define APRILTAGS2_ROS_CONTINUOUS_DETECTOR_H

#include "apriltags2_ros/common_functions.h"
#include <chrono>

namespace apriltags2_ros
{

class ContinuousDetector
{
 public:
  ContinuousDetector(ros::NodeHandle& nh, ros::NodeHandle& pnh);

  void imageCallback(const sensor_msgs::ImageConstPtr& image_rect,
                     const sensor_msgs::CameraInfoConstPtr& camera_info);
  void timerCallback(const ros::TimerEvent& event);

  double time_duration_;
  double x_pos_now__;
  double x_pos_old_;
  double z_distance__;
  double velocity_;
  bool detect_flag_;
  localization_msgs::StopPoints  stopPoints_;
  boost::mutex mutex_;

  TagDetector tag_detector_;
  bool draw_tag_detections_image_;
  cv_bridge::CvImagePtr cv_image_;
//  cv::Mat cv_image_;

  image_transport::ImageTransport it_;
  image_transport::CameraSubscriber camera_image_subscriber_;

  ros::Subscriber pnc_vehicle_info_sub_;
  ros::Subscriber center_vehicle_target_sub_;
  image_transport::Publisher tag_detections_image_publisher_;
  ros::Publisher tag_detections_publisher_;
  ros::Publisher tag_detections_publisher2_;
  ros::Publisher tag_ack_publisher_;
  ros::Timer timer_;

  void do_pnc_vehicle_info_Msg(const pnc_msgs::VehicleInfo& msg);
  void do_center_vehicle_target_Msg(const center_msgs::VehicleTarget& msg);
};

} // namespace apriltags2_ros

#endif // APRILTAGS2_ROS_CONTINUOUS_DETECTOR_H
