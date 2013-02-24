#include <stdio.h>

#ifdef LINUX
#include <thread>
#endif

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32)
#include <Windows.h>
#endif

#include <coin/utils/time.h>

#include <coin/coin.h>
#include <coin/gl.h>
#include <coin/application/State.h>
#include <coin/application/Application.h>

using namespace std;


namespace coin {


namespace {

Application*    application_;
SDL_GLContext   context_;
SDL_Window*     window_;
bool            running_;

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32)
DWORD WINAPI Update (LPVOID lpParam) {
#else
void Update () {
#endif
    application_->Update ();
    application_->GetState ().Update ();
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32)
    return 0;
#endif
}

void Render () {
    application_->Render ();
    application_->GetState ().Render ();
}

void OnPause () {
    application_->OnPause ();
    application_->GetState ().OnPause ();
}

void OnResume () {
    application_->OnResume ();
    application_->GetState ().OnResume ();
}

void OnPointerDown (MouseButton button, Position x, Position y) {
    application_->MouseDown (button, x, y);
    application_->GetState ().MouseDown (button, x, y);
}

void OnPointerMoved (RelativePosition x, RelativePosition y) {
    application_->MouseMoved (x, y);
    application_->GetState ().MouseMoved (x, y);
}

void OnPointerUp (MouseButton button, Position x, Position y) {
    application_->MouseUp (button, x, y);
    application_->GetState ().MouseUp (button, x, y);
}

void OnMouseWheelScrolled (RelativePosition scroll) {
    application_->MouseWheelScrolled (scroll);
    application_->GetState ().MouseWheelScrolled (scroll);
}

void OnKeyDown (Key key) {
    application_->KeyDown (key);
    application_->GetState ().KeyDown (key);
}

void OnKeyUp (Key key) {
    application_->KeyUp (key);
    application_->GetState ().KeyUp (key);
}

void application_InitGl () {
    application_->InitGl ();
}

void application_Resize (Size width, Size height) {
    application_->Resize (width, height);
}

void application_Destroy () {
    application_->Destroy ();
}

}


