#ifndef RUCUBE_H
#define RUCUBE_H

#include <cstdint>
#include <vector>

class ruCube
{
    public:
        ruCube();
        ruCube(uint32_t edges, uint64_t corners);
        ruCube(const ruCube& other);
        virtual ~ruCube();

        uint32_t getEdges() const;
        uint64_t getCorners() const;
        void setEdges(uint32_t edges);
        void setCorners(uint64_t corners);
        void setCube(uint32_t edges, uint64_t corners);

        bool isSolved(uint32_t edgesMask, uint64_t cornersMask) const;
        bool isSolvedEdges(uint32_t edgesMask) const;
        bool isSolvedCorners(uint64_t cornersMask) const;
        bool isInDomino() const;

        void reset();
        void turn(uint8_t turnIndex);
        void inverseTurn(uint8_t turnIndex);
        void scramble(std::vector<uint8_t> moves);
        void inverseScramble(std::vector<uint8_t> moves);


    private:
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

        using movePointer = void (ruCube::*)();
        std::vector<movePointer> movesVect;
        std::vector<movePointer> movesInvertionsVect;


        void R();
        void R2();
        void Ri();
        void U();
        void U2();
        void Ui();
        void initializeMovesVectors();
        bool isSolvedCornersO() const;
        bool isSolvedEEinE() const;
        bool isSolvedMEinM() const;
        bool isSolvedSEinS() const;

    public:
        static inline const uint64_t solvedCorners = 0101112131415;
        static inline const uint32_t solvedEdges = 00123456;
        static inline const uint64_t allCornersMask = 0777777777777;
        static inline const uint32_t allEdgesMask = 07777777;

};

#endif // RUCUBE_H
