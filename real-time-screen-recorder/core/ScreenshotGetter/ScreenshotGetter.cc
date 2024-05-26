#include "core/ScreenshotGetter/ScreenshotGetter.h"

ScreenshotGetter::ScreenshotGetter() : cropped_screenshot(nullptr) {
    INIReader ini_reader("../../meta/config/config.ini");
    if (ini_reader.ParseError() < 0) {
        LOG(ERROR) << "Failed to parse config.ini";
    }

    this->crop_x = ini_reader.GetInteger("CROP", "x", -1);
    this->crop_y = ini_reader.GetInteger("CROP", "y", -1);
    this->crop_w = ini_reader.GetInteger("CROP", "w", -1);
    this->crop_h = ini_reader.GetInteger("CROP", "h", -1);

    if (this->crop_x == -1 || this->crop_y == -1 || this->crop_w == -1 || this->crop_h == -1) {
        LOG(ERROR) << "Failed to parse crop parameters from config.ini";
    }

    //ultrasound_volume(absl::make_unique<UltrasoundVolume>()),
    //ultrasound_image(absl::make_unique<UltrasoundImage>()) {
    this->submitTask(std::bind(&ScreenshotGetter::recordScreenshotAndCrop, this));

    /*
    this->example_var = 114514 + example_init_delay;
    this->example_delay = example_init_delay;
    this->example_data = nullptr;

    this->submitTask(std::bind(&ScreenshotGetter::exampleInit, this));
    */
}

//ScreenshotGetter::~ScreenshotGetter() {}

void ScreenshotGetter::setData(const std::string& init_topic_name, IData* init_data_ptr) {
    if (init_topic_name == "cropped_screenshot") {
        CroppedScreenshot* casted_ptr = dynamic_cast<CroppedScreenshot*>(init_data_ptr);

        if (casted_ptr == nullptr) {
            LOG(ERROR) << "Failed by casting data pointer";
        } else {
            this->cropped_screenshot = casted_ptr;
        }
    }
}

void ScreenshotGetter::receive(const std::string& in_info) {
    /*
    LOG(INFO) << "node_" << this->example_delay << " has received command on Topic_1. in_info: " << in_info;

    
    if (in_info.empty()) {
        LOG(ERROR) << "Received empty message";
        return;
    }

    if (in_info == "some other command") {
        // do something with method submitTask() like the code below
    }

    this->submitTask(std::bind(&ScreenshotGetter::exampleFunc, this));
    */
}

void ScreenshotGetter::recordScreenshotAndCrop() {
    LOG(INFO) << "Starting infinite loop to record screenshot...";
    while (true) {
        LOG(INFO) << "Getting screenshot...";
        std::this_thread::sleep_for(std::chrono::milliseconds(500)); // [DEBUG] simulation time
        LOG(INFO) << "Cropping out region of interest...";
        std::this_thread::sleep_for(std::chrono::milliseconds(500)); // [DEBUG] simulation time
        absl::WriterMutexLock lock(&this->cropped_screenshot->mtx);
        this->send("cropped_screenshot", "new_screenshot_was_cropped");
    }
}

/*
void ScreenshotGetter::exampleInit() {
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(this->example_delay));

        if (this->example_delay == 1) {
            this->send("Topic_1", "testing sub-pub system (from node 1)");
        } else {
            this->send("Topic_1", "testing sub-pub system (from node 2)");
        }

        LOG(INFO) << "node_" << this->example_delay << " has sent command to Topic_1.";
    }
}

void ScreenshotGetter::exampleFunc() {
    LOG(INFO) << "node_" << this->example_delay << ".exampleFunc() called.";
}
*/

