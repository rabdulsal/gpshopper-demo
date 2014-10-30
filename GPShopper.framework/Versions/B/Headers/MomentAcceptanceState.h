//
//  MomentAcceptanceState.h
//  northface
//
//  Created by Patrick Caraher on 8/28/12.
//  Copyright (c) 2012 GPShopper. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface MomentAcceptanceState : NSObject

+ (MomentAcceptanceState *)momentAcceptanceStateForId:(NSUInteger)stateId;
- (MomentAcceptanceState *)initWithStateId:(NSUInteger)sid;

@property (assign) NSUInteger stateId;
- (NSString *)title;

- (BOOL)isAccepted;
- (BOOL)isFeatured;
- (BOOL)isRejected;
- (BOOL)isSubmitted;

@end
