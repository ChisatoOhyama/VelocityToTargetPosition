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
    "vendor",            "pretty",
    "category",          "Convete",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
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
  return RTC::RTC_OK;
}


RTC::ReturnCode_t VelocityToTargetPosition::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t VelocityToTargetPosition::onExecute(RTC::UniqueId ec_id)
{
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


