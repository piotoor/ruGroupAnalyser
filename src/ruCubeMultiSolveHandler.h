#ifndef RUCUBEMULTISOLVEHANDLER_H
#define RUCUBEMULTISOLVEHANDLER_H

#include "ruLutCubeGenerator.h"
#include "ruCubeSingleSolveHandler.h"

#include <string>

auto operator""_MB(long double x) -> uint64_t;
auto operator""_GB(long double x) -> uint64_t;

class ruCubeMultiSolveHandler
{
    public:
        ruCubeMultiSolveHandler(const generatorParameters &genParams = generatorParameters(),
                                const solutionParameters &solParams = solutionParameters(),
                                const solveReportFlags &flags = solveReportFlags());
        virtual ~ruCubeMultiSolveHandler() = default;
        void configure( const generatorParameters &genParams = generatorParameters(),
                        const solutionParameters &solParams = solutionParameters(),
                        const solveReportFlags &flags = solveReportFlags());

        void generateAndSolve(std::string fileName = "output.txt");
        uint32_t calculateTotalNumberOfCubesToGenerate();
    private:
        uint64_t estimateSingleSolveReportSize();
        uint64_t calculateAvailableDiskSpace();
        uint8_t calculateNumOfAvailableThreads();

        void disableHeadersAndFooters();
        void disableLineNumbers();
        void disableFixedWidthMoves();
        void disableSummary();
        void compressSolutions();
        void compressCubeState();
        void dropMaxNumOfSolutionsToN(uint8_t n);

        void prepare();
        void printOptimizations();
        bool optimizeReport();

        ruLutCubeGenerator generator;


        solutionParameters solParams;
        solvedMasks masks;
        solveReportFlags flags;
        generatorParameters genParams;
        bool compressedCubeState = false;
        bool compressedCubeStateInitial = false;

        solutionParameters solParamsInitial;
        solveReportFlags flagsInitial;


        static inline const uint8_t maxCubeStateStrSize = 69; // cube state; solved mask printed once
        static inline const uint8_t maxCompressedCubeStateStrSize = 21;
        static inline const uint8_t maxSolutionStrSize = 60;
        static inline const uint8_t maxCompressedSolutionStrSize = 40;
        static inline const uint8_t maxLineNumStrSize = 7;
        static inline const uint8_t maxHeaderStrSize = 26;
        static inline const uint8_t maxSummaryStrSize = 52;
        static inline const uint8_t maxNumOfHeaders = 20;
        static inline const uint8_t maxNumOfBlankLines = 20;
        static inline const uint64_t maxOutputFileSize = 4.5_GB;    // todo calculate
        // todo num of thhreads

        // fullreport header == gen masks + solved masks
        // fullpreport header size

        static inline const std::vector<std::vector<uint8_t>> numOfCornerPerms {    // [ignored][locked]
            { 120, 20, 4, 1, 1, 1, 1 },
            { 120, 20, 4, 1, 1, 1 },
            { 120, 20, 4, 1, 1 },
            { 120, 20, 4, 1 },
            {  30,  5, 1 },
            {   6,  1 },
            {   1 }
        };


        uint32_t totalNumberOfCubesToGenerate = 0;
        size_t numOfThreads = 1;
};

#endif // RUCUBEMULTISOLVEHANDLER_H

