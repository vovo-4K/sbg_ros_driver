#include "message_publisher.h"

using sbg::MessagePublisher;

/*!
 * Class to publish all SBG-ROS messages to the corresponding publishers. 
 */
//---------------------------------------------------------------------//
//- Constructor                                                       -//
//---------------------------------------------------------------------//

MessagePublisher::MessagePublisher(void):
m_max_mesages_(10),
m_output_mode_(SBG_ECOM_OUTPUT_MODE_DISABLED)
{

}

//---------------------------------------------------------------------//
//- Private methods                                                   -//
//---------------------------------------------------------------------//

void MessagePublisher::updateOutputConfiguration(SbgEComOutputMode output_conf)
{
  //
  // Update the sbg output configuration if needed.
  // Always get the minimal output configuration (Highest frequency).
  //
  if (m_output_mode_ == SBG_ECOM_OUTPUT_MODE_DISABLED)
  {
    m_output_mode_ = output_conf;
  }
  else
  {
    m_output_mode_ = sbgMin(m_output_mode_, output_conf);
  }

  //
  // In case of sbg output event configuration, just define the output on a 25Hz frequency.
  //
  if (m_output_mode_ >= SBG_ECOM_OUTPUT_MODE_PPS)
  {
    m_output_mode_ = SBG_ECOM_OUTPUT_MODE_DIV_8;
  }
}

