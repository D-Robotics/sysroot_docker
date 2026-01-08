/****************************************************************************\
*
*COPYRIGHT(c) 2022 by Ofilm Micro Electronic, Inc.
*
*This file belongs to Ofilm Micro Electronic, Inc. It is considered a trade secret,
*and is not to be divulged or used by parties who have not
*received written authorization from the owner.
*
\****************************************************************************/
#ifndef __DEPTHMAP_WRAPPER_H__
#define __DEPTHMAP_WRAPPER_H__

//==============================================================================
// Included modules
//==============================================================================
#include <stdint.h>
#include <stdbool.h>

//==============================================================================
// MACROS
//==============================================================================
#ifdef _MSC_VER
#define CP_DLL_PUBLIC __declspec(dllexport)
#else
#define CP_DLL_PUBLIC __attribute__ ((visibility ("default")))
#endif

#define IMG_UNUSED(x) (void)(x)

//==============================================================================
// DECLARATIONS
//==============================================================================
typedef enum{
  MODE_HYBRID_DUAL_HDR_25 = 0,
}TofModeHybird;

typedef enum{
  MODE_SPOT_HDR_12 = 0,
}TofModeSpot;

typedef enum  
{
  IRS2381C,
  IRS2381C_MTP006,
  IRS2875C,
  IRS2875C_LIOW2,
  IRS2875C_OZT338B,
  IRS2875C_OZT613,
  IRS2875C_OZT613_20,
  IRS2875C_OZT797,
  IRS2875C_Pinocchio,
  IRS2875C_Pinocchio_EVO3,
  IRS2877A_OZT526,
  IRS2877C,
  IRS2877C_OZT224,
  IRS2877C_Spot,
  IRS2976C,
}SupportedModule;

typedef enum  
{
  RARDATA_FLOOD,
  RARDATA_SPOT,
}RawdataType;

typedef struct {
	float x;
	float y;
	float z;
	float confidence;
}PointCloudPack;

typedef struct 
{
	float	   principalPoint[2];		      //!< cx/cy
	float	   focalLength[2]; 		        //!< fx/fy
	float	   distortionTangential[2];   //!< p1/p2
	float	   distortionRadial[3];	      //!< k1/k2/k3
}WrapperDepthCamLensParameters;

