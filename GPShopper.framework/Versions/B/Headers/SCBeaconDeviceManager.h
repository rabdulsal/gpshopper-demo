//
//  SCBeaconDeviceManager
//
//  Created by Patrick Caraher on 6/3/13.
//  Copyright (c) 2013 GPShopper. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>


#define kDefaultBTLEPayloadRefreshSecondsKey @"DefaultBTLEPayloadRefreshSeconds"

@class GPSSDKOptIn;
@class SCBeaconDeviceManager;

@protocol SCBeaconDeviceManagerDelegate <NSObject>
@optional
-(void)scBeaconDeviceManager:(SCBeaconDeviceManager *)manager enteredBeacon:(CLBeacon *)beacon withUserInfo:(NSDictionary *)userInfo;
-(void)scBeaconDeviceManager:(SCBeaconDeviceManager *)manager didEnterRegion:(CLBeaconRegion *)region;
-(void)scBeaconDeviceManager:(SCBeaconDeviceManager *)manager didExitRegion:(CLBeaconRegion *)region;
-(void)scBeaconDeviceManager:(SCBeaconDeviceManager *)manager receivedOptIn:(GPSSDKOptIn *)optin;
-(void)scBeaconDeviceManagerWasUpdated:(SCBeaconDeviceManager *)manager;
@end


/**
 SCBeaconDeviceManager coordinates the monitoring and reaction for configured iBeacons.
 
 The SCBeaconDeviceManager relies on the SCBeaconDeviceFetcher to fetch the beacon configuration
 information.  The SCBeaconDeviceManager then sets up a CLBeaconRegion monitor that will begin
 ranging beacons once the CLBeaconRegion has been entered.  (The SCBeaconDeviceManager also ceases
 to range beacons after the CLBeaconRegion has been exited.)
 
 The SCBeaconDeviceManager periodically refreshes the configuration data.
 
 */
@interface SCBeaconDeviceManager : NSObject

/**
 Delegate that implements the SCBeaconDeviceManagerDelegate protocol.
 */
@property (nonatomic, retain) id<SCBeaconDeviceManagerDelegate> delegate;

/**
 Start up the BeaconDeviceManager using the assigned delegate.
 */
+ (void)startBeaconDeviceManagerForDelegate:(id<SCBeaconDeviceManagerDelegate>) delegate reqireOptIn:(BOOL)optInRequired;

/**
 Return a globally shared instance of the SCBeaconDeviceManager.
 */
+ (SCBeaconDeviceManager *)defaultDataCoordinator;

/**
 Manually fetch the beacon configuration data.
 */
- (void)fetch;

/**
 The SCBeaconDeviceManager tracks the history of beacon campaign notifications.  These campaign notifications
 may be throttled by a timeInterval.  Clearing the notificationHistory wipes out any memory of prior notifications.
 */
- (void)clearNotificationHistory;

/**
 Bool indicating whether or not the device has opted in to Beacons.
 
 By default, this value is NO.
 */
+ (BOOL)isOptedIn;

/**
 *  Indates whether or not the Beacons SDK has been enabled for this client.
 *
 *  @return YES if beacons SDK has been enabled.
 */
- (BOOL)isEnabled;

/**
 Set whether the user opts in or out of Beacons.
 
 By default, each device must opt in to beacons.
 */
+(void)optIn:(BOOL)optIn;

/**
 We are ranging beacons if three conditions are met;
 1) CoreBluetooth is enabled.
 2) CoreLocation is enabled.
 3) We have set optIn to YES.
 */
-(BOOL)isRangingBeacons;

/**
 If Customer Sales Associate exists, we may choose to call them.
 */
-(void)requestSalesAssociate;

/**
 Are we requesting a Customer Sales Associate?
 */
-(BOOL)isRequestingSalesAssociate;

/**
 Clear a request to the Sales Associate
 */
-(void)clearRequestSalesAssociate;

/**
 Two more Sales Associate request that are customizable.
 */
-(void)requestSalesAssociate2;
-(BOOL)isRequestingSalesAssociate2;
-(void)clearRequestSalesAssociate2;

-(void)requestSalesAssociate3;
-(BOOL)isRequestingSalesAssociate3;
-(void)clearRequestSalesAssociate3;



@end


