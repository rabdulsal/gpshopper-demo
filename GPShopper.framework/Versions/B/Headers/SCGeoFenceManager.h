//
//  SCGeoFenceManager.h
//
//  Created by Patrick Caraher on 9/19/13.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>

@class SCGeoFenceManager;

@protocol SCGeoFenceManagerDelegate
@optional
-(void)geoFenceManager:(SCGeoFenceManager *)manager didEnterRegion:(CLRegion *)region;
-(void)geoFenceManager:(SCGeoFenceManager *)manager didExitRegion:(CLRegion *)region;
@end

/**
 
 The SCGeoFenceManager will fetch any GeoFences that have been configured for the current clientType.
 
 Fences are fetched and the application is then configured to monitor up to 20 of these fences.  (This is
 an iOS limit).
 
 When a fence entry is detected, a trigger message will be sent to our server.  Additionally, if a
 SCStoreFenceManagerDelegate has been assigned, it will be notified that the Region was entered.
 
 When a fence exit is detected, if a SCStoreFenceManagerDelegate has been assigned, it will be notified.
 
 Refreshing Fences
 
 There are 4 mechanisms in place to ensure that the fences being monitored remain 'fresh'
 i. timer: By default, the GPSStoreFenceManager creates a 30 minute timer that will refetch
 the fences.  The interval for this timer can be configured via setAutomaticRefetchInterval.
 Setting the automaticRefetchInterval to 0 will disable this timer.
 ii. distance: The current location of the phone is noted when geo fences are fetched.  If the
 phone's location changes by more than the distance to the median fence in the list,
 a refresh is triggered.
 iii. awake:  When the application awakes from the background, a refresh is triggered.
 iv. manual: A geofence refresh can be manually triggered via the refetchFences method.
 */

@interface SCGeoFenceManager : NSObject

/**
 Shared, default instance of the SCGeoFenceManager.
 */
+ (SCGeoFenceManager *)defaultInstance;

/**
 Set the maximum number of GeoFence regions that can be monitored.  Currently, the iOS limit is 20.
 */
+(void)setMaxRegions: (NSInteger)maxRegions;

/**
 *  Configure the SCGeoFenceManager and set the delegate for defaultInstance.
 *
 *  @param delegate SCGeoFenceManagerDelegate
 */
+(void)configureForDelegate:(id <SCGeoFenceManagerDelegate>) delegate;

/**
 Set url string for fetching geofence data and triggering fence entry events.
 */
+(void)setRequestUrl: (NSString *)url;

/**
 Delegate that gets notified of fence events vis the SCGeoFenceManagerDelegate protocol.
 */
@property (nonatomic, retain) id <SCGeoFenceManagerDelegate> delegate;

/**
 Time interval that when it elapses a refresh of the fences will occur.
 
 The default value is 30 minutes.  Setting to 0 will disable the timed refresh.
 */
@property () NSTimeInterval automaticRefetchInterval;

/**
 *  Passed from the Application Delegate method that gets called when a
 *  devToken has been registered with Apple for APNS.  This registers
 *  against the defaultInstance.
 *
 *  @param devToken NSData containing the token.
 */
+ (void)didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)devToken;

/**
 *  Passed from the Application Delegate when we fail to register
 *  with Apple for APNS.
 *
 *  @param err Error Description
 */
+ (void)didFailToRegisterForRemoteNotificationsWithError:(NSError *)err;

/**
 NSSet of identifiers for the regions that are currently being monitored.
 */
-(NSSet *)currentlyInsideRegionIdentifiers;

/**
 Force a refetch of the fences to be monitored.
 */
-(void)refetchFences;

@end
