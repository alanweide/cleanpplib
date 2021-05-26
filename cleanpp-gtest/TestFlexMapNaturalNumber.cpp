#include <gtest/gtest.h>

#include <string>
#include <sstream>
#include <natural_number.hpp>
#include <map.hpp>
#include <map_impl/map_impl.hpp>
#include <map_impl/map_on_set.hpp>

using namespace cleanpp;

typedef natural_number nn_type;
typedef map<nn_type, nn_type> map_type;

static std::string empty_map = "{}";

static std::string mapToString(map_type &m){
    std::stringstream m_stm;
    m_stm << m;
    std::string m_str = m_stm.str();
    return m_str; 
}

TEST(FlexMapNaturalNumber, InitializerDefTest) {
    map_type m;
    std::string m_str = mapToString(m);
    EXPECT_TRUE(m_str == empty_map);
}

TEST(FlexMapNaturalNumber, ClearEmptyTest) {
    map_type m;

    m.clear();

    std::string m_str = mapToString(m);
    EXPECT_TRUE(m_str == empty_map);
}

TEST(FlexMapNaturalNumber, ClearSingleElementTest) {
    map_type m;

    nn_type key(5L);
    nn_type val(6L);

    m.add(std::move(key), std::move(val));

    m.clear();

    std::string m_str = mapToString(m);
    EXPECT_TRUE(m_str == empty_map);
}

TEST(FlexMapNaturalNumber, ClearManyElementsTest) {
    map_type m;

    int numPairs = 12;
    for(long i = 0; i < numPairs; i++){
        nn_type key(i);
        nn_type val(2*i);
        m.add(std::move(key), std::move(val));
    }

    m.clear();

    std::string m_str = mapToString(m);
    EXPECT_TRUE(m_str == empty_map);
}

TEST(FlexMapNaturalNumber, Size_InitialTest) {
    map_type m;
    EXPECT_TRUE(m.size() == 0);
}

TEST(FlexMapNaturalNumber, Size_NonEmptyTest){
    map_type m;
    nn_type key(4L);
    nn_type val(8L);
    m.add(std::move(key), std::move(val));
    EXPECT_TRUE(m.size() == 1);
}

TEST(FlexMapNaturalNumber, Size_Empty_AddRemTest){
    map_type m;
    nn_type key(5L);
    nn_type val(6L);
    
    m.add(std::move(key), std::move(val));
    m.removeAny();

    EXPECT_TRUE(m.size() == 0);
}

TEST(FlexMapNaturalNumber, AddToEmptyTest) {
    map_type m;
    std::string expected = "{(5, 6)}";

    nn_type key(5L);
    nn_type val(6L);
    
    m.add(std::move(key), std::move(val));
    
    std::string m_str = mapToString(m);
    EXPECT_TRUE(m_str == expected);
}

TEST(FlexMapNaturalNumber, AddToNonEmptyTest){
    map_type m;
    std::string expected_poss1 = "{(5, 6), (7, 8)}", expected_poss2 = "{(7, 8), {5, 6)}";

    nn_type key1(5L), val1(6L), key2(7L), val2(8L);
    m.add(std::move(key1), std::move(val1));
    m.add(std::move(key2), std::move(val2));

    std::string m_str = mapToString(m);
    EXPECT_TRUE(m_str == expected_poss1 || m_str == expected_poss2);
}

TEST(FlexMapNaturalNumber, RemoveAnyToEmptyTest) {
    map_type m;
    nn_type key(1L), val(2L), expected_key, expected_val;
    pair<nn_type, nn_type> result;
    pair<nn_type, nn_type> expected_result(nn_type(1L), nn_type(2L));
    m.add(std::move(key), std::move(val));

    result = m.removeAny();

    std::string m_str = mapToString(m);
    EXPECT_TRUE(m_str == empty_map);
    EXPECT_TRUE(key == expected_key);
    EXPECT_TRUE(val == expected_val);
    EXPECT_TRUE(result == expected_result);
}

