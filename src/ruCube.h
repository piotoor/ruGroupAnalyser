#ifndef RUCUBE_H
#define RUCUBE_H

#include <cstdint>
#include <vector>
#include <memory>
#include "lutGenerators.h"

enum ruCubeMove {
    R,
    R2,
    Ri,
    U,
    U2,
    Ui
};

class ruBaseCube {
    public:
        ruBaseCube();
        ruBaseCube(const ruBaseCube &other) = default;
        ruBaseCube & operator=(const ruBaseCube &other) = default;
        virtual ~ruBaseCube() = 0;


        virtual uint32_t getEdges() const = 0;
        virtual uint64_t getCorners() const = 0;
        virtual void setEdges(uint32_t edges) = 0;
        virtual void setCorners(uint64_t corners) = 0;
        virtual void setCube(uint32_t edges, uint64_t corners) = 0;

        virtual bool isSolved(uint32_t edgesMask, uint64_t cornersMask) const = 0;
        virtual bool isSolvedEdges(uint32_t edgesMask) const = 0;
        virtual bool isSolvedCorners(uint64_t cornersMask) const = 0;
        virtual bool isInDomino() const = 0;
        virtual bool isSolvedCornersO() const = 0;
        virtual bool isSolvedEEinE() const = 0;
        virtual bool isSolvedMEinM() const = 0;
        virtual bool isSolvedSEinS() const = 0;

        virtual void reset() = 0;
        void turn(uint8_t turnIndex);
        void inverseTurn(uint8_t turnIndex);
        void scramble(std::vector<uint8_t> moves);
        void inverseScramble(std::vector<uint8_t> moves);

        virtual bool isPruningPossible(uint8_t remainingMoves) const = 0;

    protected:
        virtual void R() = 0;
        virtual void R2() = 0;
        virtual void Ri() = 0;
        virtual void U() = 0;
        virtual void U2() = 0;
        virtual void Ui() = 0;


        using movePointer = void (ruBaseCube::*)();
        std::vector<movePointer> movesVect;
        std::vector<movePointer> movesInvertionsVect;

    public:
        static inline const uint64_t allCornersMask = UINT64_MAX;
        static inline const uint32_t allEdgesMask = UINT32_MAX;

        static inline const uint8_t noOfCorners = 6;
        static inline const uint8_t noOfEdges = 7;
};

class ruCube: public ruBaseCube
{
    public:
        ruCube();
        ruCube(uint32_t edges, uint64_t corners);
        explicit ruCube(const ruCube& other) = default;
        ~ruCube();

        uint32_t getEdges() const override;
        uint64_t getCorners() const override;
        void setEdges(uint32_t edges) override;
        void setCorners(uint64_t corners) override;
        void setCube(uint32_t edges, uint64_t corners) override;

        bool isSolved(uint32_t edgesMask = ruCube::solvedEdges, uint64_t cornersMask = ruCube::solvedCorners) const override;
        bool isSolvedEdges(uint32_t edgesMask) const override;
        bool isSolvedCorners(uint64_t cornersMask) const override;
        bool isInDomino() const override;
        bool isSolvedCornersO() const override;
        bool isSolvedEEinE() const override;
        bool isSolvedMEinM() const override;
        bool isSolvedSEinS() const override;

        void reset() override;

        bool isPruningPossible(uint8_t remainingMoves) const override;

    protected:
        void R() override;
        void R2() override;
        void Ri() override;
        void U() override;
        void U2() override;
        void Ui() override;

        uint32_t edges;
        struct cornersPBits
        {
            uint64_t DFR: 6;
            uint64_t DRB: 6;
            uint64_t UBR: 6;
            uint64_t ULB: 6;
            uint64_t UFL: 6;
            uint64_t URF: 6;
        };

        struct cornersOBits
        {
            uint64_t    : 3;
            uint64_t DFR: 3;
            uint64_t    : 3;
            uint64_t DRB: 3;
            uint64_t    : 3;
            uint64_t UBR: 3;
            uint64_t    : 3;
            uint64_t ULB: 3;
            uint64_t    : 3;
            uint64_t UFL: 3;
            uint64_t    : 3;
            uint64_t URF: 3;
        };

        union
        {
            uint64_t corners;
            cornersPBits cornersPB;
            cornersOBits cornersOB;
        };

        uint64_t tmp;

    public:
        static inline const uint64_t solvedCorners = 0101112131415;
        static inline const uint32_t solvedEdges = 00123456;

