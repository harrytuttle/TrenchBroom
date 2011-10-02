/*
This file is part of TrenchBroom.

TrenchBroom is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

TrenchBroom is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with TrenchBroom.  If not, see <http://www.gnu.org/licenses/>.
*/

#import <Cocoa/Cocoa.h>
#import "Figure.h"
#import "Math.h"

@class Grid;
@class PickingHit;

@interface EditingPlaneFigure : NSObject <Figure> {
    Grid* grid;
    TPlane plane;
    GLfloat gridPoints[2][2][3];
    int rows;
    int cols;
}

- (id)initWithGrid:(Grid *)theGrid plane:(const TPlane *)thePlane bounds:(const TBoundingBox *)theBounds ray:(const TRay *)theRay;
- (void)setBounds:(const TBoundingBox *)theBounds ray:(const TRay *)theRay;

@end