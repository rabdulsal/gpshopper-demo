//
//  TrackingEvent.h
//  Slifter_iphone_rewrite
//
//  Created by kimberly on 1/11/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#ifndef TRACKINGEVENT_H
#define TRACKINGEVENT_H

#import <Foundation/Foundation.h>
#import "InfoPacket.h"

extern const int TRACK_EVENT_TYPE_CLICK;
extern const int TRACK_EVENT_TYPE_IMPRESSION;
extern const int TRACK_EVENT_BANNER;


@interface SCTrackingEventSender : NSObject
{
    SCObjectRetriever *retriever;
}

-(void)sendEventWithDictionary: (NSDictionary *)d;

@end


@interface TrackingEvent : NSObject
{
    NSString *type;
    NSString *objid;
}

@property (copy) NSString *type;
@property (copy) NSString *objid;

+(NSString *)requestUrl;
+(void)setRequestUrl: (NSString *)url;

+(void)sendImpressionForObjectOfType: (NSString *)objtype
							objectID: (NSString *)objid
							 actorid: (uint64_t)actorid;

+(void)sendClickForObjectOfType: (NSString *)objtype
					   objectID: (NSString *)objid
						actorid: (uint64_t)actorid;

+(SCTrackingEventSender *)globalSender;

-(void)sendAsImpression;

@end

#endif