        static inline const uint32_t UFMask = 07000000;
        static inline const uint32_t ULMask = 00700000;
        static inline const uint32_t UBMask = 00070000;
        static inline const uint32_t URMask = 00007000;
        static inline const uint32_t BRMask = 00000700;
        static inline const uint32_t DRMask = 00000070;
        static inline const uint32_t FRMask = 00000007;
        static inline const uint64_t cornersOrientationMask = 0707070707070;
        static inline const uint64_t URFOrientMask = 0700000000000;
        static inline const uint64_t UFLOrientMask = 0007000000000;
        static inline const uint64_t ULBOrientMask = 0000070000000;
        static inline const uint64_t UBROrientMask = 0000000700000;
        static inline const uint64_t DRBOrientMask = 0000000007000;
        static inline const uint64_t DFROrientMask = 0000000000070;
        static inline const uint64_t cornersPermutationMask = 0070707070707;
        static inline const uint64_t URFPermMask = 0070000000000;
        static inline const uint64_t UFLPermMask = 0000700000000;
        static inline const uint64_t ULBPermMask = 0000007000000;
        static inline const uint64_t UBRPermMask = 0000000070000;
        static inline const uint64_t DRBPermMask = 0000000000700;
        static inline const uint64_t DFRPermMask = 0000000000007;

};

class ruLutCube: public ruBaseCube {
    public:
        ruLutCube();
        ruLutCube(uint16_t edgesPerm, uint16_t cornersPerm, uint16_t cornersOrient);
        ruLutCube(const ruLutCube& other) = default;
        ~ruLutCube();
        ruLutCube& operator=(const ruLutCube& other);
        bool operator==(const ruLutCube &other) const;

        uint32_t getEdges() const override;
        uint64_t getCorners() const override;
        void setEdges(uint32_t edges) override;
        void setCorners(uint64_t corners) override;
        void setCube(uint32_t edges, uint64_t corners) override;

        uint16_t getCornersOrient() const;
        uint16_t getCornersPerm() const;
        void setCornersPerm(uint16_t cornersPerm);
        void setCornersOrient(uint16_t cornersOrient);

        bool isSolved(uint32_t edgesMask = ruLutCube::allEdgesMask, uint64_t cornersMask = ruLutCube::allCornersMask) const override;
        bool isSolvedEdges(uint32_t edgesMask) const override;
        bool isSolvedCorners(uint64_t cornersMask) const override;
        bool isInDomino() const override;
        bool isSolvedCornersO() const override;
        bool isSolvedEEinE() const override;
        bool isSolvedMEinM() const override;
        bool isSolvedSEinS() const override;
        static bool isPermutationSolveable(uint16_t cornersPerm, uint16_t edgesPerm);
        static bool isCornersOrientationSolveable(uint16_t cornersOrient);
        static bool isCubeSolveable(uint16_t edgesPerm, uint16_t cornersPerm, uint16_t cornersOrient);
        void reset() override;

        bool isPruningPossible(uint8_t remainingMoves) const override;

    protected:
        void R() override;
        void R2() override;
        void Ri() override;
        void U() override;
        void U2() override;
        void Ui() override;

        uint16_t edgesPerm;
        uint16_t cornersPerm;
        uint16_t cornersOrient;

        static std::array<std::array<uint16_t, lutGenerators::noOfTurns>, lutGenerators::noOfEdgesPermutations>     edgesPermMoveMap;
        static std::array<std::array<uint16_t, lutGenerators::noOfTurns>, lutGenerators::noOfCornersPermutations>   cornersPermMoveMap;
        static std::array<std::array<uint16_t, lutGenerators::noOfTurns>, lutGenerators::noOfCornersOrientations>   cornersOrientMoveMap;

        static std::array<std::bitset<lutGenerators::noOfEdgesPermSolvedStates>, lutGenerators::noOfEdgesPermutations>          edgesPermSolvedTable;
        static std::array<std::bitset<lutGenerators::noOfCornersPermSolvedStates>, lutGenerators::noOfCornersPermutations>      cornersPermSolvedTable;
        static std::array<std::bitset<lutGenerators::noOfCornersOrientSolvedStates>, lutGenerators::noOfCornersOrientations>    cornersOrientSolvedTable;

        static std::array<int8_t, lutGenerators::noOfEdgesPermutations>                                                            edgesPermPruningTable;
        static std::array<std::array<int8_t, lutGenerators::noOfCornersOrientations>, lutGenerators::noOfCornersPermutations>      cornersPruningTable;
        static std::vector<std::vector<std::vector<int8_t>>> fullCubePruningTable;
        //static std::array<std::array<bool, lutGenerators::noOfEdgesPermutations>, lutGenerators::noOfCornersPermutations>      permutationValidityTable;
        static std::array<std::bitset<lutGenerators::noOfEdgesPermutations>, lutGenerators::noOfCornersPermutations>      permutationValidityTable;


    public:
        static inline const uint16_t solvedLexIndexEdgesPerm = 0;
        static inline const uint16_t solvedLexIndexCornersPerm = 0;
        static inline const uint16_t solvedLexIndexCornersOrient = 0;

        static inline const uint64_t allCornersOrientMask = 0x0000004000000000;
        static inline const uint64_t allCornersPermMask = 0x0000000000000040;

        static inline const uint64_t setCornersPermMask     = 0x0000FFFF;
        static inline const uint64_t setCornersOrientMask   = 0xFFFF0000;
};

#endif // RUCUBE_H

