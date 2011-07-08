//
//  VBOMemBlock.m
//  TrenchBroom
//
//  Created by Kristian Duske on 16.03.10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import "VBOMemBlock.h"
#import "VBOBuffer.h"

@implementation VBOMemBlock

- (id)init {
    if (self = [super init]) {
        state = BS_FREE;
    }
    
    return self;
}

- (id)initBlockIn:(VBOBuffer *)theVboBuffer at:(int)theAddress capacity:(int)theCapacity {
    if (self = [self init]) {
        vboBuffer = theVboBuffer;
        address = theAddress;
        capacity = theCapacity;
    }
    
    return self;
}

- (int)address {
    return address;
}

- (void)setAddress:(int)theAddress {
    address = theAddress;
}

- (int)capacity {
    return capacity;
}

- (EVBOMemBlockState)state {
    return state;
}

- (VBOBuffer *)vbo {
    return vboBuffer;
}

- (void)setCapacity:(int)aSize {
    capacity = aSize;
}

- (void)setState:(EVBOMemBlockState)theState {
    state = theState;
}

- (void)activate {
    [vboBuffer activate];
}

- (void)deactivate {
    [vboBuffer deactivate];
}

- (int)writeBuffer:(const void*)theBuffer offset:(int)theOffset count:(int)theCount {
    [vboBuffer writeBuffer:theBuffer address:address + theOffset count:theCount];
    return theOffset + theCount;
}

- (int)writeByte:(unsigned char)theByte offset:(int)theOffset {
    [vboBuffer writeByte:theByte address:address + theOffset];
    return theOffset + 1;
}

- (int)writeFloat:(float)theFloat offset:(int)theOffset {
    [vboBuffer writeFloat:theFloat address:address + theOffset];
    return theOffset + sizeof(float);
}

- (int)writeColor4fAsBytes:(const TVector4f *)theVector offset:(int)theOffset {
    [vboBuffer writeColor4fAsBytes:theVector address:address + theOffset];
    return theOffset + 4;
}

- (int)writeVector4f:(const TVector4f *)theVector offset:(int)theOffset {
    [vboBuffer writeVector4f:theVector address:address + theOffset];
    return theOffset + 4 * sizeof(float);
}

- (int)writeVector3f:(const TVector3f *)theVector offset:(int)theOffset {
    [vboBuffer writeVector3f:theVector address:address + theOffset];
    return theOffset + 3 * sizeof(float);
}

- (int)writeVector2f:(const TVector2f *)theVector offset:(int)theOffset {
    [vboBuffer writeVector2f:theVector address:address + theOffset];
    return theOffset + 2 * sizeof(float);
}

- (VBOMemBlock *)previous {
    return previous;
}

- (VBOMemBlock *)next {
    return next;
}

- (void)setPrevious:(VBOMemBlock *)memBlock {
    previous = memBlock;
}

- (void)setNext:(VBOMemBlock *)memBlock {
    next = memBlock;
}

- (void)insertBetweenPrevious:(VBOMemBlock *)previousBlock next:(VBOMemBlock *)nextBlock {
    if ((previousBlock != nil && [previousBlock next] != nextBlock) || (nextBlock != nil && [nextBlock previous] != previousBlock))
        [NSException raise:NSInvalidArgumentException format:@"cannot insert between unchained blocks"];
    
    [previousBlock setNext:self];
    previous = previousBlock;
    [nextBlock setPrevious:self];
    next = nextBlock;
}

- (void)remove {
    [previous setNext:next];
    [next setPrevious:previous];
    
    previous = nil;
    next = nil;
}

- (void)free {
    [vboBuffer freeMemBlock:self];
}

@end
