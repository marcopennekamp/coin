#include <coin/application/Application.h>


namespace coin {

void Application::Resize (const Size width, const Size height) {
    screen_config_.Resize (width, height);
}

}