//
// Created by brani on 20.08.19.
//

#ifndef MANUALOBJECTDETECTION_LOADIMAGESFROMDIRECTORY_H
#define MANUALOBJECTDETECTION_LOADIMAGESFROMDIRECTORY_H

#include <string>


class LoadImagesFromDirectory {
public:
    explicit LoadImagesFromDirectory(std::string &directory): directory(directory) {

    }

private:
    std::string directory;

};


#endif //MANUALOBJECTDETECTION_LOADIMAGESFROMDIRECTORY_H
