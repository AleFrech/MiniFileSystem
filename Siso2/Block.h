//
// Created by alejandrofrech on 08-24-16.
//

#ifndef SISO2_BLOCK_H
#define SISO2_BLOCK_H


class Block {
public:
    char Buffer[4088];
    int Position;
    int  nextBlock;
};


#endif //SISO2_BLOCK_H
