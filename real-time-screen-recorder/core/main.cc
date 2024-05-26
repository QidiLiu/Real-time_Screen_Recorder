#include "util/util.h"
#include "core/ScreenshotGetter/ScreenshotGetter.h"
#include "core/DataPipe/DataPipe.h"

int main() {
    std::shared_ptr<Secretary> secretary = std::make_shared<Secretary>(6);

    auto cropped_screenshot = absl::make_unique<CroppedScreenshot>();
    secretary->addTopic("cropped_screenshot", cropped_screenshot.get());

    auto screenshot_getter = std::make_shared<ScreenshotGetter>();
    secretary->subscribe(screenshot_getter, "cropped_screenshot");
    auto data_pipe = std::make_shared<DataPipe>();
    secretary->subscribe(data_pipe, "cropped_screenshot");

    secretary->startMainLoop();

    return EXIT_SUCCESS;
}