TEST(FlexMapNaturalNumber, RemoveAnyToNonEmptyTest){
    map_type m;
    std::string expected_poss1 = "{(1, 2)}", expected_poss2 = "{(3, 4)}";
    nn_type key1(1L), val1(2L), key2(3L), val2(4L),  expected_key1, expected_val1,
        expected_key2, expected_val2;

    pair<nn_type, nn_type> result;
    pair<nn_type, nn_type> expResult_poss1(nn_type(1L), nn_type(2L)), expResult_poss2(nn_type(3L), nn_type(4L));
    m.add(std::move(key1), std::move(val1));
    m.add(std::move(key2), std::move(val2));

    result = m.removeAny();

    std::string m_str = mapToString(m);
    EXPECT_TRUE(m_str == expected_poss1 || m_str == expected_poss2);
    EXPECT_TRUE(key1 == expected_key1);
    EXPECT_TRUE(val1 == expected_val1);
    EXPECT_TRUE(key2 == expected_key2);
    EXPECT_TRUE(val2 == expected_val2);
    EXPECT_TRUE(result == expResult_poss1 || result == expResult_poss2);
}

TEST(FlexMapNaturalNumber, RemoveOnlyElementTest){
    map_type m;
    nn_type key(1L), val(2L), expected_key, expected_val, remover(1L);
    pair<nn_type, nn_type> result, expected_result(nn_type(1L), nn_type(2L));
    m.add(std::move(key), std::move(val));

    result = m.remove(std::move(remover));

    std::string m_str = mapToString(m);
    EXPECT_TRUE(m_str == empty_map);
    EXPECT_TRUE(key == expected_key);
    EXPECT_TRUE(val == expected_val);
    EXPECT_TRUE(result == expected_result);
}

TEST(FlexMapNaturalNumber, RemoveToNonEmptyTest){
    map_type m;
    std::string expected = "{(3, 4)}";
    nn_type key1(1L), expected_key1, val1(2L), expected_val1, key2(3L), expected_key2, val2(4L), expected_val2, remover(1L);
    pair<nn_type, nn_type> result, expected_result(nn_type(1L), nn_type(2L));
    m.add(std::move(key1), std::move(val1));
    m.add(std::move(key2), std::move(val2));

    result = m.remove(std::move(remover));

    std::string m_str = mapToString(m);

    EXPECT_TRUE(m_str == expected);
    EXPECT_TRUE(key1 == expected_key1);
    EXPECT_TRUE(val1 == expected_val1);
    EXPECT_TRUE(key2 == expected_key2);
    EXPECT_TRUE(val2 == expected_val2);
    EXPECT_TRUE(result == expected_result);

}

TEST(FlexMapNaturalNumber, RemoveToNonEmptySecondAddTest){
    map_type m;
    std::string expected = "{(1, 2)}";
    nn_type key1(1L), expected_key1, val1(2L), expected_val1, key2(3L), expected_key2, val2(4L), expected_val2, remover(3L);
    pair<nn_type, nn_type> result, expected_result(nn_type(3L), nn_type(4L));
    m.add(std::move(key1), std::move(val1));
    m.add(std::move(key2), std::move(val2));

    result = m.remove(std::move(remover));

    std::string m_str = mapToString(m);

    
    EXPECT_TRUE(m_str == expected);
    EXPECT_TRUE(key1 == expected_key1);
    EXPECT_TRUE(val1 == expected_val1);
    EXPECT_TRUE(key2 == expected_key2);
    EXPECT_TRUE(val2 == expected_val2);
    EXPECT_TRUE(result == expected_result);

}

TEST(FlexMapNaturalNumber, HasKeyEmptyTest) {
    map_type m;
    nn_type a;

    bool hasKey = m.hasKey(std::move(a));

    std::string m_str = mapToString(m);
    EXPECT_TRUE(m_str == empty_map);
    EXPECT_FALSE(hasKey);
}

TEST(FlexMapNaturalNumber, HasKeyNonEmptyTrueTest){
    map_type m;
    std::string expected = "{(0, 0)}";
    nn_type key1, val1, a;

    m.add(std::move(key1), std::move(val1));

    bool hasKey = m.hasKey(std::move(a));

    std::string m_str = mapToString(m);
    EXPECT_TRUE(m_str == expected);
    EXPECT_TRUE(hasKey);

}

