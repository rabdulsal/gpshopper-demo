//
//  GPSSDKStoreLocator.h
//  GPShopper
//
//  Created by PJ Caraher on 3/10/14.
//  Copyright (c) 2014 GPShopper. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SearchResult.h"

#define kGPSSDKStoreLocationFetchedNotification @"GPSSDKStoreLocationFetchedNotification"

@interface GPSSDKStoreLocator : NSObject

/**
 Shared, default instance of the GPSSDKStoreLocator.
 */
+ (GPSSDKStoreLocator *)defaultInstance;

/**
 *  Set a message to appear when we are unable to detect the current location.
 *  If this message value is set, a UIAlert, displaying this message, will appear
 *  when we fail to detect the current location.
 *
 *  @param message NSString
 */
-(void)setLocationDetectionFailureMessage:(NSString *)message;

/**
 *  Override the default SCSearchConstraint to the specified value.
 *  The default SCSearchConstraint set to 50 kilometers.
 *
 *  @param c SCSearchConstraint
 */
-(void)setSearchConstraint:(SCSearchConstraint *)c;

/**
 *  Fetch the stores for the given ZipCode.  Notification is posted when
 *  search completes.
 *
 *  @param zipCode NSString
 */
-(void)fetchForZipCode:(NSString *)zipCode;

/**
 *  Fetch the stores for the current location.  Notification is posted when
 *  search completes.  Or, if the current location can not be detected, an
 *  error message is displayed if locationDetectionFailureMessage has been set.
 */
-(void)fetchForCurrentLocation;

/**
 *  Fetch the stores for the specified coordinates
 *  Coordinates must be valid (ie. CLLocationCoordinate2DIsValid()) else, does nothing.
 */
- (void)fetchForCoordinates:(CLLocationCoordinate2D)coordinates;

/**
 *  BOOL indicating if a search is currently in progress.
 */
-(BOOL)searchInProgress;

/**
 *  The current list of stores that have been fetched by the GPSSDKStoreLocator.
 *  Note that if a search is in progess, an empty NSArray is returned.
 *
 *  @return NSArray of StoreData objects.
 */
-(NSArray *)stores;

@end
