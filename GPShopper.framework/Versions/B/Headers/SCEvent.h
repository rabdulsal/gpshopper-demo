//
//  SCEvent.h
//  lunds
//
//  Created by kimberly on 8/29/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "InfoPacket.h"
#import "SCCache.h"
#import "SCMacros.h"


@protocol SCBaseLocation < NSObject >

-(uint64_t)storeid;
-(NSString *)locName;
-(NSString *)locSubname;
-(NSString *)locAddr;
-(NSString *)locCity;
-(NSString *)locState;
-(NSString *)locZipcode;
-(NSString *)locPhoneNumber;
-(double)locLatitude;
-(double)locLongitude;
-(double)distance;

@end


#define SCBASELOCATION_FORWARD_IMPL(var) \
FORWARD_SELECTOR(var, storeid, uint64_t, 0) \
FORWARD_SELECTOR(var, locName, NSString*, nil) \
FORWARD_SELECTOR(var, locSubname, NSString*, nil) \
FORWARD_SELECTOR(var, locAddr, NSString*, nil) \
FORWARD_SELECTOR(var, locCity, NSString*, nil) \
FORWARD_SELECTOR(var, locState, NSString*, nil) \
FORWARD_SELECTOR(var, locZipcode, NSString*, nil) \
FORWARD_SELECTOR(var, locPhoneNumber, NSString*, nil) \
FORWARD_SELECTOR(var, locLatitude, double, -1.0) \
FORWARD_SELECTOR(var, locLongitude, double, -1.0) \
FORWARD_SELECTOR(var, distance, double, 0.0)


@interface SCBaseLocation : NSObject < SCBaseLocation >

@property (readonly) uint64_t storeid;
@property (readonly) NSString *locName;
@property (readonly) NSString *locSubname;
@property (readonly) NSString *locAddr;
@property (readonly) NSString *locCity;
@property (readonly) NSString *locState;
@property (readonly) NSString *locZipcode;
@property (readonly) NSString *locPhoneNumber;
@property (readonly) double locLatitude;
@property (readonly) double locLongitude;
@property (readonly) double distance;

-(id)initWithStoreid: (uint64_t)sid
             locName: (NSString *)n
          locSubname: (NSString *)s
             locAddr: (NSString *)a
             locCity: (NSString *)c
            locState: (NSString *)s
          locZipcode: (NSString *)z
      locPhoneNumber: (NSString *)p
         locLatitude: (double)lat
        locLongitude: (double)lon
            distance: (double)d;

-(id)initWithStoreid: (uint64_t)sid
             locName: (NSString *)n
             locAddr: (NSString *)a
             locCity: (NSString *)c
            locState: (NSString *)s
      locPhoneNumber: (NSString *)p
         locLatitude: (double)lat
        locLongitude: (double)lon
            distance: (double)d __attribute__((deprecated));

+(SCBaseLocation *)newFromDictionary: (NSDictionary *)d;

@end


@interface SCEventInstance : NSObject < SCBaseLocation >
{
    SCBaseLocation *location;
}

@property (readonly) NSDate *startDate;
@property (readonly) NSDate *stopDate;

-(id)initWithLocation: (SCBaseLocation *)l
            startDate: (NSDate *)d0
             stopDate: (NSDate *)d1;

-(NSComparisonResult)startsBefore: (SCEventInstance *)i;

+(SCEventInstance *)newFromDictionary: (NSDictionary *)d;

+(NSDateFormatter *)isoDateFormatter;

@end



@interface SCEvent : NSObject < SCBaseLocation >

@property (readonly) NSString *eventName;
@property (readonly) NSString *imageUrl;
@property (readonly) NSString *shortDescription;
@property (readonly) NSString *longDescription;
@property (readonly) NSArray *instances;
@property (readonly) NSDictionary *supplemental;

-(id)initWithName: (NSString *)n
         imageUrl: (NSString *)u
 shortDescription: (NSString *)sd
  longDescription: (NSString *)ld
        instances: (NSArray *)is __attribute__ ((deprecated));

-(id)initWithName: (NSString *)n
         imageUrl: (NSString *)u
 shortDescription: (NSString *)sd
  longDescription: (NSString *)ld
        instances: (NSArray *)is
     supplemental: (NSDictionary *)sup;

-(NSComparisonResult)startsBefore: (SCEvent *)e;

-(NSArray *)uniqueInstanceValuesForKey: (NSString *)k;

+(SCEvent *)newFromDictionary: (NSDictionary *)d;

@end

/**
 Specifies constraints of an event search.
 */
@interface SCEventSearchSpecs : NSObject

/**
 Text query to be matched against event name and description.  May be nil.
 */
@property (readonly) NSString *query;

/**
 Constrains search to events with at least one instance
 at or after a given date.  May be nil.
 */
@property (readonly) NSDate *minDate;

/**
 Constrains search to events with at least one instance
 at or before a given date.  May be nil.
 */
@property (readonly) NSDate *maxDate;

/**
 Latitude of search center.  See also longitude.
 To specify no location, use -1.0.
 */
@property (readonly) double latitude;

/**
 Longitude of search center.  See also latitude.
 To specify no location, use -1.0.
 */
@property (readonly) double longitude;

/**
 Specifies a single event id to be looked up.
 To specify not event id, use 0.
 */
@property (readonly) uint64_t eventid;

/**
 Constructor.
 */
-(id)initWithQuery: (NSString *)q
           minDate: (NSDate *)dmin
           maxDate: (NSDate *)dmax
          latitude: (double)lat
         longitude: (double)lon
           eventid: (uint64_t)eid;

-(NSDictionary *)newDictionary;
+(SCEventSearchSpecs *)newFromDictionary: (NSDictionary *)d;

@end


@class SCEventsFetcher;

@protocol SCEventsFetcherListener <NSObject>

-(void)scEventsFetcher: (SCEventsFetcher *)f
         fetchedEvents: (NSArray *)es
              forSpecs: (SCEventSearchSpecs *)s;

-(void)scEventsFetcher: (SCEventsFetcher *)f
fetchedNoEventsForSpecs: (SCEventSearchSpecs *)s;

@end

@interface SCEventsFetcher : NSObject
{
    SCObjectRetriever *retriever;
}

@property (assign) id< SCEventsFetcherListener > listener;

-(void)fetchEventsWithSpecs: (SCEventSearchSpecs *)s;

+(SCCache *)cache;

+(NSString *)requestUrl;
+(void)setRequestUrl: (NSString *)s;

+(SCMockJsonData *)mockData;
+(void)setMockData: (SCMockJsonData *)d;

@end
