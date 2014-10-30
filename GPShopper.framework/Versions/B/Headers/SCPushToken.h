//
//  SCPushToken.h
//  bestbuy
//
//  Created by kimberly on 2/7/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "InfoPacket.h"
@class SCPushToken;


@protocol SCPushTokenListener

-(void)scPushTokenFetchSucceeded:(SCPushToken *)pt;
-(void)scPushTokenFetchFailed;

@end


@interface SCPushToken : NSObject

@property (nonatomic, retain) NSString *strDevToken;

+(SCPushToken *)defaultPushToken;
+(void)request;
-(void)populateWithData: (NSData *)d;

-(void)requestPushTokenFrom: (NSObject<SCPushTokenListener> *)l;
-(void)setPushToken: (NSData *)devToken;

@end



#define scDeviceProfilePushTokenKey @"ios_push_token"

/**
 Stores and updates data related to a particular device
 using a particular app.
 
 This profile is synched with a remote database
 using methods fetch, stageSupplementalValue:forKey:, and sendUpdates.
 
 The status of these remote connections is indicated
 by fetchStatus and updateStatus.
 
 ### See also ###
 
 * SCProfile
 */
@interface SCDeviceProfile : NSObject
{
    NSMutableDictionary *stagedSupplementalUpdates;
    
    SCObjectRetriever *fetchRetriever;
    SCObjectRetriever *saveRetriever;

    BOOL fetched;
    BOOL fetchFailed;
    BOOL updateFailed;
}

/**
 Arbitrary key-value pairs related to this device.  Supports key-value observing.
 */
@property (readonly) NSDictionary *supplemental;

/**
 Status of the fetch half of remote synch (pulling data from database).
 Supports key-value observing.
 */
@property (readonly) enum SCRemoteStatus fetchStatus;

/**
 Status of the update half of remote synch (pushing data to database).
 Supports key-value observing.
 */
@property (readonly) enum SCRemoteStatus updateStatus;

+(SCDeviceProfile *)defaultDeviceProfile;
+(void)setRequestUrl: (NSString *)s;

+(void)setMockData: (SCMockJsonData *)d;
+(SCMockJsonData *)mockData;

-(void)sendRemoteDeviceProfile:(NSString *)pushToken;

/**
 Pull profile data from remote database.
 Concurrent fetches will be discarded.
 */
-(void)fetch;

/**
 Adds key-value pair to a local list of updates.
 The staged data is not visible in supplemental until the next sendUpdates call.
 */
-(void)stageSupplementalValue: (NSString *)v
                       forKey: (NSString *)k;

/**
 Transmits all staged updates to database.
 All staged updates will *immediately* be copied to supplemental.
 */
-(void)sendUpdates;

@end

