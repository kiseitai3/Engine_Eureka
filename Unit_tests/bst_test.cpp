#include <iostream>
#include <string>
#include <vector>
#include "../typedefs.h"
#include "../BST.h"

int main()
{
    int res;
    BinarySearchTree<size_t, size_t> bst;
    std::vector<size_t> contents;

    for(size_t i = 0; i < 500; i++)
    {
        bst.insert(i, i * (i-1));
    }

    bst.print();
    std::cin >> res;
    contents = bst.getContents();

    for(size_t i = 0; i < contents.size(); i++)
    {
        std::cout << contents[i] << std::endl;
    }

    std::cin >> res;

    std::cout << contents[40] << std::endl;
    std::cin >> res;
    return 0;

}