void MessagePublisher::initPublisher(ros::NodeHandle *p_ros_node_handle, SbgEComMsgId sbg_msg_id, SbgEComOutputMode output_conf, const std::string &ref_output_topic)
{
  //
  // Check if the publisher has to be initialized.
  //
  if (output_conf != SBG_ECOM_OUTPUT_MODE_DISABLED)
  {
    updateOutputConfiguration(output_conf);

    switch (sbg_msg_id)
    {
      case SBG_ECOM_LOG_STATUS:
        m_sbgStatus_pub_ = p_ros_node_handle->advertise<sbg_driver::SbgStatus>(ref_output_topic, m_max_mesages_);
        break;

      case SBG_ECOM_LOG_UTC_TIME:
        m_sbgUtcTime_pub_ = p_ros_node_handle->advertise<sbg_driver::SbgUtcTime>(ref_output_topic, m_max_mesages_);
        break;

      case SBG_ECOM_LOG_IMU_DATA:
        m_sbgImuData_pub_ = p_ros_node_handle->advertise<sbg_driver::SbgImuData>(ref_output_topic, m_max_mesages_);
        break;

      case SBG_ECOM_LOG_MAG:
        m_sbgMag_pub_ = p_ros_node_handle->advertise<sbg_driver::SbgMag>(ref_output_topic, m_max_mesages_);
        break;

      case SBG_ECOM_LOG_MAG_CALIB:
        m_sbgMagCalib_pub_ = p_ros_node_handle->advertise<sbg_driver::SbgMagCalib>(ref_output_topic, m_max_mesages_);
        break;

      case SBG_ECOM_LOG_EKF_EULER:
        m_sbgEkfEuler_pub_ = p_ros_node_handle->advertise<sbg_driver::SbgEkfEuler>(ref_output_topic, m_max_mesages_);
        break;

      case SBG_ECOM_LOG_EKF_QUAT:
        m_sbgEkfQuat_pub_ = p_ros_node_handle->advertise<sbg_driver::SbgEkfQuat>(ref_output_topic, m_max_mesages_);
        break;

      case SBG_ECOM_LOG_EKF_NAV:

        m_sbgEkfNav_pub_ = p_ros_node_handle->advertise<sbg_driver::SbgEkfNav>(ref_output_topic, m_max_mesages_);
        break;

      case SBG_ECOM_LOG_SHIP_MOTION:

        m_sbgShipMotion_pub_ = p_ros_node_handle->advertise<sbg_driver::SbgShipMotion>(ref_output_topic, m_max_mesages_);
        break;

      case SBG_ECOM_LOG_GPS1_VEL:
      case SBG_ECOM_LOG_GPS2_VEL:

        m_sbgGpsVel_pub_ = p_ros_node_handle->advertise<sbg_driver::SbgGpsVel>(ref_output_topic, m_max_mesages_);
        break;

      case SBG_ECOM_LOG_GPS1_POS:
      case SBG_ECOM_LOG_GPS2_POS:

        m_sbgGpsPos_pub_ = p_ros_node_handle->advertise<sbg_driver::SbgGpsPos>(ref_output_topic, m_max_mesages_);
        break;

      case SBG_ECOM_LOG_GPS1_HDT:
      case SBG_ECOM_LOG_GPS2_HDT:

        m_sbgGpsHdt_pub_ = p_ros_node_handle->advertise<sbg_driver::SbgGpsHdt>(ref_output_topic, m_max_mesages_);
        break;

      case SBG_ECOM_LOG_GPS1_RAW:
      case SBG_ECOM_LOG_GPS2_RAW:

        m_sbgGpsRaw_pub_ = p_ros_node_handle->advertise<sbg_driver::SbgGpsRaw>(ref_output_topic, m_max_mesages_);
        break;

      case SBG_ECOM_LOG_ODO_VEL:

        m_sbgOdoVel_pub_ = p_ros_node_handle->advertise<sbg_driver::SbgOdoVel>(ref_output_topic, m_max_mesages_);
        break;

      case SBG_ECOM_LOG_EVENT_A:

        m_sbgEventA_pub_ = p_ros_node_handle->advertise<sbg_driver::SbgEvent>(ref_output_topic, m_max_mesages_);
        break;

      case SBG_ECOM_LOG_EVENT_B:

        m_sbgEventB_pub_ = p_ros_node_handle->advertise<sbg_driver::SbgEvent>(ref_output_topic, m_max_mesages_);
        break;

      case SBG_ECOM_LOG_EVENT_C:

        m_sbgEventC_pub_ = p_ros_node_handle->advertise<sbg_driver::SbgEvent>(ref_output_topic, m_max_mesages_);
        break;

      case SBG_ECOM_LOG_EVENT_D:

        m_sbgEventD_pub_ = p_ros_node_handle->advertise<sbg_driver::SbgEvent>(ref_output_topic, m_max_mesages_);
        break;

      case SBG_ECOM_LOG_EVENT_E:

        m_sbgEventE_pub_ = p_ros_node_handle->advertise<sbg_driver::SbgEvent>(ref_output_topic, m_max_mesages_);
        break;

      case SBG_ECOM_LOG_DVL_BOTTOM_TRACK:
      case SBG_ECOM_LOG_DVL_WATER_TRACK:
      case SBG_ECOM_LOG_SHIP_MOTION_HP:

        break;

      case SBG_ECOM_LOG_PRESSURE:

        m_sbgPressure_pub_ = p_ros_node_handle->advertise<sbg_driver::SbgPressure>(ref_output_topic, m_max_mesages_);
        break;

      case SBG_ECOM_LOG_USBL:
      case SBG_ECOM_LOG_DEBUG_0:
      case SBG_ECOM_LOG_IMU_RAW_DATA:
      case SBG_ECOM_LOG_DEBUG_1:
      case SBG_ECOM_LOG_DEBUG_2:
      case SBG_ECOM_LOG_DEBUG_3:
      case SBG_ECOM_LOG_IMU_SHORT:
      case SBG_ECOM_LOG_ECOM_NUM_MESSAGES:

        break;
    }
  }
}

