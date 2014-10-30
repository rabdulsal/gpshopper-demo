//
//  SASCustomerData.h
//  GPShopper
//
//  Created by Patrick Caraher on 2/3/14.
//  Copyright (c) 2014 GPShopper. All rights reserved.
//

#import <Foundation/Foundation.h>

#define kUnknownPosition @"Unknown"

@interface SASCustomerData : NSObject

/**
 Distinct queue number for the Customer.
 */
-(NSNumber *)queueNumber;

/**
 The position at which the customer was last seen.  nil if not known.
 */
-(NSString *)position;

/**
 The Distance at which the customer was last seen.
 */
-(NSString *)distance;

/**
 The name of the customer, if known.
 */
-(NSString *)customerName;

/**
 How long ago did we last see the beacon for this Customer?
 */
-(NSTimeInterval)timeSinceLastSeen;

/**
 Update time at which the Customer was last seen to be now.
 */
-(void)updateLastSeenTime;

/**
 The backing data store.
 */
@property (nonatomic, retain) NSDictionary *dataDictionary;

/**
 Customer is requesting a Sales Associate.
 */
@property (readwrite) BOOL requestingSalesAssociate;

/**
 A customizable, second Sales Associate request.
 */
@property (readwrite) BOOL requestingSalesAssociate2;

/**
 A customizable, third Sales Associate request.
 */
@property (readwrite) BOOL requestingSalesAssociate3;

@end