void Start (Application* application, const Size window_width, const Size window_height, const bool fullscreen, const bool vsync) {
    application_ = application;

    TimeInit ();

    /* Set OpenGL parameters */
    SDL_DisplayMode display_mode;
    if (SDL_VideoInit (NULL) < 0) {
        printf ("Couldn't initialize video driver: %s\n", SDL_GetError ());
        return;
    }

    SDL_GL_SetAttribute (SDL_GL_RED_SIZE,               8);
    SDL_GL_SetAttribute (SDL_GL_GREEN_SIZE,             8);
    SDL_GL_SetAttribute (SDL_GL_BLUE_SIZE,              8);
    SDL_GL_SetAttribute (SDL_GL_ALPHA_SIZE,             8);
    SDL_GL_SetAttribute (SDL_GL_DOUBLEBUFFER,           1);
    SDL_GL_SetAttribute (SDL_GL_BUFFER_SIZE,            32);
    SDL_GL_SetAttribute (SDL_GL_DEPTH_SIZE,             24);
    SDL_GL_SetAttribute (SDL_GL_STENCIL_SIZE,           0);
    SDL_GL_SetAttribute (SDL_GL_ACCUM_RED_SIZE,         8);
    SDL_GL_SetAttribute (SDL_GL_ACCUM_GREEN_SIZE,       8);
    SDL_GL_SetAttribute (SDL_GL_ACCUM_BLUE_SIZE,        8);
    SDL_GL_SetAttribute (SDL_GL_ACCUM_ALPHA_SIZE,       8);
    SDL_GL_SetAttribute (SDL_GL_STEREO,                 SDL_FALSE);
    SDL_GL_SetAttribute (SDL_GL_MULTISAMPLEBUFFERS,     0);
    SDL_GL_SetAttribute (SDL_GL_MULTISAMPLESAMPLES,     0);
    SDL_GL_SetAttribute (SDL_GL_ACCELERATED_VISUAL,     1);
    SDL_GL_SetAttribute (SDL_GL_RETAINED_BACKING,       1);
    SDL_GL_SetAttribute (SDL_GL_CONTEXT_MAJOR_VERSION,  3);
    SDL_GL_SetAttribute (SDL_GL_CONTEXT_MINOR_VERSION,  3);

    memset (&display_mode, 0, sizeof (SDL_DisplayMode));
    display_mode.format = SDL_PIXELFORMAT_RGBA8888;
    display_mode.w = window_width;
    display_mode.h = window_height;

    int flags =  SDL_WINDOW_OPENGL;
    if (fullscreen) flags |= SDL_WINDOW_FULLSCREEN;
    window_ = SDL_CreateWindow ("coin", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window_width, window_height, flags);
    if (!window_) {
        printf ("Couldn't create window: %s\n", SDL_GetError ());
        return;
    }

    if (SDL_SetWindowDisplayMode (window_, &display_mode) < 0) {
        printf ("Can't set up display mode: %s\n", SDL_GetError ());
        return;
    }

    SDL_ShowWindow (window_);

    /* Create OpenGL context */
    context_ = SDL_GL_CreateContext (window_);
    if (!context_) {
        printf ("SDL_GL_CreateContext (): %s\n", SDL_GetError());
        return; /* TODO(Marco): Go to cleanup stage... */
    }

    if (vsync) {
        if (SDL_GL_SetSwapInterval (-1) == -1) {
            SDL_GL_SetSwapInterval (1);
        }
    }else {
        SDL_GL_SetSwapInterval (0);
    }

    glewExperimental = GL_TRUE; /* Enable all the CORE stuff you can use on NVidia! */
    GLenum err = glewInit ();
    if (GLEW_OK != err) {
            printf ("Error: %s\n", glewGetErrorString (err));
    }
    printf ("Status: Using GLEW %s\n", glewGetString (GLEW_VERSION));

    SDL_DisplayMode mode;
    SDL_GetCurrentDisplayMode(0, &mode);
    printf ("Screen BPP    : %d\n", SDL_BITSPERPIXEL (mode.format));
    printf ("Swap Interval : %d\n", SDL_GL_GetSwapInterval ());
    printf ("\n");
    printf ("Vendor        : %s\n", glGetString (GL_VENDOR));
    printf ("Renderer      : %s\n", glGetString (GL_RENDERER));
    printf ("Version       : %s\n", glGetString (GL_VERSION));
    printf ("\n");
    fflush (stdout);


    /* Initialize application. */
    application_InitGl ();
    application_Resize (window_width, window_height);

    /* Game loop. */
    SDL_Event event;
    running_ = true;
    while (running_) {
        Render ();

        /* Check for events */
        while (SDL_PollEvent (&event)) {
            switch (event.type) {
                case SDL_KEYDOWN:
                    OnKeyDown (event.key.keysym.sym);
                    break;
                case SDL_KEYUP:
                    OnKeyUp (event.key.keysym.sym);
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    OnPointerDown (event.button.button, event.button.x, event.button.y);
                    break;
                case SDL_MOUSEBUTTONUP:
                    OnPointerUp (event.button.button, event.button.x, event.button.y);
                    break;
                case SDL_MOUSEMOTION:
                    OnPointerMoved (event.motion.xrel, event.motion.yrel);
                    break;
                case SDL_MOUSEWHEEL:
                    OnMouseWheelScrolled (event.wheel.y);
                    break;
                case SDL_QUIT: /* Window closed. */
                    running_ = false;
                    break;
            }
        }

        if (application->GetState ().GrabMouse ()) {
            SDL_EventState (SDL_MOUSEMOTION, SDL_IGNORE);
            SDL_WarpMouseInWindow (window_, window_width / 2, window_height / 2);
            SDL_EventState (SDL_MOUSEMOTION, SDL_ENABLE);
        }

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32)
        DWORD threadId;
        HANDLE update_thread = CreateThread (NULL, 0, Update, NULL, 0, &threadId);                      
#else
        thread update_thread (&Update);
#endif
        
        SDL_GL_SwapWindow (window_);

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32)
        WaitForSingleObject (update_thread, INFINITE);
#else 
        update_thread.join ();
#endif
    }



    if (context_) {
        SDL_GL_DeleteContext (context_);
    }

    SDL_DestroyWindow (window_);
    SDL_VideoQuit();
}


void Stop () {
    running_ = false;
}

SDL_Window* GetWindow () {
    return window_;
}

}

