//
//  GPSSDKConfiguration.h
//  GPShopper
//
//  Created by PJ Caraher on 2/25/14.
//  Copyright (c) 2014 GPShopper. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Location.h"

@protocol  BannerActionDelegate;

#define kReachabilitySuccessNotification @"ReachabilitySuccessNotification"
#define kReachabilityFailedNotification @"ReachabilityFailedNotification"

#define kStaticCacheOverrideImageHost @"GPSSDKStaticCacheImageHost"

@protocol GPSSDKConfigurationDelegate
@optional
-(void)locationUpdated:(SCGeoLocation *)location;
@end

@interface GPSSDKConfiguration : NSObject

/**
 *  Perform any Generic preparation work, required for using the GPShopper SDK.
 */
+(void)configureForSDK;

/**
 *  Perform any Generic preparation work, required for using the GPShopper SDK
 *  and set the delegate.
 */
+(void)configureForSDKWithDelegate:(id <GPSSDKConfigurationDelegate>)delegate;

/**
 * Call checkReachability and post a notification on Success or Failure.
 */
+(void)checkReachability;

/**
 *  Configure the BannerManager for working with the GPShopper framework.  Make certain that the
 *  GPSSDK properties have been set.
 */
+(void)configureBannerManager:(id <BannerActionDelegate>)delegate;

/**
 *  Inform the Configuration to check for a change in location.
 */
+(void)detectLatLon;

/**
 Shared, default instance of the GPSSDKConfiguration.
 */
+ (GPSSDKConfiguration *)defaultInstance;

/**
 SCGeoLocation object that can be queried for the most recent location.
 */
@property (retain, readonly) SCGeoLocation *geoLocation;


@end
