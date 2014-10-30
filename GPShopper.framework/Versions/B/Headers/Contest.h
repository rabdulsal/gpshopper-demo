//
//  Contest.h
//  project
//
//  Created by kimberly on 7/13/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "InfoPacket.h"

extern NSString* const kSCContestKeyContestid;
extern NSString* const kSCContestKeyName;
extern NSString* const kSCContestKeyDescription;
extern NSString* const kSCContestKeyEndDate;
extern NSString* const kSCContestKeyAcceptMessage;
extern NSString* const kSCContestKeyTermsUrl;
extern NSString* const kSCContestKeyImageHash;
extern NSString* const kSCContestKeyContestType;
extern NSString* const kSCContestKeySupplemental;

extern NSString* const kSCContestEntryKeyDateEntered;
extern NSString* const kSCContestEntryKeyOutcomeName;
extern NSString* const kSCContestEntryDateFormat;

extern NSString* const kSCHistoricalContestKeyPriorEntries;
extern NSString* const kSCHistoricalContestKeyContests;

extern NSString* const kSCContestErrorDomain;
extern NSInteger const kSCContestErrorCodeParseFailed;


//-----------------------------------------------------------------
//-----------------------------------------------------------------


enum SCContestEligibility
{
    SCContestEligibilityUnknown,
    SCContestEligibilityTrue,
    SCContestEligibilityFalse
};


//-----------------------------------------------------------------
//-----------------------------------------------------------------


@interface SCContest : NSObject
{
    uint64_t contestid;
	NSString *name;
	NSString *desc;
	NSString *endDate;
	NSString *acceptMessage;
	NSString *termsUrl;
	NSString *imageHash;
    NSString *imageUrl;
    NSString *contestType;
    NSDictionary *supplemental;
}

@property (readonly) uint64_t contestid;
@property (readonly) NSString *name;
@property (readonly) NSString *desc;
@property (readonly) NSString *endDate;
@property (readonly) NSString *acceptMessage;
@property (readonly) NSString *termsUrl;
@property (readonly) NSString *imageUrl;
@property (readonly) NSString *contestType;
@property (readonly) NSDictionary *supplemental;

-(id)initWithContestid: (uint64_t)cid
                  name: (NSString *)n
           description: (NSString *)d
               endDate: (NSString *)e
         acceptMessage: (NSString *)a
              termsUrl: (NSString *)t
              imageUrl: (NSString *)i
           contestType: (NSString *)c
          supplemental: (NSDictionary *)s;

-(NSString *)imageHash;

@end


@interface SCContestEntry : NSObject

@property (readonly) NSDate *dateEntered;
@property (readonly) NSString *outcomeName;

-(id)initWithOutcomeName: (NSString *)on
             dateEntered: (NSDate *)de;

+(SCContestEntry *)newFromDictionary: (NSDictionary *)kv;

@end


@interface SCHistoricalContest : SCContest

@property (readonly) NSArray *priorEntries;

-(id)initWithContestid: (uint64_t)cid
                  name: (NSString *)n
           description: (NSString *)d
               endDate: (NSString *)e
         acceptMessage: (NSString *)a
              termsUrl: (NSString *)t
              imageUrl: (NSString *)i
           contestType: (NSString *)c
          supplemental: (NSDictionary *)s
          priorEntries: (NSArray *)es;

+(SCHistoricalContest *)newFromDictionary: (NSDictionary *)kv;

@end


//-----------------------------------------------------------------
//-----------------------------------------------------------------


@class SCContestFetcher;

@protocol SCContestFetcherListener

-(void)scContestFetcher: (SCContestFetcher *)fetcher
		 fetchedContest: (SCContest *)c
				  forId: (uint64_t)cid;

-(void)scContestFetcher: (SCContestFetcher *)fetcher
failedToFetchContestForId: (uint64_t)cid;

@end


