#include "core/DataPipe/DataPipe.h"

DataPipe::DataPipe() : cropped_screenshot(nullptr), new_cropped_data_ready_flag(false) {
    this->submitTask(std::bind(&DataPipe::manageConnectionAndSendData, this));

    /*
    this->example_var = 114514 + example_init_delay;
    this->example_delay = example_init_delay;
    this->example_data = nullptr;

    this->submitTask(std::bind(&DataPipe::exampleInit, this));
    */
}

//DataPipe::~DataPipe() {}

void DataPipe::setData(const std::string& init_topic_name, IData* init_data_ptr) {
    if (init_topic_name == "cropped_screenshot") {
        CroppedScreenshot* casted_ptr = dynamic_cast<CroppedScreenshot*>(init_data_ptr);

        if (casted_ptr == nullptr) {
            LOG(ERROR) << "Failed by casting data pointer";
        } else {
            this->cropped_screenshot = casted_ptr;
        }
    }
}

void DataPipe::receive(const std::string& in_info) {
    if (in_info == "new_screenshot_was_cropped") {
        this->new_cropped_data_ready_flag = true;
    }

    /*
    LOG(INFO) << "node_" << this->example_delay << " has received command on Topic_1. in_info: " << in_info;

    
    if (in_info.empty()) {
        LOG(ERROR) << "Received empty message";
        return;
    }

    if (in_info == "some other command") {
        // do something with method submitTask() like the code below
    }

    this->submitTask(std::bind(&DataPipe::exampleFunc, this));
    */
}

void DataPipe::manageConnectionAndSendData() {
    while (true) {
        if (!this->new_cropped_data_ready_flag) { continue; }
        LOG(INFO) << "Sending data...";
        absl::ReaderMutexLock lock(&this->cropped_screenshot->mtx);
        std::this_thread::sleep_for(std::chrono::milliseconds(500)); // [DEBUG] simulation time
        this->new_cropped_data_ready_flag = false;
        LOG(INFO) << "Data sent.";
    }
}

/*
void DataPipe::exampleInit() {
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

void DataPipe::exampleFunc() {
    LOG(INFO) << "node_" << this->example_delay << ".exampleFunc() called.";
}
*/

