//
//  SalesAssociateDataManager.h
//  GPShopper
//
//  Created by Patrick Caraher on 2/2/14.
//  Copyright (c) 2014 GPShopper. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol SalesAssociateDataManagerDelegate
-(void)visibleCustomers:(NSDictionary *)customerBeacons;
@end

@interface SalesAssociateDataManager : NSObject

/**
 Start up the SalesAssociateDataManager using the assigned delegate.
 */
+ (void)startSalesAssociateDataManagerForDelegate:(id<SalesAssociateDataManagerDelegate>) delegate;

/**
 Delegate that implements the SalesAssociateDataManagerDelegate protocol.
 */
@property (nonatomic, retain) id<SalesAssociateDataManagerDelegate> delegate;

/**
 Return a globally shared instance of the SalesAssociateDataManager.
 */
+ (SalesAssociateDataManager *)defaultDataManager;

/**
 The url string used for configuration data fetches.
 */
+ (void)setRequestUrl:(NSString *)requestUrl;

/**
 The maximum amount of time that a Customer is allowed to not report before it
 is removed from the customer queue.
 */
@property (readwrite) NSTimeInterval maxInactiveInterval;

@end
