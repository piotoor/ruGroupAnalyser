#include "gtest/gtest.h"
#include "ruCubeStateConverter.h"
#include <vector>
#include <iostream>


TEST(ruCubeStateConverterTest, convertvectCornersToIntCornersTest) {
    ruCubeStateConverter conv;
    const std::vector<std::vector<int8_t>> cornersOrient = {
        { 0, 0, 0, 0, 0, 0 },
        { 1, 1, 1, 1, 1, 1 },
        { 0, 1, 0, 1, 0, 1 },
        { 2, 2, 2, 2, 2, 2 },
        { 2, 0, 2, 0, 2, 0 },
        { 2, 1, 2, 1, 2, 1 },
        { 2, 1, 2, 1, 2, 1 },
        { 2, 0, 2, 0, 2, 0 },
        { 2, 1, 2, 1, 0, 0 },
        { 2, 1, 2, 1, 0, 0 },
        { 2, 1, 1, 0, 1, 1 },
    };

    const std::vector<std::vector<int8_t>> cornersPerm = {
        { 0, 1, 2, 3, 4, 5 },
        { 0, 1, 2, 3, 4, 5 },
        { 0, 1, 2, 3, 4, 5 },
        { 0, 1, 2, 3, 4, 5 },
        { 0, 1, 2, 3, 4, 5 },
        { 0, 1, 2, 3, 4, 5 },
        { 5, 4, 3, 2, 1, 0 },
        { 5, 4, 3, 2, 1, 0 },
        { 5, 4, 3, 2, 1, 0 },
        { 2, 4, 3, 1, 5, 0 },
        { 0, 4, 3, 1, 2, 5 },
    };

    const std::vector<uint64_t> expectedCorners = {
        0101112131415,
        0202122232425,
        0102112231425,
        0404142434445,
        0401142134415,
        0402142234425,
        0452443224120,
        0451443124110,
        0452443221110,
        0422443211510,
        0402423112225,
    };

    for (uint8_t i = 0; i < std::size(cornersOrient); ++i) {
        auto corners = conv.vectCornersToIntCorners(cornersPerm[i], cornersOrient[i]);
        ASSERT_EQ(expectedCorners[i], corners);
    }
}

TEST(ruCubeStateConverterTest, convertvectEdgesToIntEdgesTest) {
    ruCubeStateConverter conv;

    const std::vector<std::vector<int8_t>> edgesPerm = {
        { 0, 1, 2, 3, 4, 5, 6 },
        { 6, 5, 4, 3, 2, 1, 0 },
        { 1, 3, 0, 2, 4, 5, 6 },
        { 6, 5, 1, 3, 4, 2, 0 },
        { 2, 0, 1, 3, 6, 4, 5 },
    };

    const std::vector<uint64_t> expectedEdges = {
        00123456,
        06543210,
        01302456,
        06513420,
        02013645,
    };

    for (uint8_t i = 0; i < std::size(edgesPerm); ++i) {
        auto edges = conv.vectEdgesToIntEdges(edgesPerm[i]);
        ASSERT_EQ(expectedEdges[i], edges);
    }
}

TEST(ruCubeStateConverterTest, convertVectCornersWithIgnoredPiecesToIntTest) {
    ruCubeStateConverter conv;

    const std::vector<std::vector<int8_t>> cornersOrient = {
        {  0,  0,  0,  0,  0,  0 },
        { -1,  1,  1,  1,  1, -1 },
        { -1,  1,  1,  1,  1, -1 },
        { -1, -1, -1, -1, -1, -1 },
        {  0,  0,  0,  0,  0,  0 },
        { -1, -1, -1, -1, -1, -1 },
        {  2,  2,  2,  2,  2, -1 },
        {  2,  2,  2,  1,  1, -1 },
        {  2,  2,  2,  1,  1,  1 },
    };
    const std::vector<std::vector<int8_t>> cornersPerm = {
        {  0,  1,  2,  3, -1, -1 },
        {  0,  1,  2,  3,  4,  5 },
        {  0, -1, -1,  3,  4,  5 },
        {  0,  1,  2,  3,  4,  5 },
        { -1, -1, -1, -1, -1, -1 },
        { -1, -1, -1, -1, -1, -1 },
        { -1, -1, -1, -1, -1, -1 },
        { -1, -1, -1, -1, -1, -1 },
        {  5,  4,  3, -1, -1,  1 },
    };

    const std::vector<uint64_t> expectedCorners = {
        0101112131415,
        0402122232415,
        0402122232415,
        0101112131415,
        0101112131415,
        0101112131415,
        0404142434445,
        0404142232425,
        0454443202221,
    };

    for (uint8_t i = 0; i < std::size(cornersPerm); ++i) {
        auto corners = conv.vectCornersToIntCorners(cornersPerm[i], cornersOrient[i]);
        ASSERT_EQ(expectedCorners[i], corners);
    }

}

