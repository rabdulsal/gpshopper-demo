//
//  SCAuthenticate.h
//  EXPproject
//
//  Created by kimberly on 11/10/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "InfoPacket.h"


//------------------------------------------------------------------
//------------------------------------------------------------------


@interface SCAuthId : NSObject
{
	uint64_t userid;
	uint64_t password;
}

@property (readonly) uint64_t userid;
@property (readonly) uint64_t password;

-(id)initWithUserid: (uint64_t)u
		   password: (uint64_t)p;

@end

//------------------------------------------------------------------
//------------------------------------------------------------------


// notification: scsessionstatus_updated
@interface SCSessionStatus : NSObject
{
	BOOL authenticated;
}

@property (readonly) BOOL authenticated;

+(SCSessionStatus *)defaultStatus;

@end


//------------------------------------------------------------------
//------------------------------------------------------------------


@class SCRegistrationState;
@class SCLoginFetcher;
@class SCLogoutFetcher;

// notification: scsession_updated
@interface SCSession : NSObject
{
    SCLoginFetcher *loginFetcher;
    SCLogoutFetcher *logoutFetcher;
    SCRegistrationState *regState;
    NSDictionary *details;
    NSDictionary *headers;
    BOOL exists;
    BOOL createFailed;
    BOOL destroyFailed;
}

@property (readonly) NSDictionary *details;
@property (readonly) NSDictionary *headers;
@property (readonly) BOOL exists;
@property (readonly) BOOL createFailed;
@property (readonly) BOOL destroyFailed;
@property (readonly) SCRegistrationState *regState;

-(id)initWithRegState: (SCRegistrationState *)s;

-(void)create;
-(void)destroy;

-(void)writeToFile;
-(void)readFromFile;

-(NSString *)jsessionid;

+(SCSession *)defaultSession;

+(void)setRequestUrl: (NSString *)s;
+(NSString *)requestUrl;

+(void)setCookieDomains: (NSArray *)ds;
+(NSArray *)cookieDomains;

+(void)deleteCookies;

@end


//------------------------------------------------------------------
//------------------------------------------------------------------


@interface SCProfileDataSupplementalFactory : NSObject

-(NSObject *)newSupplementalObject: (NSDictionary *)attrs;

@end

@interface SCProfileData : NSObject < NSCopying >
{
	NSString *firstName;
	NSString *lastName;
	NSString *email;
	NSMutableDictionary *supplemental;
    NSObject *supplementalObject;
}

@property (copy) NSString *firstName;
@property (copy) NSString *lastName;
@property (copy) NSString *email;
@property (readonly) NSMutableDictionary *supplemental;
@property (readonly) NSObject *supplementalObject;

-(void)clear;

+(SCProfileData *)currentValue;
+(void)setCurrentValue: (SCProfileData *)pd;

+(void)setSupplementalFactory: (SCProfileDataSupplementalFactory *)f;

@end


//------------------------------------------------------------------
//------------------------------------------------------------------


@interface SCAuthUpdateSpecs : NSObject
{
	SCAuthId *authId;
	SCProfileData *profileData;
}

-(id)initWithAuthId: (SCAuthId *)ai
		profileData: (SCProfileData *)pd;

@property (readonly) SCAuthId *authId;
@property (readonly) SCProfileData *profileData;

@end


//------------------------------------------------------------------
//------------------------------------------------------------------


@interface SCAuthResult : NSObject
{
	SCProfileData *profileData;
	NSArray *shoppingListItems;
	NSDictionary *attrs;
}

@property (retain) SCProfileData *profileData;
@property (retain) NSArray *shoppingListItems;
@property (retain) NSDictionary *attrs;

@end


//------------------------------------------------------------------
//------------------------------------------------------------------


@class SCShoppingList;
@class SCAuthFetcher;

@protocol SCAuthFetcherDelegate

-(void)scAuthFetcher: (SCAuthFetcher *)fetcher
fetchedShoppingListItems: (NSArray *)items;

-(void)scAuthFetcher: (SCAuthFetcher *)fetcher
  fetchedProfileData: (SCProfileData *)profileData;

-(void)scAuthFetcher: (SCAuthFetcher *)fetcher
		fetchedAttrs: (NSDictionary *)attrs;

-(BOOL)respondsToSelector: (SEL)s;

@end


@interface SCAuthFetcher : NSObject
{
	SCObjectRetriever *emptyRetriever;
	SCObjectRetriever *updateRetriever;
	id<SCAuthFetcherDelegate> delegate;
}

@property (assign) id<SCAuthFetcherDelegate> delegate;

-(void)fetchUpdatedAuthForId: (SCAuthId *)ai;
-(void)fetchUpdatedAuthForId: (SCAuthId *)ai
				 profileData: (SCProfileData *)profileData;

+(void)setRequestUrl: (NSString *)url;

@end


//------------------------------------------------------------------
//------------------------------------------------------------------


@class SCLogoutFetcher;

@protocol SCLogoutFetcherListener

-(void)scLogoutFetcherLoggedOut: (SCLogoutFetcher *)fetcher;
-(void)scLogoutFetcherLogoutFailed: (SCLogoutFetcher *)fetcher;

@end


@interface SCLogoutFetcher : NSObject
{
	SCObjectRetriever *retriever;
	id<SCLogoutFetcherListener> listener;
}

@property (assign) id<SCLogoutFetcherListener> listener;

-(void)fetch;

+(void)setRequestUrl: (NSString *)url;

@end


//------------------------------------------------------------------
//------------------------------------------------------------------


@class SCLoginFetcher;

@protocol SCLoginFetcherListener

-(void)scLoginFetcherLoggedIn: (SCLoginFetcher *)f
                      details: (NSDictionary *)d
                      headers: (NSDictionary *)h;
-(void)scLoginFetcherLoginFailed: (SCLoginFetcher *)f;

@end

@interface SCLoginFetcher : NSObject
{
    SCObjectRetriever *retriever;
    id<SCLoginFetcherListener> listener;
}

@property (assign) id<SCLoginFetcherListener> listener;

-(id)initWithRequestUrl: (NSString *)s;

-(void)fetchSessionForUserid: (uint64_t)n
                     headers: (NSDictionary *)kv;

@end


//------------------------------------------------------------------
//------------------------------------------------------------------


@interface SCAuthEmptyBodyConstructor : SCRequestBodyConstructor
{}

@end


//------------------------------------------------------------------
//------------------------------------------------------------------


@interface SCAuthUpdateBodyConstructor : SCRequestBodyConstructor
{}

@end


//------------------------------------------------------------------
//------------------------------------------------------------------


@interface SCAuthResponseParser : SCRemoteResponseParser
{}

@end
