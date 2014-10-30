//
//  SCNullHandling.h
//  northface
//
//  Created by kimberly on 3/28/12.
//  Copyright (c) 2012 GPShopper. All rights reserved.
//

#import <Foundation/Foundation.h>


@protocol SCNullHandling < NSObject >

-(BOOL)containsNulls;
-(NSArray *)newWithoutNulls;

@end


@interface NSArray ( SCNullHandling ) < SCNullHandling >
@end

@interface NSDictionary ( SCNullHandling ) < SCNullHandling >
- (id) nullSafeObjectForKey:(id)key;
@end