TEST(ruCubeStateConverterTest, convertVectEdgesWithIgnoredPiecesToIntTest) {
    ruCubeStateConverter conv;

    const std::vector<std::vector<int8_t>> edgesPerm = {
        {  0,  1,  2,  3,  4,  5, -1 },
        {  6,  5, -1,  3,  2,  1,  0 },
        {  6,  5, -1, -1, -1, -1,  0 },
        { -1, -1, -1, -1, -1, -1,  1 },
        {  3, -1,  0, -1, -1, -1,  1 },
    };

    const std::vector<uint64_t> expectedEdges = {
        00123456,
        06543210,
        06512340,
        00234561,
        03204561,
    };

    for (uint8_t i = 0; i < std::size(edgesPerm); ++i) {
        auto edges = conv.vectEdgesToIntEdges(edgesPerm[i]);
        ASSERT_EQ(expectedEdges[i], edges);
    }
}

TEST(ruCubeStateConverterTest, convertIntEdgesToLexIndexEdgesTest) {
    ruCubeStateConverter conv;

    const std::vector<uint32_t> edgesInts = {
        00123456,
        00123465,
        00123546,
        00123564,
        00123645,

        00123654,
        00124356,
        00124365,
        00124536,
        00124563,

        00124635,
        00124653,
        00125346,
        00125364,
        00125436,

        00125463,
        00125634,
        00125643,
        00126345,
        00126354,

        00126435,
        00126453,
        00126534,
        00126543,
        00132456,

        00132465,
        00132546,
        00132564,
        00132645,
        00132654,

        00134256,
        00134265,
        00134526,
        00134562,
        00134625,

        00134652,
        00135246,
        00135264,
        00135426,
        00135462,

        00135624,
        00135642,
        00136245,
        00136254,
        00136425,

        00136452,
        00136524,
        00136542,
        00142356,
        00142365,

        00142536,
        00142563,
        00142635,
        00142653,
        00143256,

        00143265,
        00143526,
        00143562,
        00143625,
        00143652,

        00145236,
        00145263,
        00145326,
        00145362,
        00145623,

        00145632,
        00146235,
        00146253,
        00146325,
        00146352,

        00146523,
        00146532,
        00152346,
        00152364,
        00152436,

        00152463,
        00152634,
        00152643,
        00153246,
        00153264,

        00153426,
        00153462,
        00153624,
        00153642,
        00154236,

        00154263,
        00154326,
        00154362,
        00154623,
        00154632,

        00156234,
        00156243,
        00156324,
        00156342,
        00156423,

        00156432,
        00162345,
        00162354,
        00162435,
        00162453,

        00162534,
        00162543,
        00163245,
        00163254,
        00163425,

        00163452,
        00163524,
        00163542,
        00164235,
        00164253,

        00164325,
        00164352,
        00164523,
        00164532,
        00165234,

        00165243,
        00165324,
        00165342,
        00165423,
        00165432,

        00213456,
        00213465,
        00213546,
        00213564,
        00213645,

        00213654,
        00214356,
        00214365,
        00214536,
        00214563,

        00214635,
        00214653,
        00215346,
        00215364,
        00215436,

        00215463,
        00215634,
        00215643,
        00216345,
        00216354,

        00216435,
        00216453,
        00216534,
        00216543,
        00231456,

        00231465,
        00231546,
        00231564,
        00231645,
        00231654,

        00234156,
        00234165,
        00234516,
        00234561,
        00234615,

        00234651,
        00235146,
        00235164,
        00235416,
        00235461,

        00235614,
        00235641,
        00236145,
        00236154,
        00236415,

        00236451,
        00236514,
        00236541,
        00241356,
        00241365,

        00241536,
        00241563,
        00241635,
        00241653,
        00243156,

        00243165,
        00243516,
        00243561,
        00243615,
        00243651,

        00245136,
        00245163,
        00245316,
        00245361,
        00245613,

        00245631,
        00246135,
        00246153,
        00246315,
        00246351,

        00246513,
        00246531,
        00251346,
        00251364,
        00251436,

        00251463,
        00251634,
        00251643,
        00253146,
        00253164,

        00253416,
        00253461,
        00253614,
        00253641,
        00254136,

        00254163,
        00254316,
        00254361,
        00254613,
        00254631,

        00256134,
        00256143,
        00256314,
        00256341,
        00256413,

        00256431,
        00261345,
        00261354,
        00261435,
        00261453,

        00261534,
        00261543,
        00263145,
        00263154,
        00263415,

        00263451,
        00263514,
        00263541,
        00264135,
        00264153,

        00264315,
        00264351,
        00264513,
        00264531,
        00265134,

        00265143,
        00265314,
        00265341,
        00265413,
        00265431,

        00312456,
        00312465,
        00312546,
        00312564,
        00312645,

        00312654,
        00314256,
        00314265,
        00314526,
        00314562,

        00314625,
        00314652,
        00315246,
        00315264,
        00315426,

        00315462,
        00315624,
        00315642,
        00316245,
        00316254,

        00316425,
        00316452,
        00316524,
        00316542,
        00321456,

        00321465,
        00321546,
        00321564,
        00321645,
        00321654,

        00324156,
        00324165,
        00324516,
        00324561,
        00324615,

        00324651,
        00325146,
        00325164,
        00325416,
        00325461,

        00325614,
        00325641,
        00326145,
        00326154,
        00326415,

        00326451,
        00326514,
        00326541,
        00341256,
        00341265,

        00341526,
        00341562,
        00341625,
        00341652,
        00342156,

        00342165,
        00342516,
        00342561,
        00342615,
        00342651,

        00345126,
        00345162,
        00345216,
        00345261,
        00345612,

        00345621,
        00346125,
        00346152,
        00346215,
        00346251,

        00346512,
        00346521,
        00351246,
        00351264,
        00351426,

        00351462,
        00351624,
        00351642,
        00352146,
        00352164,

        00352416,
        00352461,
        00352614,
        00352641,
        00354126,

        00354162,
        00354216,
        00354261,
        00354612,
        00354621,
    };

    for (uint16_t i = 0; i < std::size(edgesInts); ++i) {
        uint16_t edgesLexIndex = conv.intEdgesToLexIndexEdges(edgesInts[i]);
        ASSERT_EQ(i, edgesLexIndex);
    }
}

