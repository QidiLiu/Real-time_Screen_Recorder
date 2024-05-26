#ifndef DATAPIPE_DATAPIPE_H_
#define DATAPIPE_DATAPIPE_H_

#include "util/util.h"
#include "util/data/CroppedScreenshot.hpp"

class DataPipe : public IWorker {
public:

    DataPipe(); // TODO: implement the initialization
    //~DataPipe();

    /// @brief [LOGIC] set custom data for your node
    /// @param init_topic_name data source topic name
    /// @param init_data_ptr data pointer
    void setData(const std::string& init_topic_name, IData* init_data_ptr) override;

    /// @brief [LOGIC] message processing
    /// @param in_info input message
    void receive(const std::string& in_info) override;

private:

    CroppedScreenshot* cropped_screenshot;
    bool new_cropped_data_ready_flag;

    void manageConnectionAndSendData();

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

#endif // DATAPIPE_DATAPIPE_H_
