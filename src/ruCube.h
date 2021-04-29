#ifndef RUCUBE_H
#define RUCUBE_H

#include <cstdint>
#include <vector>
#include <memory>

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

        virtual void reset() = 0;
        virtual void turn(uint8_t turnIndex) = 0;
        virtual void inverseTurn(uint8_t turnIndex) = 0;
        virtual void scramble(std::vector<uint8_t> moves) = 0;
        virtual void inverseScramble(std::vector<uint8_t> moves) = 0;

        virtual std::unique_ptr<ruBaseCube> clone() const = 0;

        virtual bool isPruningPossible(uint8_t remainingMoves) const = 0;

    protected:
        virtual void R() = 0;
        virtual void R2() = 0;
        virtual void Ri() = 0;
        virtual void U() = 0;
        virtual void U2() = 0;
        virtual void Ui() = 0;
        virtual bool isSolvedCornersO() const = 0;
        virtual bool isSolvedEEinE() const = 0;
        virtual bool isSolvedMEinM() const = 0;
        virtual bool isSolvedSEinS() const = 0;

        using movePointer = void (ruBaseCube::*)();
        std::vector<movePointer> movesVect;
        std::vector<movePointer> movesInvertionsVect;
};

class ruCube: public ruBaseCube
{
    public:
        ruCube();
        ruCube(uint32_t edges, uint64_t corners);
        ruCube(const ruCube& other);
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

        void reset() override;
        void turn(uint8_t turnIndex) override;
        void inverseTurn(uint8_t turnIndex) override;
        void scramble(std::vector<uint8_t> moves) override;
        void inverseScramble(std::vector<uint8_t> moves) override;

        std::unique_ptr<ruBaseCube> clone() const override;

        bool isPruningPossible(uint8_t remainingMoves) const override;

    protected:
        void R() override;
        void R2() override;
        void Ri() override;
        void U() override;
        void U2() override;
        void Ui() override;
        bool isSolvedCornersO() const override;
        bool isSolvedEEinE() const override;
        bool isSolvedMEinM() const override;
        bool isSolvedSEinS() const override;


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
        static inline const uint64_t allCornersMask = 0777777777777;
        static inline const uint32_t allEdgesMask = 07777777;
        static inline const uint64_t cornersOrientationMask = 0707070707070;
        static inline const uint64_t cornersPermutationMask = 0070707070707;
};

//class ruLutCube: public ruBaseCube {
//
//};

#endif // RUCUBE_H

