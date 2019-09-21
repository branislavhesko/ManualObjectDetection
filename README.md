# ManualObjectDetection

Simple app to mark object labels and boundaries for object detection tasks.


This simple application allows to manually detect objects in a video, which can be then used for object detection. The project is only OpenCV dependent, all gui elements are header only defined in cvui.h, which was downloaded from:
https://dovyski.github.io/cvui/

This library is quite simple and does not add unwanted dependencies.

## Build

Prerequisites:

    - OpenCV 4 (build with 4.1.0 has been verified).
    - gcc-8 (if not, please update the CMakeLists.txt for the filesystem library).

To build from the command line, use the following snippet:
```
mkdir build
cd build
cmake ..
make
```

Afterwards, executable ManualObjectDetection (for windows ManualObjectDetetion.exe) will be created.

## Usage
Usage is simple, we tried to make the application as simple as possible. Please **create classes.txt** in the application directory. There you should write your objects categories, separated by a new line. For example:

    - classes.txt:
        ```
        Car
        Person
        Bus
        Building
        Other
        ```

At the same time create a new directory called **images** in the application folder. In this folder, all marked images will be stored. Application is able to process both video_files (for a good video support please install ffmpeg) and folder with images. Images are resized to 1280x720 (different size can be set in code) and stored with a timestamp. Bounding boxes together with informations are stored in detected.txt. When no object has been picked, **None** label is reserved for bad boundaries.
Usage:
```
./ManualObjectDetection file/folder second_to_start step
```
Step is the number of seconds between frames picked from a video, second_to_start is the number of seconds of the video skipped from the beginning. There is also a slider in the application allowing to move freely in the video. file/folder means:

    - file: only for videos.
    - folder: when you want to mark multiple images in that folder.

## Control
When only the window with the image is use LEFT MOUSE button to depict bounding box.

Few keyboard shortcuts are usable:

    - ESC - when object is depicted, pressing this key will cause a menu window appear. In this window you may pick a category or move in the video or end application.
    - LEFT_KEY - move to the next frame.
    - RIGHT_KEY - move to the previous frame.
    - S - when menu present, pressing this key allow to move in the video to the desired frame (set with the slider).

If you have any questions, please contact me via email: branislav.hesko@protonmail.ch.
