#include "VerkeersSituatie.h"
#include <fstream>
#include <unistd.h>

int main() {
    VerkeersSituatie* fSituatie = new VerkeersSituatie();
    fSituatie->fromXML("../test.xml");
    ofstream fileList("../graphics_render/filelist");
    for (int i = 0; i < 250; ++i) {
        string fileName = "test" + to_string(i) + ".ini";
        fileList << fileName << "\n";
        string filePath = "../graphics_render/" + fileName;
        ofstream file(filePath.c_str());
        fSituatie->exportGraphics(file);
        file.close();
        //usleep(400000);
        for (int j = 0; j < 25; ++j) {
            fSituatie->nextTijd();
        }
    }
    fileList.close();
}