void MessagePublisher::defineRosStandardPublishers(ros::NodeHandle *p_ros_node_handle)
{
  if (m_sbgImuData_pub_ && m_sbgEkfQuat_pub_)
  {
    m_imu_pub_ = p_ros_node_handle->advertise<sensor_msgs::Imu>("imu/data", m_max_mesages_);
  }

  if (m_sbgImuData_pub_)
  {
    m_temp_pub_     = p_ros_node_handle->advertise<sensor_msgs::Temperature>("imu/temp", m_max_mesages_);
    m_velocity_pub_ = p_ros_node_handle->advertise<geometry_msgs::TwistStamped>("imu/velocity", m_max_mesages_);
  }
  else
  {
    ROS_WARN("SBG_DRIVER - [Message] SBG Imu data output are not configured, the standard Temperature publisher can not be defined.");
  }

  if (m_sbgMag_pub_)
  {
    m_mag_pub_ = p_ros_node_handle->advertise<sensor_msgs::MagneticField>("imu/mag", m_max_mesages_);
  }
  else
  {
    ROS_WARN("SBG_DRIVER - [Message] SBG Mag data output are not configured, the standard Magnetic publisher can not be defined.");
  }

  if (m_sbgPressure_pub_)
  {
    m_fluid_pub_ = p_ros_node_handle->advertise<sensor_msgs::FluidPressure>("imu/pres", m_max_mesages_);
  }
  else
  {
    ROS_WARN("SBG_DRIVER - [Message] SBG Pressure data output are not configured, the standard FluidPressure publisher can not be defined.");
  }

  if (m_sbgEkfNav_pub_)
  {
    m_pos_ecef_pub_ = p_ros_node_handle->advertise<geometry_msgs::PointStamped>("imu/pos_ecef", m_max_mesages_);
  }
  else
  {
    ROS_WARN("SBG_DRIVER - [Message] SBG Ekf data output are not configured, the standard ECEF position publisher can not be defined.");
  }

  if (m_sbgUtcTime_pub_)
  {
    m_utc_reference_pub_ = p_ros_node_handle->advertise<sensor_msgs::TimeReference>("imu/utc_ref", m_max_mesages_);
  }
  else
  {
    ROS_WARN("SBG_DRIVER - [Message] SBG Utc data output are not configured, the UTC time reference publisher can not be defined.");
  }

  if (m_sbgGpsPos_pub_)
  {
    m_nav_sat_fix_pub_ = p_ros_node_handle->advertise<sensor_msgs::NavSatFix>("imu/nav_sat_fix", m_max_mesages_);
  }
  else
  {
    ROS_WARN("SBG_DRIVER - [Message] SBG GPS Pos data output are not configured, the NavSatFix publisher can not be defined.");
  }
}

void MessagePublisher::publishIMUData(const SbgBinaryLogData &ref_sbg_log)
{
  sbg_driver::SbgImuData sbg_message_imu_old;
  sbg_message_imu_old = m_sbg_imu_message_;

  if (m_sbgImuData_pub_)
  {
    m_sbg_imu_message_ = m_message_wrapper_.createSbgImuDataMessage(ref_sbg_log.imuData);
    m_sbgImuData_pub_.publish(m_sbg_imu_message_);
  }
  if (m_temp_pub_)
  {
    m_temp_pub_.publish(m_message_wrapper_.createRosTemperatureMessage(m_sbg_imu_message_));
  }
  if (m_velocity_pub_)
  {
    m_velocity_pub_.publish(m_message_wrapper_.createRosTwistStampedMessage(m_sbg_imu_message_, sbg_message_imu_old));
  }

  processRosImuMessage();
}

void MessagePublisher::processRosImuMessage(void)
{
  if (m_imu_pub_)
  {
    if (m_sbg_imu_message_.time_stamp == m_sbg_ekf_quat_message_.time_stamp)
    {
      m_imu_pub_.publish(m_message_wrapper_.createRosImuMessage(m_sbg_imu_message_, m_sbg_ekf_quat_message_));
    }
  }
}

