//
//  Location.h
//  project
//
//  Created by kimberly on 3/2/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#ifndef LOCATION_H
#define LOCATION_H

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import "InfoPacket.h"
#import "SCCache.h"

@class Logger;


//----------------------------------------------------------------
//----------------------------------------------------------------


@class SCGeoLocation;
@class SCLocationDetector;


@protocol SCLocationDetectorDelegate

-(void)scLocationDetectorSucceeded: (SCLocationDetector *)d;
-(void)scLocationDetectorFailed: (SCLocationDetector *)d;

@end


/**
 DEPRECATED.  Use location detection methods of SCGeoLocation instead.
 */
@interface SCLocationDetector : NSObject

@property (retain) SCGeoLocation *geoLocation;
@property (assign) id < SCLocationDetectorDelegate > delegate;

-(void)start;

@end


//----------------------------------------------------------------
//----------------------------------------------------------------


@class SCObjectRetriever;

/**
 Represents a geographical location specified either as latlon or zipcode.
 
 Latlon or zipcode can be set at init time,
 but otherwise location can only be updated by detecting latlon.
 
 Properties latlon, zipcode, name, and detectionStatus support key-value observing
 and should be used to detect changes in the instance's state.
 */
@interface SCGeoLocation : NSObject
{
    CLLocationManager *locationManager;
    SCObjectRetriever *retriever;
}

/**
 Latitude + longitude.  Default value: (0.0, 0.0).
 */
@property (readonly) CLLocationCoordinate2D latlon;

/**
 Zipcode.  Default value: nil.
 
 Note: if latlon are updated, zipcode will be set to nil to prevent confusion.
 */
@property (retain) NSString *zipcode;

/**
 Pretty name of a location.  Default value: nil.
 
 Once a latlon or zipcode is set, it can be fetched using updateName.
 */
@property (readonly) NSString *name;

/**
 Status of location detection.
 */
@property (readonly) enum SCRemoteStatus detectionStatus;

/** @name Init methods */

/**
 Init with an existing zipcode.
 */
-(id)initWithZipcode: (NSString *)z;

/**
 Init with an existing latlon.
 */
-(id)initWithLatlon: (CLLocationCoordinate2D)c;

/**
 Detect the user's current latlon.
 
 This is implemented using CoreLocation and subject to the standard location permissions.
 */
-(void)detectLatLon;

/**
 Look up the pretty name of the current location.
 
 @warning  Currently only supports lookup of zipcodes.
 However, latlon can be implemented if need be.
 */
-(void)updateName;

+(SCGeoLocation *)defaultLocation;

+(void)setRequestUrl: (NSString *)s;
+(NSString *)requestUrl;

+(NSArray *)kvoKeys;

/** @name Deprecated methods */

/**
 @warning  DEPRECATED.  Use property latlon instead.
 */
-(double)lat;

/**
 @warning  DEPRECATED.  Use property latlon instead.
 */
-(double)lon;

/**
 @warning DEPRECATED.  Latlon should be updated either
 (1) at init or (2) by detection.
 */
-(void)setLatitude: (double)l0
         longitude: (double)l1;

/**
 @warning DEPRECATED.  Zipcode should be set at init.
 */
-(void)setZipcode:(NSString *)z;

@end


//----------------------------------------------------------------
//----------------------------------------------------------------


@class SCGeocoder;

@protocol SCGeocoderListener <NSObject>

-(void)cmkGeocoder: (SCGeocoder *)g
  convertedAddress: (NSString *)s
     intoPlacemark: (CLPlacemark *)p;

-(void)cmkGeocoder: (SCGeocoder *)g
failedToConvertAddress: (NSString *)s;

@end


/**
 Wrapper for CLGeocoder that adds caching.

 Queueing should be added as need dictates.
 */
@interface SCGeocoder : NSObject
{
    CLGeocoder *geocoder;
    NSString *addressInProgress;
}

@property (assign) id<SCGeocoderListener> listener;

-(void)lookupAddress: (NSString *)s;

-(void)gotPlacemarks: (NSArray *)ps
               error: (NSError *)e;

+(SCCache *)cache;

@end


//----------------------------------------------------------------
//----------------------------------------------------------------


@interface Location : NSObject
{
	NSString *city;
	NSString *state;
	NSString *zip;
    NSString *displayName;
}

@property (readonly) NSString *city;
@property (readonly) NSString *state;
@property (readonly) NSString *zip;
@property (readonly) NSString *displayName;

-(id)initWithCity: (NSString *)c
			state: (NSString *)s
			  zip: (NSString *)z
      displayName: (NSString *)d;

-(NSComparisonResult)compareNames: (id)element;
-(NSComparisonResult)compareZips: (id)element;
-(NSComparisonResult)compareStates: (id)element;

-(BOOL)cityBeginsWith: (NSString *)s;
-(BOOL)zipBeginsWith: (NSString *)s;

+(Location *)newLocationFromString: (NSString *)s;

@end


//----------------------------------------------------------------
//----------------------------------------------------------------


enum SCLocationListType
{
	SCLocationListTypeZip,
	SCLocationListTypeName,
    SCLocationListTypeState
};


//----------------------------------------------------------------
//----------------------------------------------------------------


@interface SCLocationSearchResult : NSObject
{
	int listType;
	int index;
}

@property (readonly) int listType;
@property (readonly) int index;

-(id)initWithType: (int)t
			index: (int)i;

@end


//----------------------------------------------------------------
//----------------------------------------------------------------


@interface SCLocationListSubstringMatch : NSObject

@property (readonly) NSString *substring;
@property (readonly) NSArray *matchingLocations;

-(id)initWithSubstring: (NSString *)s
     matchingLocations: (NSArray *)ls;

@end


//----------------------------------------------------------------
//----------------------------------------------------------------


@interface SCLocationList : NSObject
{
	NSArray *orderedByZip;
	NSArray *orderedByName;
    NSArray *orderedByState;
}

@property (readonly) NSArray *orderedByZip;
@property (readonly) NSArray *orderedByName;
@property (readonly) NSArray *orderedByState;

-(id)initWithLocations: (NSArray *)ls;

-(void)setContentsFromFile: (NSString *)filename;
-(SCLocationSearchResult *)newSearchResultForString: (NSString *)s;
-(Location *)locationAtSearchResult: (SCLocationSearchResult *)sr;

-(NSArray *)orderedByType: (int)t;

-(SCLocationListSubstringMatch *)newBestMatchForInitialSubstring: (NSString *)s;

+(SCLocationList *)defaultList;

@end


//----------------------------------------------------------------
//----------------------------------------------------------------


@interface LocationManager : NSObject
{}

+(NSString *)latitude;
+(NSString *)longitude;
+(NSString *)zipcode;
+(NSString *)locationName;
+(void)setRequestUrl: (NSString *)url;

+(void)setLocationFromLatitude: (NSString *)lat
					 longitude: (NSString *)lng;

+(void)setLocationFromZipcode: (NSString *)zipcode
				 locationName: (NSString *)ln;

@end

#endif