TEST(ruCubeStateConverterTest, convertLexIndexEdgesToIntEdgesTest) {
    ruCubeStateConverter conv;

    const std::vector<uint32_t> expectedEdgesInts = {
        00123456,
        00123465,
        00123546,
        00123564,
        00123645,

        00123654,
        00124356,
        00124365,
        00124536,
        00124563,

        00124635,
        00124653,
        00125346,
        00125364,
        00125436,

        00125463,
        00125634,
        00125643,
        00126345,
        00126354,

        00126435,
        00126453,
        00126534,
        00126543,
        00132456,

        00132465,
        00132546,
        00132564,
        00132645,
        00132654,

        00134256,
        00134265,
        00134526,
        00134562,
        00134625,

        00134652,
        00135246,
        00135264,
        00135426,
        00135462,

        00135624,
        00135642,
        00136245,
        00136254,
        00136425,

        00136452,
        00136524,
        00136542,
        00142356,
        00142365,

        00142536,
        00142563,
        00142635,
        00142653,
        00143256,

        00143265,
        00143526,
        00143562,
        00143625,
        00143652,

        00145236,
        00145263,
        00145326,
        00145362,
        00145623,

        00145632,
        00146235,
        00146253,
        00146325,
        00146352,

        00146523,
        00146532,
        00152346,
        00152364,
        00152436,

        00152463,
        00152634,
        00152643,
        00153246,
        00153264,

        00153426,
        00153462,
        00153624,
        00153642,
        00154236,

        00154263,
        00154326,
        00154362,
        00154623,
        00154632,

        00156234,
        00156243,
        00156324,
        00156342,
        00156423,

        00156432,
        00162345,
        00162354,
        00162435,
        00162453,

        00162534,
        00162543,
        00163245,
        00163254,
        00163425,

        00163452,
        00163524,
        00163542,
        00164235,
        00164253,

        00164325,
        00164352,
        00164523,
        00164532,
        00165234,

        00165243,
        00165324,
        00165342,
        00165423,
        00165432,

        00213456,
        00213465,
        00213546,
        00213564,
        00213645,

        00213654,
        00214356,
        00214365,
        00214536,
        00214563,

        00214635,
        00214653,
        00215346,
        00215364,
        00215436,

        00215463,
        00215634,
        00215643,
        00216345,
        00216354,

        00216435,
        00216453,
        00216534,
        00216543,
        00231456,

        00231465,
        00231546,
        00231564,
        00231645,
        00231654,

        00234156,
        00234165,
        00234516,
        00234561,
        00234615,

        00234651,
        00235146,
        00235164,
        00235416,
        00235461,

        00235614,
        00235641,
        00236145,
        00236154,
        00236415,

        00236451,
        00236514,
        00236541,
        00241356,
        00241365,

        00241536,
        00241563,
        00241635,
        00241653,
        00243156,

        00243165,
        00243516,
        00243561,
        00243615,
        00243651,

        00245136,
        00245163,
        00245316,
        00245361,
        00245613,

        00245631,
        00246135,
        00246153,
        00246315,
        00246351,

        00246513,
        00246531,
        00251346,
        00251364,
        00251436,

        00251463,
        00251634,
        00251643,
        00253146,
        00253164,

        00253416,
        00253461,
        00253614,
        00253641,
        00254136,

        00254163,
        00254316,
        00254361,
        00254613,
        00254631,

        00256134,
        00256143,
        00256314,
        00256341,
        00256413,

        00256431,
        00261345,
        00261354,
        00261435,
        00261453,

        00261534,
        00261543,
        00263145,
        00263154,
        00263415,

        00263451,
        00263514,
        00263541,
        00264135,
        00264153,

        00264315,
        00264351,
        00264513,
        00264531,
        00265134,

        00265143,
        00265314,
        00265341,
        00265413,
        00265431,

        00312456,
        00312465,
        00312546,
        00312564,
        00312645,

        00312654,
        00314256,
        00314265,
        00314526,
        00314562,

        00314625,
        00314652,
        00315246,
        00315264,
        00315426,

        00315462,
        00315624,
        00315642,
        00316245,
        00316254,

        00316425,
        00316452,
        00316524,
        00316542,
        00321456,

        00321465,
        00321546,
        00321564,
        00321645,
        00321654,

        00324156,
        00324165,
        00324516,
        00324561,
        00324615,

        00324651,
        00325146,
        00325164,
        00325416,
        00325461,

        00325614,
        00325641,
        00326145,
        00326154,
        00326415,

        00326451,
        00326514,
        00326541,
        00341256,
        00341265,

        00341526,
        00341562,
        00341625,
        00341652,
        00342156,

        00342165,
        00342516,
        00342561,
        00342615,
        00342651,

        00345126,
        00345162,
        00345216,
        00345261,
        00345612,

        00345621,
        00346125,
        00346152,
        00346215,
        00346251,

        00346512,
        00346521,
        00351246,
        00351264,
        00351426,

        00351462,
        00351624,
        00351642,
        00352146,
        00352164,

        00352416,
        00352461,
        00352614,
        00352641,
        00354126,

        00354162,
        00354216,
        00354261,
        00354612,
        00354621,
    };

    for (uint16_t i = 0; i < std::size(expectedEdgesInts); ++i) {
        uint32_t intEdges = conv.lexIndexEdgesToIntEdges(i);
        ASSERT_EQ(expectedEdgesInts[i], intEdges);
    }
}