void MessagePublisher::publishMagData(const SbgBinaryLogData &ref_sbg_log)
{
  sbg_driver::SbgMag sbg_mag_message;
  sbg_mag_message = m_message_wrapper_.createSbgMagMessage(ref_sbg_log.magData);

  if (m_sbgMag_pub_)
  {
    m_sbgMag_pub_.publish(sbg_mag_message);
  }
  if (m_mag_pub_)
  {
    m_mag_pub_.publish(m_message_wrapper_.createRosMagneticMessage(sbg_mag_message));
  }
}

void MessagePublisher::publishFluidPressureData(const SbgBinaryLogData &ref_sbg_log)
{
  sbg_driver::SbgPressure sbg_pressure_message;
  sbg_pressure_message = m_message_wrapper_.createSbgPressureMessage(ref_sbg_log.pressureData);

  if (m_sbgPressure_pub_)
  {
    m_sbgPressure_pub_.publish(sbg_pressure_message);
  }
  if (m_fluid_pub_)
  {
    m_fluid_pub_.publish(sbg_pressure_message);
  }
}

void MessagePublisher::publishEkfNavigationData(const SbgBinaryLogData &ref_sbg_log)
{
  sbg_driver::SbgEkfNav sbg_ekf_nav_message;
  sbg_ekf_nav_message = m_message_wrapper_.createSbgEkfNavMessage(ref_sbg_log.ekfNavData);

  if (m_sbgEkfNav_pub_)
  {
    m_sbgEkfNav_pub_.publish(sbg_ekf_nav_message);
  }
  if (m_pos_ecef_pub_)
  {
    m_pos_ecef_pub_.publish(m_message_wrapper_.createRosPointStampedMessage(sbg_ekf_nav_message));
  }
}

void MessagePublisher::publishUtcData(const SbgBinaryLogData &ref_sbg_log)
{
  sbg_driver::SbgUtcTime sbg_utc_message;

  sbg_utc_message = m_message_wrapper_.createSbgUtcTimeMessage(ref_sbg_log.utcData);

  if (m_sbgUtcTime_pub_)
  {
    m_sbgUtcTime_pub_.publish(sbg_utc_message);
  }
  if (m_utc_reference_pub_)
  {
    if (sbg_utc_message.clock_status.clock_utc_status != SBG_ECOM_UTC_INVALID)
    {
      m_utc_reference_pub_.publish(m_message_wrapper_.createRosUtcTimeReferenceMessage(sbg_utc_message));
    }
  }
}

void MessagePublisher::publishGpsPosData(const SbgBinaryLogData &ref_sbg_log)
{
  sbg_driver::SbgGpsPos sbg_gps_pos_message;

  sbg_gps_pos_message = m_message_wrapper_.createSbgGpsPosMessage(ref_sbg_log.gpsPosData);

  if (m_sbgGpsPos_pub_)
  {
    m_sbgGpsPos_pub_.publish(sbg_gps_pos_message);
  }
  if (m_nav_sat_fix_pub_)
  {
    m_nav_sat_fix_pub_.publish(m_message_wrapper_.createRosNavSatFixMessage(sbg_gps_pos_message));
  }
}

//---------------------------------------------------------------------//
//- Parameters                                                        -//
//---------------------------------------------------------------------//

int MessagePublisher::getOutputFrequency(void) const
{
  switch (m_output_mode_)
  {
  case SBG_ECOM_OUTPUT_MODE_DISABLED:
    return 0;
  
  case SBG_ECOM_OUTPUT_MODE_MAIN_LOOP:
    return 200;

  case SBG_ECOM_OUTPUT_MODE_DIV_2:
    return 100;

  case SBG_ECOM_OUTPUT_MODE_DIV_4:
    return 50;

  case SBG_ECOM_OUTPUT_MODE_DIV_5:
    return 40;

  case SBG_ECOM_OUTPUT_MODE_DIV_8:
    return 25;

  case SBG_ECOM_OUTPUT_MODE_DIV_10:
    return 20;

  case SBG_ECOM_OUTPUT_MODE_DIV_20:
    return 10;

  case SBG_ECOM_OUTPUT_MODE_DIV_40:
    return 5;

  case SBG_ECOM_OUTPUT_MODE_DIV_200:
    return 1;

  case SBG_ECOM_OUTPUT_MODE_HIGH_FREQ_LOOP:
    return 1000;

  default:
    return 0;
  }
}

