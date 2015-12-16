// -*- C++ -*-
/*!
 * @file  VelocityToTargetPosition.cpp
 * @brief ModuleDescription
 * @date $Date$
 *
 * $Id$
 */

#include "VelocityToTargetPosition.h"

// Module specification
// <rtc-template block="module_spec">
static const char* velocitytotargetposition_spec[] =
  {
    "implementation_id", "VelocityToTargetPosition",
    "type_name",         "VelocityToTargetPosition",
    "description",       "ModuleDescription",
    "version",           "1.0.0",
    "vendor",            "Ogata Lab.",
    "category",          "Converter",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    "conf.default.initial_pose_x", "0.0",
    "conf.default.initial_pose_y", "0.0",
    "conf.default.initial_pose_z", "0.0",
    "conf.default.initial_pose_yaw", "0.0",
    "conf.default.initial_pose_roll", "0.0",
    "conf.default.initial_pose_pitch", "0.0",
    "conf.default.timeout", "-1.0",
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
VelocityToTargetPosition::VelocityToTargetPosition(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_velocityIn("velocity", m_velocity),
    m_targetPositionOut("targetPosition", m_targetPosition)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
VelocityToTargetPosition::~VelocityToTargetPosition()
{
}



RTC::ReturnCode_t VelocityToTargetPosition::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("velocity", m_velocityIn);
  
  // Set OutPort buffer
  addOutPort("targetPosition", m_targetPositionOut);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  bindParameter("initial_pose_x", m_initial_pose_x, "0.0");
  bindParameter("initial_pose_y", m_initial_pose_y, "0.0");
  bindParameter("initial_pose_z", m_initial_pose_z, "0.0");
  bindParameter("initial_pose_yaw", m_initial_pose_yaw, "0.0");
  bindParameter("initial_pose_roll", m_initial_pose_roll, "0.0");
  bindParameter("initial_pose_pitch", m_initial_pose_pitch, "0.0");
  bindParameter("timeout", m_timeout, "0.0");
  // </rtc-template>
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t VelocityToTargetPosition::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t VelocityToTargetPosition::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t VelocityToTargetPosition::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t VelocityToTargetPosition::onActivated(RTC::UniqueId ec_id)
{
  std::cout << "[RTC::VelocityToTargetPosition] onActivated called." << std::endl;
  m_targetPose.position.x = m_initial_pose_x;
  m_targetPose.position.y = m_initial_pose_y;
  m_targetPose.position.z = m_initial_pose_z;
  m_targetPose.orientation.y = m_initial_pose_yaw;
  m_targetPose.orientation.r = m_initial_pose_roll;
  m_targetPose.orientation.p = m_initial_pose_pitch;


  while (!m_velocityIn.isNew()) {
    std::cout << "[RTC::VelocityToTargetPosition] Waiting for First Velocity Command" << std::endl;
    coil::usleep(100*1000); // 100ms sleep
  }
  m_velocityIn.read();
  m_lastVelocityReceivedTime = coil::gettimeofday();
  m_targetPosition.data = m_targetPose;
  setTimestamp<TimedPose3D>(m_targetPosition);
  m_targetPositionOut.write();
  std::cout << "[RTC::VelocityToTargetPosition] onActivated end." << std::endl;  
  return RTC::RTC_OK;
}


RTC::ReturnCode_t VelocityToTargetPosition::onDeactivated(RTC::UniqueId ec_id)
{
  std::cout << "[RTC::VelocityToTargetPosition] onDeactivated called." << std::endl;
  return RTC::RTC_OK;
}


RTC::ReturnCode_t VelocityToTargetPosition::onExecute(RTC::UniqueId ec_id)
{
  coil::TimeValue currentTime = coil::gettimeofday();
  double duration = currentTime - m_lastVelocityReceivedTime;

  if (m_velocityIn.isNew()) {
    // Integration.
    // Here, old value to calculate delta position is used.
    // CAUTION!!! This calulation is too simple. 
    // You need to apply more sophisticated integration method (like Runge-Kutta)
    double dx = m_velocity.data.vx * duration;
    double dy = m_velocity.data.vy * duration;
    double dz = m_velocity.data.vz * duration;
    double dyaw = m_velocity.data.va * duration;
    double droll = m_velocity.data.vr * duration;
    double dpitch = m_velocity.data.vp * duration;
    m_targetPose.position.x += dx;
    m_targetPose.position.y += dy;
    m_targetPose.position.z += dz;
    m_targetPose.orientation.y += dyaw;
    m_targetPose.orientation.r += droll;
    m_targetPose.orientation.p += dpitch;
    m_targetPosition.data = m_targetPose;
    setTimestamp<TimedPose3D>(m_targetPosition);
    m_targetPositionOut.write();

    // Then, update velocity command.
    m_velocityIn.read();
    m_lastVelocityReceivedTime = currentTime;
  } else {
    if (m_timeout > 0 && m_timeout < duration) {
      std::cout << "[RTC::VelocityToTargetPosition] Velocity Command Timeout" << std::endl;      
      return RTC::RTC_ERROR;
    }
  }

  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t VelocityToTargetPosition::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t VelocityToTargetPosition::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t VelocityToTargetPosition::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t VelocityToTargetPosition::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t VelocityToTargetPosition::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void VelocityToTargetPositionInit(RTC::Manager* manager)
  {
    coil::Properties profile(velocitytotargetposition_spec);
    manager->registerFactory(profile,
                             RTC::Create<VelocityToTargetPosition>,
                             RTC::Delete<VelocityToTargetPosition>);
  }
  
};


