/**
 * CS 225 lab_avl
 * @file main.cpp
 * @author Daniel Hoodin in Spring 2008.
 * Modified by Kyle Johnson in Fall 2010.
 * Modified by Sean Massung in Summer 2012:
 *  - added templates
 *  - CRTP tree printing
 *  - doxygen
 */

#include <iostream>
#include <sstream>
#include <string>
#include "avltree.h"
#include "coloredout.h"
#include "catch_config.h"

TEST_CASE("testRotateLeft")
{
    AVLTree<int, int> tree;
    vector<int> expected({0, 6, 4, 7, 2, 5, 0, 9, 0});
    tree.insert(4, 4);
    tree.insert(6, 6);
    tree.insert(2, 2);
    tree.insert(7, 7);
    tree.insert(5, 5);
    tree.insert(9, 9);
    REQUIRE(expected == tree.heap());
}

TEST_CASE("testRotateRight")
{
    AVLTree<int, int> tree;
    vector<int> expected({0, 3, 0, 6, 0, 0, 5, 8, 0});
    tree.insert(3, 3);
    tree.insert(0, 0);
    tree.insert(8, 8);
    tree.insert(6, 6);
    tree.insert(5, 5);
    REQUIRE(expected == tree.heap());
}

TEST_CASE("testRotateLeftRight")
{
    AVLTree<int, int> tree;
    vector<int> expected({0, 3, 1, 5, 0, 2, 0, 8, 0});
    tree.insert(5, 5);
    tree.insert(1, 1);
    tree.insert(8, 8);
    tree.insert(0, 0);
    tree.insert(3, 3);
    tree.insert(2, 2);
    REQUIRE(expected == tree.heap());
}

TEST_CASE("testRotateRightLeft")
{
    AVLTree<int, int> tree;
    vector<int> expected({0, 6, 3, 8, 0});
    tree.insert(3, 3);
    tree.insert(8, 8);
    tree.insert(6, 6);
    REQUIRE(expected == tree.heap());
}

TEST_CASE("testManyInsertions")
{
    AVLTree<int, string> tree;
    vector<int> expected({0, 61, 26, 87, 17, 36, 76, 94, 3, 23, 31, 42, 73, 78, 92, 96, 1, 11, 18, 24, 0, 0, 41, 45, 71, 74, 0, 82, 0, 93, 95, 0});
    tree.insert(94, "data for 94");
    tree.insert(87, "data for 87");
    tree.insert(61, "data for 61");
    tree.insert(96, "data for 96");
    tree.insert(76, "data for 76");
    tree.insert(92, "data for 92");
    tree.insert(42, "data for 42");
    tree.insert(78, "data for 78");
    tree.insert(17, "data for 17");
    tree.insert(11, "data for 11");
    tree.insert(41, "data for 41");
    tree.insert(95, "data for 95");
    tree.insert(36, "data for 36");
    tree.insert(26, "data for 26");
    tree.insert(23, "data for 23");
    tree.insert(93, "data for 93");
    tree.insert(31, "data for 31");
    tree.insert( 3, "data for 3");
    tree.insert(45, "data for 45");
    tree.insert(18, "data for 18");
    tree.insert(73, "data for 73");
    tree.insert(24, "data for 24");
    tree.insert(74, "data for 74");
    tree.insert( 1, "data for 1");
    tree.insert(71, "data for 71");
    tree.insert(82, "data for 82");
    REQUIRE(expected == tree.heap());
}

TEST_CASE("testManyRemovals")
{
    AVLTree<int, string> tree;
    vector<int> expected({0, 45, 26, 87, 17, 36, 78, 93, 3, 23, 31, 42, 74, 82, 92, 96, 1, 11, 18, 24, 0, 0, 41, 0});
    tree.insert(94, "data for 94");
    tree.insert(87, "data for 87");
    tree.insert(61, "data for 61");
    tree.insert(96, "data for 96");
    tree.insert(76, "data for 76");
    tree.insert(92, "data for 92");
    tree.insert(42, "data for 42");
    tree.insert(78, "data for 78");
    tree.insert(17, "data for 17");
    tree.insert(11, "data for 11");
    tree.insert(41, "data for 41");
    tree.insert(95, "data for 95");
    tree.insert(36, "data for 36");
    tree.insert(26, "data for 26");
    tree.insert(23, "data for 23");
    tree.insert(93, "data for 93");
    tree.insert(31, "data for 31");
    tree.insert( 3, "data for 3");
    tree.insert(45, "data for 45");
    tree.insert(18, "data for 18");
    tree.insert(73, "data for 73");
    tree.insert(24, "data for 24");
    tree.insert(74, "data for 74");
    tree.insert( 1, "data for 1");
    tree.insert(71, "data for 71");
    tree.insert(82, "data for 82");
    tree.remove(95);
    tree.remove(94);;
    tree.remove(61);
    tree.remove(76);
    tree.remove(73);
    tree.remove(71);
    REQUIRE(expected == tree.heap());
}