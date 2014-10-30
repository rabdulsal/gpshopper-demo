//
//  SCPerk.h
//  EXPproject
//
//  Created by kimberly on 11/8/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "InfoPacket.h"


//------------------------------------------------------------------
//------------------------------------------------------------------


@interface SCPerkId : NSObject
{}

@end


//------------------------------------------------------------------
//------------------------------------------------------------------


@interface SCPerk : NSObject
{
	NSString *code;
	NSString *endDate;
	BOOL valid;
    NSString *barcodeUrl;
}

-(id)initWithCode: (NSString *)c
		  endDate: (NSString *)ed
			valid: (BOOL)v
       barcodeUrl: (NSString *)b;

-(id)initWithCode: (NSString *)c
		  endDate: (NSString *)ed
			valid: (BOOL)v
       barcodeUrl: (NSString *)b
         passData: (NSData*) pData;

@property (readonly) NSString *code;
@property (readonly) NSString *endDate;
@property (readonly) BOOL valid;
@property (readonly) NSString *barcodeUrl;
@property (readonly) NSData *passData;
@end


//------------------------------------------------------------------
//------------------------------------------------------------------

@class SCPerkFetcher;

@protocol SCPerkFetcherDelegate

-(void)scPerkFetcher: (SCPerkFetcher *)fetcher
		 fetchedPerk: (SCPerk *)perk
			forGrpid: (uint64_t)grpid;

@end

@interface SCPerkFetcher : NSObject
{
	SCObjectRetriever *retriever;
	id<SCPerkFetcherDelegate> delegate;
}

@property (assign) id<SCPerkFetcherDelegate> delegate;

-(void)requestPerkForGrpid: (uint64_t)grpid
                      piid: (uint64_t)piid;

+(void)setRequestUrl: (NSString *)s;

@end


//------------------------------------------------------------------
//------------------------------------------------------------------


@interface SCPerks : NSObject
{}

+(SCObjectRetriever *)newPerkRetriever;

@end


//------------------------------------------------------------------
//------------------------------------------------------------------


@interface SCPerkRequest : NSObject
{
    uint64_t grpid;
    uint64_t piid;
}

-(id)initWithGrpid: (uint64_t)g
              piid: (uint64_t)p;

@property (readwrite) uint64_t grpid;
@property (readonly) uint64_t piid;

@end


//------------------------------------------------------------------
//------------------------------------------------------------------


@interface SCPerkRequestBodyConstructor : SCRequestBodyConstructor
{}

@end


//------------------------------------------------------------------
//------------------------------------------------------------------


@interface SCPerkResponseParser : SCRemoteResponseParser
{}

@end

@interface SCPerkFakeSuccessResponseParser : SCRemoteResponseParser
{}
@end

@interface SCPerkFakeFailureResponseParser : SCRemoteResponseParser
{}
@end

//------------------------------------------------------------------
//------------------------------------------------------------------


@interface SCPerkRetriever : SCObjectRetriever
{
}

@end