TEST(ruCubeStateConverterTest, convertIntCornersToLexIndexCornersPermTest) {
    ruCubeStateConverter conv;

    const std::vector<uint64_t> cornersInts = {
        0101112131415,
        0101112131514,
        0101112141315,
        0101112141513,
        0101112151314,

        0101112151413,
        0101113121415,
        0101113121514,
        0101113141215,
        0101113141512,

        0101113151214,
        0101113151412,
        0101114121315,
        0101114121513,
        0101114131215,

        0101114131512,
        0101114151213,
        0101114151312,
        0101115121314,
        0101115121413,

        0101115131214,
        0101115131412,
        0101115141213,
        0101115141312,
        0101211131415,

        0101211131514,
        0101211141315,
        0101211141513,
        0101211151314,
        0101211151413,

        0101213111415,
        0101213111514,
        0101213141115,
        0101213141511,
        0101213151114,

        0101213151411,
        0101214111315,
        0101214111513,
        0101214131115,
        0101214131511,

        0101214151113,
        0101214151311,
        0101215111314,
        0101215111413,
        0101215131114,

        0101215131411,
        0101215141113,
        0101215141311,
        0101311121415,
        0101311121514,
    };

    for (uint16_t i = 0; i < std::size(cornersInts); ++i) {
        uint16_t cornersLexIndex = conv.intCornersToLexIndexCornersPerm(cornersInts[i]);
        ASSERT_EQ(i, cornersLexIndex);
    }
}

