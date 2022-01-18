#include "ruCubeFileWriter.h"
#include <iostream>

ruCubeFileWriter::ruCubeFileWriter(std::string path) {
    output.open(path);
}

ruCubeFileWriter::~ruCubeFileWriter() {
    output.close();
}

void ruCubeFileWriter::write(const std::string &data) {
    std::lock_guard<std::mutex> lock(writeMutex);
    output.write(data.c_str(), data.size());
}