TEST(FlexMapNaturalNumber, BigMapHasKeyTest){
    map_type m;
    int expected_size = 12;
    nn_type a;

    int numElem = 12;
    for(long i = 0; i < numElem; i++) {
        nn_type key(i), val(2 * i);
        m.add(std::move(key), std::move(val));
    }

    bool hasKey = m.hasKey(std::move(a));

    std::string m_str = mapToString(m);
    EXPECT_TRUE(m.size() == expected_size);
    EXPECT_TRUE(hasKey);
}

TEST(FlexMapNaturalNumber, ContainsNonEmptyFalseTest) {
    map_type m;
    std::string expected = "{(1, 2)}";
    nn_type searchKey, key(1L), val(2L);

    m.add(std::move(key), std::move(val));

    bool hasKey = m.hasKey(std::move(searchKey));

    std::string m_str = mapToString(m);
    EXPECT_TRUE(m_str == expected);
    EXPECT_FALSE(hasKey);
}

TEST(FlexMapNaturalNumber, CombineWithEmpty) {
    map_type receiver_m, transmitter_m;
    
    receiver_m.combine_with(std::move(transmitter_m));

    std::string receiver_str = mapToString(receiver_m);
    std::string transmitter_str = mapToString(transmitter_m);
    EXPECT_TRUE(receiver_str == empty_map);
    EXPECT_TRUE(transmitter_str == empty_map);
    
}

TEST(FlexMapNaturalNumber, CombineWithBothNonEmpty) {
    map_type receiver_m, transmitter_m;
    std::string expected_poss1 = "{(1, 2), (3, 4)}", expected_poss2 = "{(3, 4), (1, 2)}";
    nn_type key1(1L), val1(2L), key2(3L), val2(4L);

    receiver_m.add(std::move(key1), std::move(val1));
    transmitter_m.add(std::move(key2), std::move(val2));

    receiver_m.combine_with(std::move(transmitter_m));

    std::string receiver_str = mapToString(receiver_m);
    std::string transmitter_str = mapToString(transmitter_m);
    EXPECT_TRUE(receiver_str == expected_poss1 || receiver_str == expected_poss2);
    EXPECT_TRUE(transmitter_str == empty_map);
    
}

TEST(FlexMapNaturalNumber, CombineWithReceiverNonEmpty) {
    map_type receiver_m, transmitter_m;
    std::string expected_poss1 = "{(1, 2), (3, 4)}", expected_poss2 = "{(3, 4), (1, 2)}";
    nn_type key1(1L), val1(2L), key2(3L), val2(4L);

    receiver_m.add(std::move(key1), std::move(val1));
    receiver_m.add(std::move(key2), std::move(val2));

    receiver_m.combine_with(std::move(transmitter_m));

    std::string receiver_str = mapToString(receiver_m);
    std::string transmitter_str = mapToString(transmitter_m);
    EXPECT_TRUE(receiver_str == expected_poss1 || receiver_str == expected_poss2);
    EXPECT_TRUE(transmitter_str == empty_map);
    
}

TEST(FlexMapNaturalNumber, CombineWithTransmitterNonEmpty) {
    map_type receiver_m, transmitter_m;
    std::string expected_poss1 = "{(1, 2), (3, 4)}", expected_poss2 = "{(3, 4), (1, 2)}";
    nn_type key1(1L), val1(2L), key2(3L), val2(4L);

    transmitter_m.add(std::move(key1), std::move(val1));
    transmitter_m.add(std::move(key2), std::move(val2));

    receiver_m.combine_with(std::move(transmitter_m));

    std::string receiver_str = mapToString(receiver_m);
    std::string transmitter_str = mapToString(transmitter_m);
    EXPECT_TRUE(receiver_str == expected_poss1 || receiver_str == expected_poss2);
    EXPECT_TRUE(transmitter_str == empty_map);
    
}