// Class factories
#ifdef __cplusplus
extern "C" 
{
#endif

/**
 * @brief   enable log print
 * 
 * @param[in]   printEnable   true：print  false：not print    
 *
 * @return 无
*/
CP_DLL_PUBLIC
void DepthMapWrapperSetLogPrintfEnable(bool pState);

//tof1 interface function(for 0896-50 decoding)
/**
 * @brief   sdk Initialize
 * 
 * @param[in]   i2cDevice           i2c device
 * @param[in]   caliFileDirectory   calibration file directory(e.g.:/mnt/data/)
 * @param[in]   module              module type
 *
 * @return  None
*/
CP_DLL_PUBLIC
void DepthMapWrapperSetUp1(char *i2cDevice, char *caliFileDirectory, SupportedModule module);

/**
 * @brief   sdk deregistration
 * 
 * @return  None
*/
CP_DLL_PUBLIC
void DepthMapWrapperTearDown1(); 

/**
 * @brief   get module calibration file form tof sensor
 * 
 * @param[in]   i2cDevice           i2c device
 * @param[in]   caliFilePath        calibration file storage path(e.g.:/mnt/data/pmd1.spc)
 * 
 * @return  execution result: true:success false:failure
*/
CP_DLL_PUBLIC
bool DepthMapWrapperGetCalibrationData1(char *i2cDevice, char *caliFilePath);	

/**
 * @brief   get lens parameters
 * 
 * @param[out]   lensParams      lens parameters
 *
 * @return  execution result: true:success false:failure
*/
CP_DLL_PUBLIC 
bool DepthMapWrapperGetLensParameters1(WrapperDepthCamLensParameters *lensParams);

/**
 * @brief   set usecase
 * 
 * @param[in]   usecaseIndex      usecase index
 *
 * @return  execution result: true:success false:failure
*/
CP_DLL_PUBLIC
bool DepthMapWrapperSetUseCase1(int usecaseIndex);

/**
 * @brief   updata auto exposure time to tof sensor
 * 
 * @param[in]   rawdataType         rawdata type
 * @param[out]  tofExposureTime     auto exposure time
 * 
 * @return  execution result: true:success false:failure
*/
CP_DLL_PUBLIC
bool DepthMapWrapperUpdateAutoExposureTime1(RawdataType rawdataType, uint32_t *tofExposureTime);

/**
 * @brief   enable auto exposure
 * 
 * @param[in]   aeEnable   true：auto exposure  false：manual exposure     
 *
 * @return  execution result: true:success false:failure
*/
CP_DLL_PUBLIC
bool DepthMapWrapperSetAutoExposureEnabled1(bool aeEnable);

/**
 * @brief   start recording rrf file
 * 
 * @param[in]   rrfFileDirectory      rrffile storage directory(e.g.:/mnt/data/)
 * 
 * @param[in]   usecaseIndex          usecase index
 *
 * @return  None
*/
CP_DLL_PUBLIC
void DepthMapWrapperStartRecRrf1(const char *rrfFileDirectory, int32_t usecaseIndex);

/**
 * @brief   stop recording rrf file
 *
 * @return  None
*/
CP_DLL_PUBLIC
void DepthMapWrapperStopRecRrf1();

/**
 * @brief   rawdata decode
 * 
 * @param[in]    rawdataBuff      rawdata
 * @param[out]   irImage          ir image data
 * @param[out]   depthImage       depth image data
 * @param[out]   pointCloudImage  point cloud data
 * @param[out]   pointCloudCount  point cloud data count
 * @param[out]   dataType         data type
 * 
 * @return  execution result: true:success false:failure
*/
CP_DLL_PUBLIC
bool DepthMapWrapperProcessFrameHybrid1(char *rawdataBuff,  char *irImage, char *depthImage, 
                                        char *pointCloudImage, unsigned int *pointCloudCount, 
                                        RawdataType *rawdataType);

//tof2 interface function(for 0951 decoding)
/**
 * @brief   sdk Initialize
 * 
 * @param[in]   i2c_name            i2c device
 * @param[in]   caliFileDirectory   calibration file directory(e.g.:/mnt/data/)
 * @param[in]   module              module type
 *
 * @return None
*/
CP_DLL_PUBLIC
void DepthMapWrapperSetUp2(char* i2cDevice, char *caliFileDirectory, SupportedModule module);

/**
 * @brief   sdk deregistration
 * 
 * @return  None
*/
CP_DLL_PUBLIC
void DepthMapWrapperTearDown2(); 

/**
 * @brief   get module calibration file form tof sensor
 * 
 * @param[in]   i2cDevice           i2c device
 * @param[in]   caliFilePath        calibration file storage path(e.g.:/mnt/data/pmd2.spc)
 * 
 * @return  execution result: true:success false:failure
*/
CP_DLL_PUBLIC
bool DepthMapWrapperGetCalibrationData2(char *i2cDevice, char *caliFilePath);	

/**
 * @brief   get lens parameters
 * 
 * @param[out]   lensParams      lens parameters
 *
 * @return  execution result: true:success false:failure
*/
CP_DLL_PUBLIC 
bool DepthMapWrapperGetLensParameters2(WrapperDepthCamLensParameters *lensParams);

/**
 * @brief   set usecase
 * 
 * @param[in]   usecaseIndex      usecase index
 *
 * @return  execution result: true:success false:failure
*/
CP_DLL_PUBLIC
bool DepthMapWrapperSetUseCase2(int usecaseIndex);

/**
 * @brief   updata auto exposure time to tof sensor
 * 
 * @param[in]   rawdataType         rawdata type
 * @param[out]  tofExposureTime     auto exposure time
 * 
 * @return  execution result: true:success false:failure
*/
CP_DLL_PUBLIC
bool DepthMapWrapperUpdateAutoExposureTime2(uint32_t *tofExposureTime);

/**
 * @brief   enable auto exposure
 * 
 * @param[in]   aeEnable   true：auto exposure  false：manual exposure     
 *
 * @return  execution result: true:success false:failure
*/
CP_DLL_PUBLIC
bool DepthMapWrapperSetAutoExposureEnabled2(bool aeEnable);

/**
 * @brief   start recording rrf file
 * 
 * @param[in]   rrfFileDirectory      rrffile storage directory(e.g.:/mnt/data/)
 * @param[in]   usecaseIndex          usecase index
 *
 * @return  None
*/
void DepthMapWrapperStartRecRrf2(const char* rrfFileDirectory, int usecaseIndex);

/**
 * @brief   stop recording rrf file
 *
 * @return  None
*/
CP_DLL_PUBLIC
void DepthMapWrapperStopRecRrf2();

/**
 * @brief   rawdata decode
 * 
 * @param[in]    rawdataBuff      rawdata
 * @param[out]   irImage          ir image data
 * @param[out]   depthImage       depth image data
 * @param[out]   pointCloudImage  point cloud data
 * @param[out]   pointCloudCount  point cloud data count
 * 
 * @return  execution result: true:success false:failure
*/
CP_DLL_PUBLIC
bool DepthMapWrapperProcessFrameSpot2(char *rawdataBuff,  char *irImage, char *depthImage, 
                                        char *pointCloudImage, uint32_t *pointCloudCount);


 #ifdef __cplusplus
 }
#endif


#endif //__DEPTHMAP_WRAPPER_H__



