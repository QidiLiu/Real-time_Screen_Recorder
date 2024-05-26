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
    cv::Mat test_mat;
    HDC screen_hdc = GetDC(NULL);
    int screen_width = GetDeviceCaps(screen_hdc, HORZRES);
    int screen_height = GetDeviceCaps(screen_hdc, VERTRES);
    if ((this->crop_x + this->crop_w) > screen_width || (this->crop_y + this->crop_h) > screen_height) {
        LOG(ERROR) << "Crop size is larger than screen size";
        return;
    }

    HBITMAP hbmp = CreateCompatibleBitmap(screen_hdc, this->crop_w, this->crop_h);
    HDC memory_hdc = CreateCompatibleDC(screen_hdc);
    SelectObject(memory_hdc, hbmp);
    BitBlt(memory_hdc, this->crop_x, this->crop_y, this->crop_w, this->crop_h, screen_hdc, 0, 0, SRCCOPY);

    BITMAP bmp = {};
    GetObject(hbmp, sizeof(BITMAP), &bmp);
    int channel_num = bmp.bmBitsPixel == 1 ? 1 : bmp.bmBitsPixel / 8;
    test_mat.create(cv::Size(this->crop_w, this->crop_h), CV_MAKETYPE(CV_8U, channel_num));

    while (cv::waitKey(1) != 'q') {
        //LOG(INFO) << "Getting screenshot...";
        //LOG(INFO) << "bmp.bmWidth: " << bmp.bmWidth << " bmp.bmHeight: " << bmp.bmHeight << ", channel num: " << channel_num;

        BitBlt(memory_hdc, 0, 0, this->crop_w, this->crop_h, screen_hdc, this->crop_x, this->crop_y, SRCCOPY);
        GetBitmapBits(hbmp, this->crop_h * this->crop_w * channel_num, test_mat.data);
        cv::imshow("screenshot", test_mat);

        absl::WriterMutexLock lock(&this->cropped_screenshot->mtx);
        // TODO: write data to cropped_screenshot
        this->send("cropped_screenshot", "new_screenshot_was_cropped");
    }

    cv::destroyAllWindows();
    DeleteObject(hbmp);
    DeleteDC(memory_hdc);
    ReleaseDC(NULL, screen_hdc);
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

