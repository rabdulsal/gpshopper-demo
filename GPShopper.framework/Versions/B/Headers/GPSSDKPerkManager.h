//
//  GPSSDKPerkManager.h
//  GPShopper
//
//  Created by PJ Caraher on 3/24/14.
//  Copyright (c) 2014 GPShopper. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SCPerk.h"
#import "SearchResult.h"

@protocol GPSSDKPerkManagerDelegate
-(void)fetchedProximityPerk:(SCPerk *)perk forProduct:(SCSearchResultProduct *)product;
@end

@interface GPSSDKPerkManager : NSObject

/**
 Shared, default instance of the GPSSDKPerkManager.
 */
+ (GPSSDKPerkManager *)defaultInstance;

/**
 * Fetch any Proxmity Perks that may exist
 */
-(void)fetchProximityPerk;

/**
 * Name of the Perk to be fetched.  Defaults to "perk"
 */
@property (nonatomic, copy) NSString *perkName;

/**
 * Radius for searching proxmity perks.  Units are 1/100 of a mile.  Default
 * value is 50 miles.
 */
@property NSUInteger proxmityPerkSearchRadius;

/**
 * The last time that an attempt was made to fetch a proximity perk.
 * Value is -1 if no attempt has yet been made.
 */
@property (readonly) double timeOfLastFetch;

/**
 * Delegate that will be notified when a Perk has been fetched.
 */
@property (nonatomic, assign) id <GPSSDKPerkManagerDelegate> delegate;

@end