@interface SCContestFetcher : NSObject
{
	SCObjectRetriever *retriever;
	id<SCContestFetcherListener> listener;
}

@property (assign) id<SCContestFetcherListener> listener;

-(void)fetchContestForId: (uint64_t)cid;
+(void)setRequestUrl: (NSString *)url;

@end


//-----------------------------------------------------------------
//-----------------------------------------------------------------


@class SCContestEligibilityFetcher;

@protocol SCContestEligibilityFetcherListener

-(void)scContestEligibilityFetcher: (SCContestEligibilityFetcher *)fetcher
				fetchedEligibility: (BOOL)e
							 forId: (uint64_t)cid;

@end

@interface SCContestEligibilityFetcher : NSObject
{
	SCObjectRetriever *retriever;
	id<SCContestEligibilityFetcherListener> listener;
}

@property (assign) id<SCContestEligibilityFetcherListener> listener;

-(void)fetchEligibilityForId: (uint64_t)cid;
+(void)setRequestUrl: (NSString *)url;

@end


//-----------------------------------------------------------------
//-----------------------------------------------------------------


@interface ContestManager : NSObject
{
}

+(void)setRequestUrl: (NSString *)url;

+(BOOL)enterContest: (uint64_t)contestid
			   wait: (BOOL)wait;

@end


@class SCContestEntryFetcher;

@protocol SCContestEntryFetcherListener < NSObject >

-(void)scContestEntryFetcher: (SCContestEntryFetcher *)f
              enteredContest: (uint64_t)c
                     outcome: (NSDictionary *)kv;

-(void)scContestEntryFetcher: (SCContestEntryFetcher *)f
        failedToEnterContest: (uint64_t)c;

@optional

// DEPRECATED
-(void)scContestEntryFetcher: (SCContestEntryFetcher *)f
              enteredContest: (uint64_t)c
              outcomeMessage: (NSString *)s;

@end

@interface SCContestEntryFetcher : NSObject
{
    SCObjectRetriever *retriever;
    id<SCContestEntryFetcherListener> listener;
}

@property (assign) id<SCContestEntryFetcherListener> listener;

-(void)submitEntryForContest: (uint64_t)c;

+(void)setMockData: (SCMockJsonData *)md;

+(void)addGlobalListener: (id<SCContestEntryFetcherListener>)l;
+(void)removeGlobalListener: (id<SCContestEntryFetcherListener>)l;

@end


@class SCContestHistoryFetcher;

@protocol SCContestHistoryFetcherListener < NSObject >

@optional
-(void)scContestHistoryFetcher: (SCContestHistoryFetcher *)f
     fetchedHistoricalContests: (NSArray *)cs;

-(void)scContestHistoryFetcher: (SCContestHistoryFetcher *)f
               failedWithError: (NSError *)e;

@end


@interface SCContestHistoryFetcher : NSObject
{
    SCObjectRetriever *retriever;
    id<SCContestHistoryFetcherListener> listener;
}

@property (assign) id<SCContestHistoryFetcherListener> listener;

-(void)fetchHistory;

-(NSArray *)newHistoricalContestsFromDictionary: (NSDictionary *)kv;
-(SCHistoricalContest *)newHistoricalContestFromDictionary: (NSDictionary *)kv;

+(void)setMockData: (SCMockJsonData *)md;

@end

//-----------------------------------------------------------------
//-----------------------------------------------------------------


@interface SCContestBodyConstructor : SCRequestBodyConstructor
{}
@end


@interface SCContestResponseParser : SCRemoteResponseParser
{}
@end


@interface SCContestFakeSuccessResponseParser : SCRemoteResponseParser
{}
@end


@interface SCContestEligibilityBodyConstructor : SCRequestBodyConstructor
{}
@end


@interface SCContestEligibilityResponseParser : SCRemoteResponseParser
{}
@end


@interface SCContestEligibilityFakeResponseParser : SCRemoteResponseParser
{
	int code;
}

@property (readwrite) int code;

@end