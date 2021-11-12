#ifndef RUCUBEFILEWRITER_H
#define RUCUBEFILEWRITER_H

#include <fstream>
#include <thread>
#include <string>
#include <mutex>

class ruCubeFileWriter {
    public:
        ruCubeFileWriter(std::string path);
        void write(const std::string &data);
        virtual ~ruCubeFileWriter();

    private:
        std::ofstream output;
        std::mutex writeMutex;
};

#endif // RUCUBEFILEWRITER_H