//---------------------------------------------------------------------//
//- Operations                                                        -//
//---------------------------------------------------------------------//

void MessagePublisher::initPublishers(ros::NodeHandle *p_ros_node_handle, const ConfigOutput &ref_output_config)
{
  initPublisher(p_ros_node_handle, SBG_ECOM_LOG_STATUS, ref_output_config.getOutputMode(SBG_ECOM_LOG_STATUS), "sbg/status");
  initPublisher(p_ros_node_handle, SBG_ECOM_LOG_UTC_TIME, ref_output_config.getOutputMode(SBG_ECOM_LOG_UTC_TIME), "sbg/utc_time");
  initPublisher(p_ros_node_handle, SBG_ECOM_LOG_IMU_DATA, ref_output_config.getOutputMode(SBG_ECOM_LOG_IMU_DATA), "sbg/imu_data");

  initPublisher(p_ros_node_handle, SBG_ECOM_LOG_MAG, ref_output_config.getOutputMode(SBG_ECOM_LOG_MAG), "sbg/mag");
  initPublisher(p_ros_node_handle, SBG_ECOM_LOG_MAG_CALIB, ref_output_config.getOutputMode(SBG_ECOM_LOG_MAG_CALIB), "sbg/mag_calib");

  initPublisher(p_ros_node_handle, SBG_ECOM_LOG_EKF_EULER, ref_output_config.getOutputMode(SBG_ECOM_LOG_EKF_EULER), "sbg/ekf_euler");
  initPublisher(p_ros_node_handle, SBG_ECOM_LOG_EKF_QUAT, ref_output_config.getOutputMode(SBG_ECOM_LOG_EKF_QUAT), "sbg/ekf_quat");
  initPublisher(p_ros_node_handle, SBG_ECOM_LOG_EKF_NAV, ref_output_config.getOutputMode(SBG_ECOM_LOG_EKF_NAV), "sbg/ekf_nav");

  initPublisher(p_ros_node_handle, SBG_ECOM_LOG_SHIP_MOTION, ref_output_config.getOutputMode(SBG_ECOM_LOG_SHIP_MOTION), "sbg/ship_motion");

  initPublisher(p_ros_node_handle, SBG_ECOM_LOG_GPS1_VEL, ref_output_config.getOutputMode(SBG_ECOM_LOG_GPS1_VEL), "sbg/gps_vel");
  initPublisher(p_ros_node_handle, SBG_ECOM_LOG_GPS1_POS, ref_output_config.getOutputMode(SBG_ECOM_LOG_GPS1_POS), "sbg/gps_pos");
  initPublisher(p_ros_node_handle, SBG_ECOM_LOG_GPS1_HDT, ref_output_config.getOutputMode(SBG_ECOM_LOG_GPS1_HDT), "sbg/gps_hdt");
  initPublisher(p_ros_node_handle, SBG_ECOM_LOG_GPS1_RAW, ref_output_config.getOutputMode(SBG_ECOM_LOG_GPS1_RAW), "sbg/gps_raw");

  initPublisher(p_ros_node_handle, SBG_ECOM_LOG_ODO_VEL, ref_output_config.getOutputMode(SBG_ECOM_LOG_ODO_VEL), "sbg/odo_vel");

  initPublisher(p_ros_node_handle, SBG_ECOM_LOG_EVENT_A, ref_output_config.getOutputMode(SBG_ECOM_LOG_EVENT_A), "sbg/eventA");
  initPublisher(p_ros_node_handle, SBG_ECOM_LOG_EVENT_B, ref_output_config.getOutputMode(SBG_ECOM_LOG_EVENT_B), "sbg/eventB");
  initPublisher(p_ros_node_handle, SBG_ECOM_LOG_EVENT_C, ref_output_config.getOutputMode(SBG_ECOM_LOG_EVENT_C), "sbg/eventC");
  initPublisher(p_ros_node_handle, SBG_ECOM_LOG_EVENT_D, ref_output_config.getOutputMode(SBG_ECOM_LOG_EVENT_D), "sbg/eventD");
  initPublisher(p_ros_node_handle, SBG_ECOM_LOG_EVENT_E, ref_output_config.getOutputMode(SBG_ECOM_LOG_EVENT_E), "sbg/eventE");

  initPublisher(p_ros_node_handle, SBG_ECOM_LOG_PRESSURE, ref_output_config.getOutputMode(SBG_ECOM_LOG_PRESSURE), "sbg/pressure");

  if (ref_output_config.isRosStandardMessagesDefined())
  {
    defineRosStandardPublishers(p_ros_node_handle);
  }

  m_message_wrapper_.setLeapSeconds(ref_output_config.getLeapSeconds());
}

