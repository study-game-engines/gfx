/****************************************************************************
MIT License

Copyright (c) 2021 Guillaume Boissé

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
****************************************************************************/
#include "gfx_window.h"

int main()
{
    auto window = gfxCreateWindow(1280, 720, "gfx - hellotriangle");
    auto gfx = gfxCreateContext(window);

    float vertices[] = {  0.5f, -0.5f, 0.0f,
                          0.0f,  0.7f, 0.0f,
                         -0.5f, -0.5f, 0.0f };
    auto vertex_buffer = gfxCreateBuffer(gfx, sizeof(vertices), vertices);

    auto program = gfxCreateProgram(gfx, "triangle");
    auto kernel = gfxCreateGraphicsKernel(gfx, program);

    for(auto time = 0.0f; !gfxWindowIsCloseRequested(window); time += 0.1f)
    {
        gfxWindowPumpEvents(window);

        float color[] = { 0.5f * cosf(time) + 0.5f,
                          0.5f * sinf(time) + 0.5f,
                          1.0f };
        gfxProgramSetParameter(gfx, program, "Color", color);

        gfxCommandBindKernel(gfx, kernel);
        gfxCommandBindVertexBuffer(gfx, vertex_buffer);

        gfxCommandDraw(gfx, 3);

        gfxFrame(gfx);
    }

    gfxDestroyContext(gfx);
    gfxDestroyWindow(window);

    return 0;
}
