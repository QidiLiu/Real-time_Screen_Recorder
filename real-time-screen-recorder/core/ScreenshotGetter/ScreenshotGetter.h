#ifndef SCREENSHOTGETTER_SCREENSHOTGETTER_H_
#define SCREENSHOTGETTER_SCREENSHOTGETTER_H_

#include "util/util.h"
#include "util/data/CroppedScreenshot.hpp"

#include <ini.h>
#include "INIReader.h"

//struct UltrasoundVolume : public IData {};
//struct UltrasoundImage : public IData {};

class ScreenshotGetter : public IWorker {
public:

    ScreenshotGetter();
    //~ScreenshotGetter();

    /// @brief [LOGIC] set custom data for your node
    /// @param init_topic_name data source topic name
    /// @param init_data_ptr data pointer
    void setData(const std::string& init_topic_name, IData* init_data_ptr) override;

    /// @brief [LOGIC] message processing
    /// @param in_info input message
    void receive(const std::string& in_info) override;

private:

    int crop_x;
    int crop_y;
    int crop_w;
    int crop_h;
    CroppedScreenshot* cropped_screenshot;

    //std::unique_ptr<UltrasoundVolume> ultrasound_volume;
    //std::unique_ptr<UltrasoundImage> ultrasound_image;

    void recordScreenshotAndCrop(); // TODO: implement this function

    /*
    ExampleData* example_data;
    int example_var;
    int example_delay;

    /// @brief [LOGIC] example function
    void exampleInit();

    /// @brief [LOGIC] example function
    void exampleFunc();
    */
};

#endif // SCREENSHOTGETTER_SCREENSHOTGETTER_H_
