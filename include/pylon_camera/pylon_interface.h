/*
 * pylon_interface.h
 *
 *  Created on: May 21, 2015
 *      Author: md
 */

#ifndef PYLON_INTERFACE_H_
#define PYLON_INTERFACE_H_
#include <iostream>
#include <pylon/PylonIncludes.h>
#include <GenApi/IEnumEntry.h>
#include <pylon/usb/BaslerUsbInstantCamera.h>
#include <pylon/gige/BaslerGigEInstantCamera.h>

#include <pylon_camera/pylon_camera_parameter.h>

using std::cout;
using std::cerr;
using std::endl;
using namespace Pylon;

namespace pylon_camera
{

enum PYLON_CAM_TYPE
{
  GIGE = 1, USB = 2, DART = 3,
};

class PylonInterface
{
public:
  PylonInterface();
  virtual ~PylonInterface();

  int initialize(const PylonCameraParameter &params);

  virtual int img_rows();
  virtual int img_cols();
  virtual std::string img_encoding();
  virtual int img_pixel_depth();
  virtual float max_possible_framerate();
  virtual bool has_auto_exposure();
  virtual bool is_cam_removed();
  virtual double last_exposure_val();
  virtual int last_brightness_val();

  virtual int setExposure(double exposure);
  virtual int setBrightness(int brightness);
  int setupCameraConfiguration(const PylonCameraParameter &params);
  const uint8_t* grab(const PylonCameraParameter &params);

  virtual int initSequencer(const PylonCameraParameter &params);

  // Con-/ De-structor automagically calls PylonInitialize and PylonTerminate to ensure the pylon runtime system
  // is initialized during the lifetime of this object.
  Pylon::PylonAutoInitTerm auto_init_term_;

  CInstantCamera* c_instant_cam_; // base camera class

//    virtual int updateRuntimeParameter(const PylonCameraParameter &params);
protected:
  std::string pylonCamTypeToString(const PYLON_CAM_TYPE type);
  int findDesiredCam(const PylonCameraParameter &params);
  PYLON_CAM_TYPE detectPylonCamType(const CInstantCamera* cam);

  Basler_GigECameraParams::PixelFormatEnums gige_img_encoding_;
  Basler_GigECameraParams::PixelSizeEnums gige_img_pixel_depth_;
  Basler_UsbCameraParams::PixelFormatEnums usb_img_encoding_;
  Basler_UsbCameraParams::PixelSizeEnums usb_img_pixel_depth_;

  int img_rows_, img_cols_;
  int height_aoi_, width_aoi_, offset_height_aoi_, offset_width_aoi_;
  float max_framerate_;
  bool has_auto_exposure_;

  PYLON_CAM_TYPE cam_type_;

  // This smart pointer will receive the grab result data.
  CGrabResultPtr ptr_grab_result_;

  CBaslerGigEInstantCamera* gige_cam_;
  CBaslerUsbInstantCamera* usb_cam_;
  CBaslerUsbInstantCamera* dart_cam_;

  double last_exposure_val_;
  int last_brightness_val_;
  bool is_cam_removed_;
};

} /* namespace pylon_camera */

#endif /* PYLON_INTERFACE_H_ */
