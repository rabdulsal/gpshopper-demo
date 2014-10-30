//
//  SCRegistration.h
//  EXPproject
//
//  Created by kimberly on 11/12/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "InfoPacket.h"


enum SCRegStatus
{
    SCRegStatusUnregistered,
    SCRegStatusBusy,
    SCRegStatusSuccess,
    SCRegStatusFail
};

@interface SCRegistrationState : NSObject
{
	uint64_t userid;
	uint64_t pw;
	NSMutableString *archivePath;
    SCObjectRetriever *retriever;
}

@property (readwrite, nonatomic) uint64_t userid;
@property (readwrite, nonatomic) uint64_t pw;
@property (readonly) NSString *phone;
@property (readonly) NSString *zipcode;
@property (readonly) enum SCRegStatus status;

-(void)tieToArchiveFileAtPath: (NSString *)path;
-(void)clear;

-(void)loginWithIdentifier: (NSString *)i
                   zipcode: (NSString *)z;

+(SCRegistrationState *)defaultState;

@end


//------------------------------------------------------------------
//------------------------------------------------------------------


@class SCRegistrationFetcher;

@protocol SCRegistrationFetcherListener

-(void)scRegistrationFetchSucceeded: (SCRegistrationFetcher *)f;
-(void)scRegistrationFetchFailed: (SCRegistrationFetcher *)f;

@end


/**
 @warning DEPRECATED.  Use SCRegistrationState instead.
 */
@interface SCRegistrationFetcher : NSObject
{
    SCRegistrationState *state;
    SCObjectRetriever *retriever;
    id<SCRegistrationFetcherListener> listener;
}

@property (retain) SCRegistrationState *state;
@property (assign) id<SCRegistrationFetcherListener> listener;

-(void)fetchRegistrationForPhoneNumber: (NSString *)p
                               zipcode: (NSString *)z;

@end

