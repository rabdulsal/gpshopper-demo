//
//  SCNotificationInbox.h
//  feature
//
//  Created by kkd on 8/8/14.
//  Copyright (c) 2014 GPShopper. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "InfoPacket.h"

extern NSString* const kSCNotificationInboxErrorDomain;

extern NSInteger const kSCNotificationInboxErrorCodeParseFailed;
extern NSInteger const kSCNotificationInboxErrorCodeErrorReturned;

@interface SCNotificationInboxFetcher : NSObject
{
    SCObjectRetriever *retriever;
    NSMutableDictionary *handlersForRequest;
}

-(void)setMockData: (SCMockJsonData *)md;
-(SCMockJsonData *)mockData;

-(void)fetchInboxWithCompletionHandler: (void (^)(NSArray *notifications, NSError *error))h;

// Override point if we ever need to subclass (hopefully not).
-(NSDictionary *)newRequestDictionary;

// Override point if we ever need to subclass (hopefully not).
-(NSArray *)newNotificationsFromResponseDictionary: (NSDictionary *)kv;

// Override point if we ever need to subclass (hopefully not).
-(NSError *)newErrorFromResponseDictionary: (NSDictionary *)kv;

@end