TEST(ruCubeStateConverterTest, convertIntCornersToLexIndexCornersOrientTest) {
    ruCubeStateConverter conv;

    const std::vector<uint64_t> cornersInts = {
        0101112131415,
        0202122232425,
        0102112231425,
        0404142434445,

        0401142134415,
        0402142234425,
        0452443224120,
        0451443124110,

        0452443221110,
        0422443211510,
        0402423112225,
    };

    const std::vector<uint16_t> cornersOrientsExpected = {
        0,
        364,
        91,
        728,

        546,
        637,
        637,
        546,

        630,
        630,
        598
    };

    for (uint16_t i = 0; i < std::size(cornersInts); ++i) {
        uint16_t cornersLexIndex = conv.intCornersToLexIndexCornersOrient(cornersInts[i]);
        ASSERT_EQ(cornersOrientsExpected[i], cornersLexIndex);
    }
}

TEST(ruCubeStateConverterTest, convertLexIndexCornersToIntCornersTest) {
    ruCubeStateConverter conv;

    const std::vector<uint16_t> lexIndexCornersPerms = {
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10
    };

    const std::vector<uint16_t> lexIndexCornersOrients = {
        0,
        364,
        91,
        728,

        546,
        637,
        637,
        546,

        630,
        630,
        598
    };

    const std::vector<uint64_t> expectedCornersInts = {
        0101112131415,
        0202122232524,
        0102112241325,
        0404142444543,

        0401142154314,
        0402142254423,
        0402143224425,
        0401143124514,

        0402143241215,
        0402143241512,
        0402123152224,
    };

    for (uint16_t i = 0; i < std::size(expectedCornersInts); ++i) {
        uint64_t cornersInt = conv.lexIndexCornersToIntCorners(lexIndexCornersPerms[i], lexIndexCornersOrients[i]);
        ASSERT_EQ(expectedCornersInts[i], cornersInt);
    }
}
