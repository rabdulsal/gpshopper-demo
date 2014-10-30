//
//  InfoPacket.h
//  project
//
//  Created by kimberly on 7/13/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#ifndef INFOPACKET_H
#define INFOPACKET_H

#import <Foundation/Foundation.h>
#import "SCTestData.h"


enum SCRemoteStatus
{
    SCRemoteStatusNone=0,
    SCRemoteStatusBusy=1,
    SCRemoteStatusSuccess=2,
    SCRemoteStatusFail=3
};


enum SCRetrievalSource
{
    SCRetrievalSourceCache=(1<<0),
    SCRetrievalSourceRemote=(1<<1),
    SCRetrievalSourceMock=(1<<2)
};


@class SCRequestBodyConstructor;
@class SCRequestConstructor;
@class SCRemoteRequester;
@class SCRemoteResponseParser;

@class SCObjectRetriever;

@protocol SCObjectRetrieverListener

-(void)scObjectRetriever: (SCObjectRetriever *)retriever
		 retrievedObject: (NSObject *)obj
				response: (NSURLResponse *)response
				   error: (NSError *)error
        forRequestObject: (NSObject *)requestObj;

@end


@interface SCObjectRetriever : NSObject
{
	SCRequestBodyConstructor *requestBodyConstructor;
	SCRequestConstructor *requestConstructor;
	SCRemoteRequester *requester;
	SCRemoteResponseParser *responseParser;
    NSMutableArray *requestObjectQueue;
    NSMutableData *responseData;
    NSObject *currentRequestObject;
    NSURLResponse *currentResponse;
    BOOL busy;
	id<SCObjectRetrieverListener> listener;
}

@property (readonly) SCRequestConstructor *requestConstructor;
@property (retain) SCMockJsonData *mockData;
@property (assign) id<SCObjectRetrieverListener> listener;

-(id)initWithBodyConstructor: (SCRequestBodyConstructor *)bc
		  requestConstructor: (SCRequestConstructor *)rc
			 remoteRequester: (SCRemoteRequester *)rr
			  responseParser: (SCRemoteResponseParser *)rp;
// initializer with all four, plus notification name?
// static factory functions in relevant classes?

-(NSString *)notificationName;
-(void)retrieveObjectWithObject: (NSObject *)obj;

@end

//-----------------------------------------------------------------
//-----------------------------------------------------------------


@interface SCRequestBodyConstructor : NSObject
{}

-(NSString *)newBodyWithData: (NSData *)data;
-(NSString *)newBodyWithObject: (NSObject *)obj;

@end


//-----------------------------------------------------------------
//-----------------------------------------------------------------


@interface SCJsonDictionaryRequestBodyConstructor : SCRequestBodyConstructor
{
    NSString *requestType;
}

@property (copy) NSString *requestType;

@end


//-----------------------------------------------------------------
//-----------------------------------------------------------------


@interface SCRequestConstructor : NSObject
{}

-(NSURLRequest *)newRequestWithBody: (NSString *)body;

@end


//-----------------------------------------------------------------
//-----------------------------------------------------------------


@interface SCRemoteResponseParser : NSObject
{}

-(NSObject *)newResponseObjectWithData: (NSData *)data;

@end

//-----------------------------------------------------------------
//-----------------------------------------------------------------


@interface SCJsonDictionaryResponseParser : SCRemoteResponseParser
{}

@end


//-----------------------------------------------------------------
//-----------------------------------------------------------------


@interface SCConfigurableRequestConstructor : SCRequestConstructor
{
	NSString *url;
	NSString *httpMethod;
	NSMutableDictionary *headers;
}

@property (nonatomic, copy) NSString *url;
@property (nonatomic, copy) NSString *httpMethod;
@property (nonatomic, assign) NSTimeInterval timeout;
@property (nonatomic, assign) NSURLRequestCachePolicy cachePolicy;

-(void)addHeaderValue: (NSString *)v
			   forKey: (NSString *)k;

-(void)clearHeaders;

+(void)setDefaultUrl: (NSString *)u;
+(NSString *)defaultUrl;
+(void)setDefaultTimeoutInterval:(NSTimeInterval)timeout;
+(NSTimeInterval)defaultTimeout;

@end

//-----------------------------------------------------------------
//-----------------------------------------------------------------


@interface SCRemoteRequester : NSObject
{}

-(NSData *)sendRequest: (NSURLRequest *)request
	 returningResponse: (NSURLResponse **)response
				 error: (NSError **)error;

@end


//-----------------------------------------------------------------
//-----------------------------------------------------------------


@interface SCSynchronousRemoteRequester : SCRemoteRequester
{}

@end


//-----------------------------------------------------------------
//-----------------------------------------------------------------


@interface SCJsonResponseUnpacker : NSObject
{}

-(NSDictionary *)firstDictFromData: (NSData *)data;

@end


//-----------------------------------------------------------------
//-----------------------------------------------------------------


@interface JsonTestRequestHandler : NSObject
{}

-(NSString *)newResponseStringForRequest: (NSDictionary *)request
									info: (NSDictionary *)info;

@end


//-----------------------------------------------------------------
//-----------------------------------------------------------------


@interface JsonTestRequester : SCRemoteRequester
{
	NSMutableDictionary *handlers;
}

-(void)setHandler: (JsonTestRequestHandler *)handler
  forRequestNamed: (NSString *)request_name;

@end


//-----------------------------------------------------------------
//-----------------------------------------------------------------


@interface SCJsonObjectRetriever : NSObject

+(SCObjectRetriever *)newJsonObjectRetrieverWithUrl: (NSString *)u
                                        requestType: (NSString *)s;

@end


//-----------------------------------------------------------------
//-----------------------------------------------------------------


@interface InfoPacket : NSObject
{
}

+(void)setRemoteRequester: (SCRemoteRequester *)rr;

+(void)setLatitude: (NSString *)l;
+(NSString *)latitude;
+(void)setLongitude: (NSString *)l;
+(NSString *)longitude;
+(void)setClientTypeID: (uint64_t)cid;
+(uint64_t)clientTypeID;
+(void)setPlatformID: (uint64_t)pid;
+(uint64_t)platformID;
+(void)setValue: (NSString *)value
		 forKey: (NSString *)key;
+(NSString *)uniqueIdentifier;

+(NSDictionary *)newDictionaryForReleaseid: (uint64_t)releaseid;
+(NSString *)newJsonRequestBodyForPacket: (NSDictionary *)packet;
+(NSArray *)responsePacketsFromJsonData: (NSData *)data;
+(NSURLRequest *)newRequestWithBody: (NSString *)body
								url: (NSString *)url;
+(NSData *)synchronousRequestWithBody: (NSString *)body
								  url: (NSString *)url;
+(NSData *)synchronousRequestWithBody: (NSString *)body
							errorInfo: (NSDictionary *)errorInfo
								  url: (NSString *)url;

+(void)setDefaultUrl: (NSString *)u;
+(NSString *)defaultUrl;

@end

#endif