void MessagePublisher::publish(const ros::Time& ref_ros_time, SbgEComClass sbg_msg_class, SbgEComMsgId sbg_msg_id, const SbgBinaryLogData &ref_sbg_log)
{
  //
  // Publish the message with the corresponding publisher and SBG message ID.
  // For each log, check if the publisher has been initialized.
  //
  m_message_wrapper_.setRosProcessingTime(ref_ros_time);

  if(sbg_msg_class == SBG_ECOM_CLASS_LOG_ECOM_0)
  {
    switch (sbg_msg_id)
    {
    case SBG_ECOM_LOG_STATUS:

      if (m_sbgStatus_pub_)
      {
        m_sbgStatus_pub_.publish(m_message_wrapper_.createSbgStatusMessage(ref_sbg_log.statusData));
      }
      break;

    case SBG_ECOM_LOG_UTC_TIME:

      publishUtcData(ref_sbg_log);
      break;

    case SBG_ECOM_LOG_IMU_DATA:

      publishIMUData(ref_sbg_log);
      break;

    case SBG_ECOM_LOG_MAG:

      publishMagData(ref_sbg_log);
      break;

    case SBG_ECOM_LOG_MAG_CALIB:

      if (m_sbgMagCalib_pub_)
      {
        m_sbgMagCalib_pub_.publish(m_message_wrapper_.createSbgMagCalibMessage(ref_sbg_log.magCalibData));
      }
      break;

    case SBG_ECOM_LOG_EKF_EULER:

      if (m_sbgEkfEuler_pub_)
      {
        m_sbgEkfEuler_pub_.publish(m_message_wrapper_.createSbgEkfEulerMessage(ref_sbg_log.ekfEulerData));
      }
      break;

    case SBG_ECOM_LOG_EKF_QUAT:

      if (m_sbgEkfQuat_pub_)
      {
        m_sbg_ekf_quat_message_ = m_message_wrapper_.createSbgEkfQuatMessage(ref_sbg_log.ekfQuatData);
        m_sbgEkfQuat_pub_.publish(m_sbg_ekf_quat_message_);
        processRosImuMessage();
      }
      break;

    case SBG_ECOM_LOG_EKF_NAV:

      publishEkfNavigationData(ref_sbg_log);
      break;

    case SBG_ECOM_LOG_SHIP_MOTION:

      if (m_sbgShipMotion_pub_)
      {
        m_sbgShipMotion_pub_.publish(m_message_wrapper_.createSbgShipMotionMessage(ref_sbg_log.shipMotionData));
      }
      break;

    case SBG_ECOM_LOG_GPS1_VEL:
    case SBG_ECOM_LOG_GPS2_VEL:

      if (m_sbgGpsVel_pub_)
      {
        m_sbgGpsVel_pub_.publish(m_message_wrapper_.createSbgGpsVelMessage(ref_sbg_log.gpsVelData));
      }
      break;

    case SBG_ECOM_LOG_GPS1_POS:
    case SBG_ECOM_LOG_GPS2_POS:

      publishGpsPosData(ref_sbg_log);
      break;

    case SBG_ECOM_LOG_GPS1_HDT:
    case SBG_ECOM_LOG_GPS2_HDT:

      if (m_sbgGpsHdt_pub_)
      {
        m_sbgGpsHdt_pub_.publish(m_message_wrapper_.createSbgGpsHdtMessage(ref_sbg_log.gpsHdtData));
      }
      break;

    case SBG_ECOM_LOG_GPS1_RAW:
    case SBG_ECOM_LOG_GPS2_RAW:

      if (m_sbgGpsRaw_pub_)
      {
        m_sbgGpsRaw_pub_.publish(m_message_wrapper_.createSbgGpsRawMessage(ref_sbg_log.gpsRawData));
      }
      break;

    case SBG_ECOM_LOG_ODO_VEL:

      if (m_sbgOdoVel_pub_)
      {
        m_sbgOdoVel_pub_.publish(m_message_wrapper_.createSbgOdoVelMessage(ref_sbg_log.odometerData));
      }
      break;

    case SBG_ECOM_LOG_EVENT_A:

      if (m_sbgEventA_pub_)
      {
        m_sbgEventA_pub_.publish(m_message_wrapper_.createSbgEventMessage(ref_sbg_log.eventMarker));
      }
      break;

    case SBG_ECOM_LOG_EVENT_B:

      if (m_sbgEventB_pub_)
      {
        m_sbgEventB_pub_.publish(m_message_wrapper_.createSbgEventMessage(ref_sbg_log.eventMarker));
      }
      break;

    case SBG_ECOM_LOG_EVENT_C:

      if (m_sbgEventC_pub_)
      {
        m_sbgEventC_pub_.publish(m_message_wrapper_.createSbgEventMessage(ref_sbg_log.eventMarker));
      }
      break;

    case SBG_ECOM_LOG_EVENT_D:

      if (m_sbgEventD_pub_)
      {
        m_sbgEventD_pub_.publish(m_message_wrapper_.createSbgEventMessage(ref_sbg_log.eventMarker));
      }
      break;

    case SBG_ECOM_LOG_EVENT_E:

      if (m_sbgEventE_pub_)
      {
        m_sbgEventE_pub_.publish(m_message_wrapper_.createSbgEventMessage(ref_sbg_log.eventMarker));
      }
      break;

    case SBG_ECOM_LOG_DVL_BOTTOM_TRACK:
    case SBG_ECOM_LOG_DVL_WATER_TRACK:
    case SBG_ECOM_LOG_SHIP_MOTION_HP:
      break;

    case SBG_ECOM_LOG_PRESSURE:

      publishFluidPressureData(ref_sbg_log);
      break;

    case SBG_ECOM_LOG_USBL:
    case SBG_ECOM_LOG_DEBUG_0:
    case SBG_ECOM_LOG_IMU_RAW_DATA:
    case SBG_ECOM_LOG_DEBUG_1:
    case SBG_ECOM_LOG_DEBUG_2:
    case SBG_ECOM_LOG_DEBUG_3:
    case SBG_ECOM_LOG_IMU_SHORT:
    case SBG_ECOM_LOG_ECOM_NUM_MESSAGES:

      break;
    } 
  }
  else if (sbg_msg_class == SBG_ECOM_CLASS_LOG_ECOM_1)
  {
    switch (sbg_msg_id)
    {
      case SBG_ECOM_LOG_FAST_IMU_DATA:
      break;
    }
  }
}